#include "cli.h"
#include "system.h"

void do_led(CommandLine &cli)
{
    (void)cli;
    gpio_xor_mask(1u << led_pin);
    printf("Toggling LED.\n");
}

void do_exit(CommandLine &cli)
{
    /* First argument: true/false for bootloader vs. application reset. */
    bool bootloader = true;
    cli.as_bool<0>(bootloader);

    printf("Resetting to %s.\n", bootloader ? "bootloader" : "application");
    reset(bootloader);
}

void do_clocks(CommandLine &cli)
{
    (void)cli;

    printf("pll_sys  = %lu kHz\n",
           frequency_count_khz(CLOCKS_FC0_SRC_VALUE_PLL_SYS_CLKSRC_PRIMARY));
    printf("pll_usb  = %lu kHz\n",
           frequency_count_khz(CLOCKS_FC0_SRC_VALUE_PLL_USB_CLKSRC_PRIMARY));
    printf("rosc     = %lu kHz\n",
           frequency_count_khz(CLOCKS_FC0_SRC_VALUE_ROSC_CLKSRC));
    printf("clk_sys  = %lu kHz\n",
           frequency_count_khz(CLOCKS_FC0_SRC_VALUE_CLK_SYS));
    printf("clk_peri = %lu kHz\n",
           frequency_count_khz(CLOCKS_FC0_SRC_VALUE_CLK_PERI));
    printf("clk_usb  = %lu kHz\n",
           frequency_count_khz(CLOCKS_FC0_SRC_VALUE_CLK_USB));
    printf("clk_adc  = %lu kHz\n",
           frequency_count_khz(CLOCKS_FC0_SRC_VALUE_CLK_ADC));
    printf("clk_rtc  = %lu kHz\n",
           frequency_count_khz(CLOCKS_FC0_SRC_VALUE_CLK_RTC));
}

void do_net(CommandLine &cli)
{
    (void)cli;
}

void register_commands(CommandLineApp &app)
{
    app.add_handler("led", do_led, "toggle the LED on or off");
    app.add_handler("exit", do_exit, "exit the application");
    app.add_handler("clocks", do_clocks);
    app.add_handler("net", do_net);
}
