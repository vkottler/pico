#pragma once

/* third-party */
#include "coral/buffer/FullDuplexBuffer.h"

/* internal */
#include "pico_headers.h"

template <size_t tx_depth, size_t rx_depth>
class UartManager
    : public Coral::FullDuplexBuffer<UartManager<tx_depth, rx_depth>, tx_depth,
                                     rx_depth, char>
{
    using FdBuffer = Coral::FullDuplexBuffer<UartManager<tx_depth, rx_depth>,
                                             tx_depth, rx_depth, char>;

  public:
    UartManager(uart_inst_t *_uart = nullptr, bool _echo = true)
        : FdBuffer(), uart(_uart), echo(_echo)
    {
    }

    void putc_block(uint8_t data)
    {
        this->tx.push_blocking(data);
    }

    void flush(void)
    {
        this->tx.flush();

        /* Wait for UART to be completely empty. */
        if (uart)
        {
            uart_tx_wait_blocking(uart);
        }

        stdio_flush();
    }

    inline void service_tx_impl(FdBuffer::TxBuffer *buf)
    {
        char data;

        while (!buf->empty() and
               (not uart or (uart and uart_is_writable(uart))))
        {
            assert(buf->pop(data));

            /* Write UART. */
            if (uart)
            {
                uart_get_hw(uart)->dr = data;
            }

            /* Write via pico-sdk stdio. */
            putchar_raw(data);
        }
    }

    inline void receive_byte(FdBuffer::RxBuffer *buf, uint8_t data)
    {
        assert(buf->push(data));

        if (echo)
        {
            switch (data)
            {
            case '\r':
                putc_block('\n');
                [[fallthrough]];
            default:
                putc_block(data);
            }
        }
    }

    inline void service_rx_impl(FdBuffer::RxBuffer *buf)
    {
        /* Check hardware UART. */
        if (uart)
        {
            while (!buf->full() and uart_is_readable(uart))
            {
                receive_byte(buf, uart_getc(uart));
            }
        }

        /* Check pico-sdk stdio. */
        int stdio_data;
        while (!buf->full() and
               ((stdio_data = getchar_timeout_us(0)) != PICO_ERROR_TIMEOUT))
        {
            receive_byte(buf, stdio_data);
        }
    }

  protected:
    uart_inst_t *uart;
    bool echo;
};
