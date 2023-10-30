#pragma once

#include "boards/pico.h"
#include "pico_headers.h"
#include "picolibc-semihost/App.h"

static constexpr uint led_pin = PICO_DEFAULT_LED_PIN;

void register_commands(CommandLineApp &app);
