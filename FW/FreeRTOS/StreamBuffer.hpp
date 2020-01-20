#ifndef _FREERTOS_STREAM_BUFFER_HPP
#define _FREERTOS_STREAM_BUFFER_HPP

#include "FreeRTOS.h"
#include "stream_buffer.h"


namespace FreeRTOS
{
    template<size_t size>
    class StreamBuffer {
    public:

        /**
         * @brief Construct a new StreamBuffer object
         * 
         */
        StreamBuffer() {
            m_handle = xStreamBufferCreateStatic(size, 1, m_buffer, &m_staticStreamBuffer);
        }


        /**
         * @brief Destroy the StreamBuffer object
         * 
         */
        ~StreamBuffer() {
            vStreamBufferDelete(m_handle);
        }


        /**
         * @brief Blocking write a single byte to stream buffer
         * @note Do not use this from an Interrupt, use WriteFromInterrupt() instead
         * 
         * @param data Data to write
         * @param timeout Timeout in milliseconds to wait if stream is full
         * @return size_t Number of bytes written, should equal length if stream buffer is not full
         */
        size_t Write(uint8_t data, uint32_t timeout) {
            return write(&data, 1, timeout);
        }


        /**
         * @brief Blocking write any number of bytes to a stream
         * 
         * @param data Pointer to daa to write
         * @param length Number of bytes to write
         * @param timeout Timeout in milliseconds to wait if stream is full
         * @return size_t Number of bytes written, should equal length if stream buffer is not full
         */
        size_t Write(uint8_t *data, size_t length, uint32_t timeout) {
            return xStreamBufferSend(m_handle, data, length, pdMS_TO_TICKS(timeout));
        }


        /**
         * @brief Non-blocking write a single byte to buffer from an interrupt
         * 
         * @param data Data to write
         */
        void WriteFromInterrupt(uint8_t data) {
            BaseType_t yield = pdFalse;

            xStreamBufferSendFromISR(m_handle, &data, 1, &yield);

            portYIELD_FROM_ISR(yield);
        }


        /**
         * @brief Blocking read a single byte of data from message buffer
         * 
         * @param data Byte to read
         * @param timeout Timeout in milliseconds to wait if the buffer is empty
         * @return size_t 
         */
        size_t Read(uint8_t *data, uint32_t timeout) {
            return Read(data, 1, timeout);
        }


        /**
         * @brief Blocking read of multiple bytes from a message buffer
         * 
         * @param data Pointer to the read buffer
         * @param length Number of bytes to read
         * @param timeout Timeout in milliseconds to wait if the buffer is empty
         * @return size_t 
         */
        size_t Read(uint8_t *data, size_t length, uint32_t timeout) {
            return xStreamBufferReceive(m_handle, data, lenght, pdMS_TO_TICKS(timeout));
        }

    private:
        StreamBufferHandle_t m_handle;
        uint8_t m_buffer[size];
        StaticStreamBuffer_t m_staticStreamBuffer;
    };
} // namespace FreeRTOS



#endif