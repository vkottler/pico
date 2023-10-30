/* toolchain */
#include <cstdio>

/* internal */
#include "pico_headers.h"
#include "system.h"

void reset(bool bootloader)
{
    fflush(stdout);

    if (bootloader)
    {
        rom_reset_usb_boot_fn func =
            (rom_reset_usb_boot_fn)rom_func_lookup(ROM_FUNC_RESET_USB_BOOT);
        func(0, 0);
    }
    else
    {
        /* Perform a reset via the Application Interrupt and Reset Control
         * Register. */
        scb_hw->aircr = (0x05FA << M0PLUS_AIRCR_VECTKEY_LSB) |
                        M0PLUS_AIRCR_SYSRESETREQ_BITS;
    }

    tight_loop_contents();
    __builtin_unreachable();
}

extern "C" void __attribute__((noreturn)) _exit(int status)
{
    printf("Exiting %d.\n", status);
    reset(true);
}
