#include <stddef.h>

/* BSS 區符號 (由 linker script 提供) */
extern char __bss_start[];
extern char __bss_end[];

/* 提供一個簡單的 stack */
__attribute__((section(".stack")))
static char stack[16 * 1024];
__attribute__((used))
void *__stack_top = stack + sizeof(stack);

void kernel_main(void);

__attribute__((section(".text.boot")))
void boot(void) {
    __asm__ __volatile__(
        "mrs x1, mpidr_el1       \n\t"
        "and x1, x1, #0xff       \n\t"
        "cbnz x1, 1f             \n\t"   // 非 core0 去 1
        "mov sp, %[stack_top]    \n\t"
        "bl kernel_main          \n\t"
        "1:                      \n\t"
        "wfe                     \n\t"
        "b 1b                    \n\t"
        :
        : [stack_top] "r" (__stack_top)
    );
}

/* 簡單清零 bss + 呼叫 main */
void kernel_main(void) {
    // 清 BSS
    for (char *p = __bss_start; p < __bss_end; p++) {
        *p = 0;
    }

    // 呼叫 main
    extern void main(void);
    main();
}

