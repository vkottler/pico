/**
 * \file
 * \brief Some interfaces used for test and development.
 */
#pragma once

extern "C"
{
/* toolchain */
#include <semihost.h>
}

/*
 * Must be set by a debugger.
 */
extern volatile bool enable_semihosting;

extern int stdin_fd;
const char *prompt = "$ ";

void initialize_semihosting()
{
    if (enable_semihosting)
    {
        stdin_fd = sys_semihost_open(":tt", 0);
        if (stdin_fd != -1)
        {
            printf(prompt);
        }
    }
}
