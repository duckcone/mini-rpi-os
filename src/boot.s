.section ".text.boot" // Make sure

.global _start // Execution starts here

_start:
    // Check processor ID is zero (executing on main core), else hang
    mrs x1, mpidr_el1
    and x1, x1, #0xff // Check processor id
    cbz x1, master // Jump to master if the processor id == 0
    b proc_hang

proc_hang: wfe // We're not on the main core, so hang in an infinite wait loop
    b proc_hang

master: // We're in the main core!
    ldr x1, =_start
    mov sp, x1

    // Clean the BSS section
    ldr x1, =__bss_start // Start address
    ldr w2, =__bss_size // Size of the section

memzero:
    cbz w2, 4f
    str xzr, [x1], #8
    sub w2, w2, #1
    cbnz w2, memzero

    // Jump to our main() routine in C (make sure it doesn't return)
4: bl main
    // In case it does return, halt the master core too
    b proc_hang


