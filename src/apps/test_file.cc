/* internal */
#include "cli.h"
#include "uart_stdio.h"
#include "wizchip.h"

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

/* Clock */
#define PLL_SYS_KHZ (133 * 1000)

static void set_clock_khz(void)
{
    // set a system clock frequency in khz
    set_sys_clock_khz(PLL_SYS_KHZ, true);

    // configure the specified clock
    clock_configure(
        clk_peri,
        0,                                                // No glitchless mux
        CLOCKS_CLK_PERI_CTRL_AUXSRC_VALUE_CLKSRC_PLL_SYS, // System PLL on AUX
                                                          // mux
        PLL_SYS_KHZ * 1000,                               // Input frequency
        PLL_SYS_KHZ * 1000 // Output (must be same as no divider)
    );
}

void init(void)
{
    set_clock_khz();
    stdio_usb_init();

    gpio_init(led_pin);
    gpio_set_dir(led_pin, GPIO_OUT);
    bi_decl(bi_1pin_with_name(led_pin, "LED"));

    /* Initialize UART pins and peripheral. */
    if (stdio_uart)
    {
        gpio_set_function(PICO_DEFAULT_UART_TX_PIN, GPIO_FUNC_UART);
        gpio_set_function(PICO_DEFAULT_UART_RX_PIN, GPIO_FUNC_UART);
        uart_init(stdio_uart, 115200);
    }

    pico_wizchip_init();
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
