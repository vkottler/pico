#pragma once

#define PIN_INT 21

#include <stdint.h>

/*! \brief Initialize w5x00 gpio interrupt callback function
 *  \ingroup w5x00_gpio_irq
 *
 *  Add a w5x00 interrupt callback.
 *
 *  \param socket socket number
 *  \param callback the gpio interrupt callback function
 */
void wizchip_gpio_interrupt_initialize(uint8_t socket, void (*callback)(void));

/*! \brief Assign gpio interrupt callback function
 *  \ingroup w5x00_gpio_irq
 *
 *  GPIO interrupt callback function.
 *
 *  \param gpio Which GPIO caused this interrupt
 *  \param events Which events caused this interrupt. See \ref
 * gpio_set_irq_enabled for details.
 */
static void wizchip_gpio_interrupt_callback(unsigned int gpio,
                                            uint32_t events);
