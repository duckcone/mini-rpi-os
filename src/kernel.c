#include "io.h"

void main() {
    uart_init();
    uart_writeText("hello world!\n");
    while (1);
}