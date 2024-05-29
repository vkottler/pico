#include "core1.h"
#include "cli.h"

static constexpr uint led1_pin = 16;
static constexpr uint led2_pin = 17;

static void core1_app(void)
{
    while (true)
    {
        // some kind of state machine thing?

        /* LED heartbeat. */
        gpio_xor_mask(1u << led_pin);

        /* board */
        gpio_xor_mask(1u << led1_pin);
        gpio_xor_mask(1u << led2_pin);

        sleep_until(delayed_by_us(get_absolute_time(), 100 * 1000));
    }
}

void core1_init(void)
{
    gpio_init(led1_pin);
    gpio_set_dir(led1_pin, GPIO_OUT);
    bi_decl(bi_1pin_with_name(led1_pin, "LED1"));

    gpio_init(led2_pin);
    gpio_set_dir(led2_pin, GPIO_OUT);
    bi_decl(bi_1pin_with_name(led2_pin, "LED2"));

    gpio_xor_mask(1u << led1_pin);

    /* Start other processor. */
    multicore_reset_core1();
    multicore_launch_core1(core1_app);
}
