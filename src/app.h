#pragma once

#include "picolibc-semihost/App.h"
#include "uart_stdio.h"

void init_clock(void);
void init_led(void);

bool dispatch_uart(UartInterface &uart, App &app);
