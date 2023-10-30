#include "wizchip.h"

extern "C"
{
#include "wizchip_conf.h"

#include "w5x00_spi.h"

#include "dhcp.h"
#include "dns.h"
#include "timer.h"
}

/* Timer */
static volatile uint16_t g_msec_cnt = 0;

/* Timer */
static void repeating_timer_callback(void)
{
    auto val = g_msec_cnt;
    val++;

    if (val >= 1000 - 1)
    {
        val = 0;

        DHCP_time_handler();
        DNS_time_handler();
    }

    g_msec_cnt = val;
}

extern "C" void pico_wizchip_init(void)
{
    wizchip_spi_initialize();
    wizchip_cris_initialize();

    wizchip_reset();

    wizchip_initialize();
    wizchip_check();

    wizchip_1ms_timer_initialize(repeating_timer_callback);
}
