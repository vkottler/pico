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
    UartManager(uart_inst_t *_uart, bool _echo = true,
                bool _add_carriage_return = true)
        : FdBuffer(), uart(_uart), echo(_echo),
          add_carriage_return(_add_carriage_return)
    {
    }

    void putc_block(uint8_t data)
    {
        switch (data)
        {
        case '\n':
            /* If we should add carriage returns, add it first. */
            if (add_carriage_return)
            {
                putc_block('\r');
            }
            break;
        }

        this->tx.push_blocking(data);
    }

    void flush(void)
    {
        this->tx.flush();

        /* Wait for UART to be completely empty. */
        uart_tx_wait_blocking(uart);
    }

    inline void service_tx_impl(FdBuffer::TxBuffer *buf)
    {
        char data;
        while (uart_is_writable(uart) and !buf->empty())
        {
            assert(buf->pop(data));
            uart_get_hw(uart)->dr = data;
        }
    }

    inline void service_rx_impl(FdBuffer::RxBuffer *buf)
    {
        uint8_t data;
        while (uart_is_readable(uart) and !buf->full())
        {
            data = uart_getc(uart);
            assert(buf->push(data));

            if (echo)
            {
                switch (data)
                {
                case '\r':
                    putc_block('\n');

                    /*
                     * If carriage returns are getting added automatically,
                     * the '\n' put will already add one.
                     */
                    if (add_carriage_return)
                    {
                        break;
                    }

                    [[fallthrough]];
                default:
                    putc_block(data);
                }
            }
        }
    }

  protected:
    uart_inst_t *uart;
    bool echo;
    bool add_carriage_return;
};
