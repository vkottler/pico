/* internal */
#include "app.h"
#include "cli.h"
#include "core1.h"
// #include "wizchip.h"

static inline void init(void)
{
    init_clock();
    init_led();

    // stdio_usb_init();

    /* Initialize UART pins and peripheral. */
    if (stdio_uart)
    {
        gpio_set_function(PICO_DEFAULT_UART_TX_PIN, GPIO_FUNC_UART);
        gpio_set_function(PICO_DEFAULT_UART_RX_PIN, GPIO_FUNC_UART);
        uart_init(stdio_uart, 115200);
    }

    core1_init();

    // pico_wizchip_init();
}

int main(void)
{
    init();

    App app(register_commands);

    auto &uart = get_stdio_uart();

    bool keep_going = true;
    while (keep_going)
    {
        /* Un-comment when leveraging semihosting for the CLI. */
        // char input[BUFSIZ];
        // app.poll_stdin(input);

        keep_going = dispatch_uart(uart, app);
    }

    return 0;
}
