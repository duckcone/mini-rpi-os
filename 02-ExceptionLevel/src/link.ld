SECTIONS
{
    /* Kernel load address for AArch64 */
    . = 0x80000;

    /* Text section, include boot code */
    .text : {
        KEEP(*(.text.boot));
        *(.text .text.* .gnu.linkonce.t*);
    }

    /* Read-only data */
    .rodata : {
        *(.rodata .rodata.* .gnu.linkonce.r*);
    }

    /* Provide _data symbol at this point */
    PROVIDE(_data = .);

    /* Data section */
    .data : {
        *(.data .data.* .gnu.linkonce.d*);
    }

    /* BSS section (uninitialized, no load) */
    .bss (NOLOAD) : {
        . = ALIGN(16);
        __bss_start = .;
        *(.bss .bss.*)
        *(COMMON)
        __bss_end = .;
    }

    /* End of kernel */
    _end = .;

    /* Discard unnecessary sections */
    /DISCARD/ : {
        *(.comment)
        *(.gnu*)
        *(.note*)
        *(.eh_frame*)
    }
}

/* BSS size in 8-byte units */
__bss_size = (__bss_end - __bss_start) >> 3;
