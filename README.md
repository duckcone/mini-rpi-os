# Mini-Rpi-OS

A mini OS for Raspberry Pi 4B

## Requirement

- QEMU: 9.2.0
- aarch64-linux-gnu-gcc: 13.3.0
- aarch64-linux-gnu-ld: 2.42
- aarch64-linux-gnu-objcopy: 2.42

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