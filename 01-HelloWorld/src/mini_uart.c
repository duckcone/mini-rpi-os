#include "peripherals/mini_uart.h"
#include "peripherals/gpio.h"
#include "mini_uart.h"

#define uintptr_t unsigned long
#define UART_CLOCK 500000000 // Set uart clock

#define AUX_MU_BAUD(baud) ((UART_CLOCK/(baud * 8)) - 1)
#define PULL_NUM 0

#define mmio_write(reg, val) (*(volatile unsigned int *)((uintptr_t)reg) = val)
#define mmio_read(reg) (*(volatile unsigned int *)((uintptr_t)reg))

unsigned int gpio_call(unsigned int pin_number, unsigned int value, unsigned int base, unsigned int field_size, unsigned int field_max) {
    unsigned int field_mask = (1 << field_size) - 1;

    if (pin_number > field_max) return 0;
    if (value > field_mask) return 0; 

    unsigned int num_fields = 32 / field_size;
    unsigned int reg = base + ((pin_number / num_fields) * 4);
    unsigned int shift = (pin_number % num_fields) * field_size;

    unsigned int curval = mmio_read(reg);
    curval &= ~(field_mask << shift);
    curval |= value << shift;
    mmio_write(reg, curval);

    return 1;
}

unsigned int gpio_pull(unsigned int pin_number, unsigned int value) {
    return gpio_call(pin_number, value, GPPUPPDN0, 2, GPIO_MAX_PIN);
}

unsigned int gpio_function(unsigned int pin_number, unsigned int value){
    return gpio_call(pin_number, value, GPFSEL0, 3, GPIO_MAX_PIN);
}

void gpio_use_as_alt5(unsigned int pin_number) {
    gpio_pull(pin_number, PULL_NUM);
    gpio_function(pin_number, GPIO_FUNCTION_ALT5);
}

void uart_init(void) {
    mmio_write(AUX_ENABLES, 1);                       // Enable mini uart (this also enables access to its registers)
    mmio_write(AUX_MU_IER_REG, 0);                    // Disable receive and transmit interrupts
    mmio_write(AUX_MU_CNTL_REG, 3);                   // Disable auto flow control and disable receiver and transmitter (for now)
    mmio_write(AUX_MU_LCR_REG, 3);                    // Enable 8 bit mode
    mmio_write(AUX_MU_MCR_REG, 0);                    // Set TRS line to be always high
    mmio_write(AUX_MU_IIR_REG, 0xC6);                 // Disable interrupts
    mmio_write(AUX_MU_BAUD_REG, AUX_MU_BAUD(115200)); // Set baud rate to 115200
    gpio_use_as_alt5(14);
    gpio_use_as_alt5(15);
}

unsigned int uart_is_write_byte_ready() {
    return mmio_read(AUX_MU_LSR_REG) & 0x20;
}

char uart_recv(void) {
    while(!(mmio_read(AUX_MU_LSR_REG)&0x01));
    return(mmio_read(AUX_MU_IO_REG)&0xFF);
}

void uart_send(unsigned char c) {
    while (!uart_is_write_byte_ready()); 
    mmio_write(AUX_MU_IO_REG, (unsigned int)c);
}

void uart_send_string(char *str) {
    if (!str || !*str) {
        return;
    }

    while (*str) {
        if (*str == '\n')
            uart_send('\r');
        uart_send(*str++);
    }

}
