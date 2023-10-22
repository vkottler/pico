INCLUDE pico-sdk/src/rp2_common/pico_standard_link/memmap_default.ld

/* https://github.com/raspberrypi/pico-sdk/issues/1381 */
PROVIDE (__heap_start = __end__);
PROVIDE (__heap_end = __HeapLimit);
