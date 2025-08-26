#include <stddef.h>

/* BSS 區符號 (由 linker script 提供) */
extern char __bss_start[];
extern char __bss_end[];

void kernel_main(void);

__attribute__((naked, section(".text.boot")))
void boot(void) {
    __asm__ __volatile__(
        "ldr x0, =__stack_top    \n"  // 設定 SP
        "mov sp, x0              \n"
        "bl kernel_main          \n"  // 呼叫 C 的 main
        "b .                     \n"  // 死迴圈避免返回
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

/* 提供一個簡單的 stack */
__attribute__((section(".bss")))
static char stack[16 * 1024];
__attribute__((used))
void *__stack_top = stack + sizeof(stack);
