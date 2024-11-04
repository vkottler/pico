#include "core1.h"
#include "cli.h"

static void core1_app(void)
{
    while (true)
    {
        /* LED heartbeat. */
        gpio_xor_mask(1u << led_pin);
        sleep_until(delayed_by_us(get_absolute_time(), 100 * 1000));
    }
}

void core1_init(void)
{
    /* Start other processor. */
    multicore_reset_core1();
    multicore_launch_core1(core1_app);
}
