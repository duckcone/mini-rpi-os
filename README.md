# Mini-Rpi-OS

A mini OS for Raspberry Pi 4B

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