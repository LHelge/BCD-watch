#ifndef _FREERTOS_MESSAGE_BUFFER_HPP
#define _FREERTOS_MESSAGE_BUFFER_HPP


#include "FreeRTOS.h"
#include "message_buffer.h"


namespace FreeRTOS
{
    /**
     * @brief Message buffer class wrapping FreeRTOS message buffer functions. passes messages of different length
     *        between tasks.
     * 
     * @tparam size Size of internal buffer in bytes
     */
    template<size_t size>
    class MessageBuffer {
    public:

        /**
         * @brief Construct a new MessageBuffer object
         * 
         */
        MessageBuffer() {
            m_handle = xMessageBufferCreateStatic(size, m_buffer, m_staticMessageBuffer);
        }


        /**
         * @brief Destroy the MessageBuffer object
         * 
         */
        ~MessageBuffer() {
            vMessageBufferDelete(m_handle);
        }


        /**
         * @brief Write a new message to the buffer
         * 
         * @param data Message
         * @param length Length of message
         * @param timeout Time in milliseconds befor timing out of bufffer is full. Only complete messages will be written
         * @return true Message was written successfully to the buffer
         * @return false Buffer full, timed out
         */
        bool Write(uint8_t *data, size_t length, uint32_t timeout) {
            size_t bytesSent = xMessageBufferSend(m_handle, data, length, pdMS_TO_TICKS(timeout));

            // Messages are only sent complete. If write times our 0 is returned
            return bytesSent > 0;
        }


        /**
         * @brief Read a message from the buffer Blocking for Timeout milliseconds if buffer is empty
         * 
         * @param data Ponter to read buffer
         * @param maxLength Size of read buffer 
         * @param timeout Time in milliseconds before timing out if buffer is empty
         * @return size_t Number of bytes read, 0 if timed out
         */
        size_t Read(uint8_t *data, size_t maxLength, uint32_t timeout) {
            return xMessageBufferReceive(m_handle, data, maxLength, pdMS_TO_TICKS(timeout));
        }


    private:
        MessageBufferHandle_t m_handle;
        StaticMessageBuffer_t m_staticMessageBuffer;
        uint8_t m_buffer[size];
    };
} // namespace FreeRTOS



#endif