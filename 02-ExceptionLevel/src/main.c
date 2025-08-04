#include "printf.h"
#include "mini_uart.h"

unsigned long get_el_level(void) {
    unsigned long el;
    __asm__ volatile (
        "mrs %0, CurrentEL\n"
        "lsr %0, %0, #2\n"
        : "=r" (el) // Output to variable el
        :           // No Input
        :           // No register be broken
    );
    return el;
}

void main() {
    uart_init();
    
    init_printf(0, putc);

    int el = get_el_level();
    printf("Exception level: %d \r\n", el);
    
    while (1) {
        uart_send(uart_recv());
    }
}