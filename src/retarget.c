/**
 * \file
 * \brief Stubs for library hooks.
 */

#ifdef __cplusplus
extern "C"
{
#endif

/* toolchain */
#include <semihost.h>
#include <stdio.h>

    void _exit(int code)
    {
        (void)code;

        while (1)
        {
            ;
        }
    }

    /*
     * Must be set by a debugger.
     */
    volatile bool enable_semihosting = false;

    static int putc_wrapper(char c, FILE *file)
    {
        (void)file;

        if (enable_semihosting)
        {
            char out[2] = {c, 0};
            sys_semihost_write0(out);
        }

        return 0;
    }

    int stdin_fd = -1;

    static int getc_wrapper(FILE *file)
    {
        (void)file;

        int result = -1;

        if (enable_semihosting && stdin_fd != -1)
        {
            char input = result;

            /*
             * The return value seems to be meaningless. There also does not
             * seem to be a way to make this non-blocking.
             */
            sys_semihost_read(stdin_fd, &input, sizeof(char));

            result = input;
        }

        return result;
    }

    static FILE __stdio =
        FDEV_SETUP_STREAM(putc_wrapper, getc_wrapper, NULL, _FDEV_SETUP_RW);

    FILE *const stdout = &__stdio;
    FILE *const stdin = &__stdio;
    FILE *const stderr = NULL;

#ifdef __cplusplus
}
#endif
