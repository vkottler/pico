/* internal */
#include "cli.h"
#include "uart_stdio.h"

void core1_app(void)
{
    while (true)
    {
        // some kind of state machine thing?

        /* LED heartbeat. */
        gpio_xor_mask(1u << led_pin);
        sleep_until(delayed_by_us(get_absolute_time(), 100 * 1000));
    }
}

void init(void)
{
    stdio_usb_init();

    gpio_init(led_pin);
    gpio_set_dir(led_pin, GPIO_OUT);

    /* Initialize UART pins and peripheral. */
    if (stdio_uart)
    {
        gpio_set_function(PICO_DEFAULT_UART_TX_PIN, GPIO_FUNC_UART);
        gpio_set_function(PICO_DEFAULT_UART_RX_PIN, GPIO_FUNC_UART);
        uart_init(stdio_uart, 115200);
    }
}

int main(void)
{
    init();

    /* Start other processor. */
    multicore_reset_core1();
    multicore_launch_core1(core1_app);

    App app(register_commands);

    auto &uart = get_stdio_uart();

    while (true)
    {
        /* Un-comment when leveraging semihosting for the CLI. */
        // char input[BUFSIZ];
        // app.poll_stdin(input);

        uart.dispatch();

        while (!uart.rx.empty())
        {
            char data;
            assert(uart.rx.pop(data));

            bool do_prompt = data == '\r';

            if (do_prompt)
            {
                data = '\n';
            }

            app.buf.push_blocking(data);

            if (do_prompt)
            {
                app.logger.log(prompt);
            }
        }
    }

    return 0;
}
