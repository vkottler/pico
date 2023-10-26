/* internal */
#include "pico_headers.h"
#include "picolibc-semihost/App.h"
#include "system.h"

static constexpr uint led_pin = 25;

static inline void gpio_toggle(uint gpio)
{
    gpio_xor_mask(1u << gpio);
}

void do_led(CommandLine &cli)
{
    (void)cli;
    gpio_toggle(led_pin);
    printf("Toggling LED.\n");
}

void register_commands(CommandLineApp &app)
{
    app.add_handler("led", do_led, "toggle the LED on or off");
}

void core1_app(void)
{
    while (true)
    {
        // some kind of state machine thing?

        /* LED heartbeat. */
        gpio_toggle(led_pin);
        sleep_until(delayed_by_us(get_absolute_time(), 100 * 1000));
    }
}

void init(uint led_pin)
{
    gpio_init(led_pin);
    gpio_set_dir(led_pin, GPIO_OUT);

    /* Initialize UART pins and peripheral. */
    gpio_set_function(0, GPIO_FUNC_UART);
    gpio_set_function(1, GPIO_FUNC_UART);
    uart_init(uart0, 115200);

    dump_clocks();
}

char input[BUFSIZ];

int main(void)
{
    init(led_pin);

    /* Start other processor. */
    multicore_reset_core1();
    multicore_launch_core1(core1_app);

    App app(register_commands);

    // need to connect uart to stdin/stdout

    while (true)
    {
        app.poll_stdin(input);
    }

    return 0;
}
