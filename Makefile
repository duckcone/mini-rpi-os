# Project Makefile

# Toolchain prefix and compiler options
GCC = aarch64-linux-gnu-gcc
LD = aarch64-linux-gnu-ld
OBJCOPY = aarch64-linux-gnu-objcopy

# Compiler flags
# CFLAGS = -Wall -g -O0 -ffreestanding -nostdinc -nostdlib -nostartfiles -mstrict-align -Iinclude
CFLAGS = -Wall -g -O0 -ffreestanding -nostdlib -nostartfiles -mstrict-align -Iinclude
LDFLAGS = -nostdlib -T src/link.ld

# Directories
SRC_DIR = src
BUILD_DIR = build
INCLUDE_DIR = include

# Source and object files
CFILES = $(wildcard $(SRC_DIR)/*.c)
SFILES = $(wildcard $(SRC_DIR)/*.s)
COBJS = $(CFILES:$(SRC_DIR)/%.c=$(BUILD_DIR)/%.o)
SOBJS = $(SFILES:$(SRC_DIR)/%.s=$(BUILD_DIR)/%.o)
OBJS = $(COBJS) $(SOBJS)

# Final target
all: kernel8.img

# Rule to build boot.o and C/ASM object files
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	mkdir -p $(BUILD_DIR)
	$(GCC) $(CFLAGS) -c $< -o $@

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.s
	mkdir -p $(BUILD_DIR)
	$(GCC) $(CFLAGS) -c $< -o $@

# Link and generate kernel8.img
kernel8.img: $(OBJS)
	$(LD) $(OBJS) $(LDFLAGS) -o $(BUILD_DIR)/kernel8.elf
	$(OBJCOPY) -O binary $(BUILD_DIR)/kernel8.elf kernel8.img

# Clean build output
clean:
	rm -rf $(BUILD_DIR) *.img

run:
	qemu-system-aarch64 -M raspi4b -serial null -serial stdio -display none -kernel kernel8.img

debug:
	qemu-system-aarch64 -M raspi4b -serial null -serial stdio -display none -kernel $(BUILD_DIR)/kernel8.elf -S -s
