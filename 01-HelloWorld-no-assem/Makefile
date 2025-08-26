# Project Makefile

ARMGNU ?= aarch64-linux-gnu

CFLAGS = -Wall -g -O0 -ffreestanding -nostdlib -nostartfiles -mstrict-align -Iinclude
LDFLAGS = -nostdlib -T src/link.ld

SRC_DIR = src
BUILD_DIR = build
INCLUDE_DIR = include

CFILES = $(wildcard $(SRC_DIR)/*.c)
SFILES = $(wildcard $(SRC_DIR)/*.s)
COBJS = $(CFILES:$(SRC_DIR)/%.c=$(BUILD_DIR)/%.o)
SOBJS = $(SFILES:$(SRC_DIR)/%.s=$(BUILD_DIR)/%.o)
OBJS = $(COBJS) $(SOBJS)

all: kernel8.img

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	mkdir -p $(BUILD_DIR)
	$(ARMGNU)-gcc $(CFLAGS) -c $< -o $@

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.s
	mkdir -p $(BUILD_DIR)
	$(ARMGNU)-gcc $(CFLAGS) -c $< -o $@

kernel8.img: $(OBJS)
	@mkdir -p $(BUILD_DIR)
	# Link with the cross gcc driver (simpler and more portable than ld directly)
	$(ARMGNU)-gcc $(CFLAGS) $(OBJS) $(LDFLAGS) -o $(BUILD_DIR)/kernel8.elf
	$(ARMGNU)-objcopy -O binary $(BUILD_DIR)/kernel8.elf kernel8.img

clean:
	rm -rf $(BUILD_DIR) *.img

run:
	qemu-system-aarch64 -M raspi4b -serial null -serial stdio -display none -kernel kernel8.img

debug:
	qemu-system-aarch64 -M raspi4b -serial null -serial stdio -display none -kernel $(BUILD_DIR)/kernel8.elf -S -s
