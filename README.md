# Mini-Rpi-OS

A mini OS for Raspberry Pi 4B

## Requirement
### QEMU
- QEMU: 10.2.1

```
$ qemu-system-aarch64 -M help
raspi4b              Raspberry Pi 4B (revision 1.5)
```
### ARM GNU Toolchain (15.2.Rel1)
- aarch64-nnone-elf-gcc: 15.2.1
- aarch64-nnone-elf-ld: 2.45.1
- aarch64-nnone-elf-objcopy: 2.45.1

## Build Image

```shell
$ make
```

## Run by QEMU
```shell
$ make run
```

## Debug by QEMU + GDB

Open two terminal and `cd` to project root directory `mini-rpi-os`

### In terminal 1

```shell
$ make debug
```

The QEMU will wait for GDB to connect.

### In terminal 2:

```shell
$ gdb-multiarch build/kernel8.elf -tui
```

Connect to QEMU in gdb mode:

```shell
(gdb) target remote:1234
```