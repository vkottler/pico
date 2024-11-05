/* internal */
#include "app.h"
#include "cli.h"
#include "pico_headers.h"

#define PLL_SYS_KHZ (133 * 1000)

void init_clock(void)
{
    // set a system clock frequency in khz
    // set_sys_clock_khz(PLL_SYS_KHZ, true);

    // configure the specified clock
    /*
    clock_configure(
        clk_peri,
        0,                                                // No glitchless mux
        CLOCKS_CLK_PERI_CTRL_AUXSRC_VALUE_CLKSRC_PLL_SYS, // System PLL on AUX
                                                          // mux
        PLL_SYS_KHZ * 1000,                               // Input frequency
        PLL_SYS_KHZ * 1000 // Output (must be same as no divider)
    );
    */
}

void init_led(void)
{
    gpio_init(led_pin);
    gpio_set_dir(led_pin, GPIO_OUT);
    bi_decl(bi_1pin_with_name(led_pin, "BLED"));
}

bool dispatch_uart(UartInterface &uart, App &app)
{
    bool result = true;

    uart.dispatch();

    while (!uart.rx.empty())
    {
        char data;
        assert(uart.rx.pop(data));

        switch (data)
        {

        /* Special cases. */
        case 0x3:
            result = false;
            break;

        /* Default handling. */
        default:
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
            break;
        }
    }

    return result;
}
