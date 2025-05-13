#include "mini_uart.h"

void main() {
    uart_init();
    // uart_writeText("hello world!\n");
    uart_send_string("hello world!!!\n");
    while (1) {
        uart_send(uart_recv());
    }
}