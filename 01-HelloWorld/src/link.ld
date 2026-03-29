SECTIONS
{
    /* Kernel load address for Rpi 4B (AArch64) */
    . = 0x80000;

    /* Text section, include boot code */
    .text : ALIGN(16) {
        KEEP(*(.text.boot))
        *(.text)
        *(.text.*)
        
    }

    /* Read-only data */
    .rodata : ALIGN(16) {
        *(.rodata);
        *(.rodata.*);
    }

    /* Data section */
    .data : ALIGN(16) {
        __data_start = .;
        *(.data)
        *(.data.*)
        __data_end = .;
    }

    /* BSS section */
    .bss : ALIGN(16) {
        __bss_start = .;
        *(.bss .bss.*)
        __bss_end = .;
    }

    . = ALIGN(16);
    . += 128 * 1024; /* 128 KB */
    __stack_top = .;
}

/* BSS size in 8-byte units */
__bss_size = (__bss_end - __bss_start) >> 3;