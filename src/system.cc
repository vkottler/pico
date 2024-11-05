/* toolchain */
#include <cstdio>

#include "pico/runtime_init.h"

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

/* stuff from their picolibc_interface.c */
extern "C"
{
    void runtime_init(void)
    {
        // install core0 stack guard
        extern char __StackBottom;
        runtime_init_per_core_install_stack_guard(&__StackBottom);

        // piolibc __libc_init_array does __preint_array and __init_array
        extern void __libc_init_array(void);
        __libc_init_array();
    }

    __weak void runtime_init_pre_core_tls_setup(void)
    {
        extern char __tls_base;
        extern void _set_tls(void *tls);
        _set_tls(&__tls_base);
    }

    PICO_RUNTIME_INIT_FUNC_PER_CORE(runtime_init_pre_core_tls_setup,
                                    PICO_RUNTIME_INIT_PER_CORE_TLS_SETUP);
}

extern "C" void __attribute__((noreturn)) _exit(int status)
{
    printf("Exiting %d.\n", status);
    reset(true);
}
