#pragma once

/* internal */
#include "UartManager.h"
#include "pico_headers.h"

extern uart_inst_t *const stdio_uart;

static constexpr size_t uart_buffer_depth = 32;

using UartInterface = UartManager<uart_buffer_depth, uart_buffer_depth>;

UartInterface &get_stdio_uart();
