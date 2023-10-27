/* internal */
#include "uart_stdio.h"

uart_inst_t *const stdio_uart = uart0;

static UartInterface uart(stdio_uart);

UartInterface &get_stdio_uart()
{
    return uart;
}

extern "C" int putc_extra(char c, FILE *file, bool semihosting_enabled)
{
    (void)file;
    (void)semihosting_enabled;

    uart.putc_block(c);

    return 0;
}

extern "C" int flush_extra(FILE *file, bool semihosting_enabled)
{
    (void)file;
    (void)semihosting_enabled;

    uart.flush();

    return 0;
}

extern "C" void getc_extra(int *result, FILE *file, bool semihosting_enabled)
{
    (void)file;
    (void)semihosting_enabled;

    if (!uart.rx.empty())
    {
        char data;
        assert(uart.rx.pop(data));
        *result = data;
    }
}
