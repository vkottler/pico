/* internal */
#include "app.h"
#include "cli.h"
#include "core1.h"

static constexpr uint led1_pin = 16;
static constexpr uint led2_pin = 17;

void toggle_leds(void)
{
    gpio_xor_mask(1u << led1_pin);
    gpio_xor_mask(1u << led2_pin);
}

int main(void)
{
    init_led();

    gpio_init(led1_pin);
    gpio_set_dir(led1_pin, GPIO_OUT);
    bi_decl(bi_1pin_with_name(led1_pin, "LED1"));

    /* blink out of sync */
    gpio_xor_mask(1u << led1_pin);

    gpio_init(led2_pin);
    gpio_set_dir(led2_pin, GPIO_OUT);
    bi_decl(bi_1pin_with_name(led2_pin, "LED2"));

    core1_init();

    if (stdio_uart)
    {
        gpio_set_function(PICO_DEFAULT_UART_TX_PIN, GPIO_FUNC_UART);
        gpio_set_function(PICO_DEFAULT_UART_RX_PIN, GPIO_FUNC_UART);
        uart_init(stdio_uart, 115200);
    }

    while (1)
    {
        toggle_leds();
        sleep_ms(100);
        printf("Hello, world!\n");
    }

    return 0;
}
