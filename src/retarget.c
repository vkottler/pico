/**
 * \file
 *
 * \brief Stubs for library hooks.
 */

/* toolchain */
#include <stdio.h>

#ifdef __cplusplus
extern "C"
{
#endif

    void _exit(int code)
    {
        (void)code;

        while (1)
        {
            ;
        }
    }

    FILE *const stdout = NULL;
    FILE *const stdin = NULL;
    FILE *const stderr = NULL;

#ifdef __cplusplus
}
#endif
