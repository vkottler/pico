#pragma once

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wpedantic"
#pragma GCC diagnostic ignored "-Wvariadic-macros"

// Can't figure out how to get rid of the warnings this emits.

/* third-party */
#include "hardware/clocks.h"
#include "hardware/gpio.h"
#include "hardware/structs/scb.h"
#include "hardware/uart.h"
#include "pico/bootrom.h"
#include "pico/critical_section.h"
#include "pico/multicore.h"
#include "pico/stdio_usb.h"
#include "pico/time.h"

#pragma GCC diagnostic pop
