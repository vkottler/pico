/* internal */
#include "app.h"
#include "cli.h"
#include "core1.h"

/* sdk */
#include "hardware/i2c.h"

static constexpr uint led1_pin = 16;
static constexpr uint led2_pin = 17;

static constexpr uint sda_pin = 8;
static constexpr uint scl_pin = 9;

static inline void init(void)
{
    // init_clock();
    init_led();

    gpio_init(led1_pin);
    gpio_set_dir(led1_pin, GPIO_OUT);
    bi_decl(bi_1pin_with_name(led1_pin, "LED1"));

    gpio_init(led2_pin);
    gpio_set_dir(led2_pin, GPIO_OUT);
    bi_decl(bi_1pin_with_name(led2_pin, "LED2"));

    // This example will use I2C0 on the default SDA and SCL pins (GP4, GP5 on
    // a Pico)
    i2c_init(i2c0, 100 * 1000);
    gpio_set_function(sda_pin, GPIO_FUNC_I2C);
    gpio_set_function(scl_pin, GPIO_FUNC_I2C);
    gpio_pull_up(sda_pin);
    gpio_pull_up(scl_pin);
    bi_decl(bi_2pins_with_func(sda_pin, scl_pin, GPIO_FUNC_I2C));

    /* Initialize UART pins and peripheral. */
    if (stdio_uart)
    {
        gpio_set_function(PICO_DEFAULT_UART_TX_PIN, GPIO_FUNC_UART);
        gpio_set_function(PICO_DEFAULT_UART_RX_PIN, GPIO_FUNC_UART);
        uart_init(stdio_uart, 115200);
    }

    // core1_init();
}

void do_led1(CommandLine &cli)
{
    (void)cli;
    gpio_xor_mask(1u << led1_pin);
    printf("Toggling LED 1.\n");
}

void do_led2(CommandLine &cli)
{
    (void)cli;
    gpio_xor_mask(1u << led2_pin);
    printf("Toggling LED 2.\n");
}

void do_i2c(CommandLine &cli)
{
    (void)cli;
    printf("TODO.\n");
}

void register_app_commands(CommandLineApp &app)
{
    register_commands(app);

    /* app specific commands */
    app.add_handler("led1", do_led1, "toggle LED 1 on or off");
    app.add_handler("led2", do_led2, "toggle LED 2 on or off");
    app.add_handler("i2c", do_i2c, "interact with an I2C bus");
}

int main(void)
{
    init();

    App app(register_app_commands);

    auto &uart = get_stdio_uart();

    bool keep_going = true;
    while (keep_going)
    {
        keep_going = dispatch_uart(uart, app);
    }

    return 0;
}
