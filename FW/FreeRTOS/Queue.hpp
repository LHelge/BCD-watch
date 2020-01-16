#ifndef _FREERTOS_QUEUE_HPP
#define _FREERTOS_QUEUE_HPP

#include "FreeRTOS.h"
#include "queue.h"


namespace FreeRTOS
{
    template<class T>
    class Queue {
    public:
        Queue(const uint16_t size) {
            m_handle = xQueueCreate(size, sizeof(T));
        }

        ~Queue() {
            vQueueDelete(m_handle);
        }


        /**
         * @brief Add item to queue, if queue is full, thread will be paused until there
         *        is room or timeout elapses. Do not use this within an interrupt, use
         *        EnqueueFromInterrupt() instead. Will return true if item successfully
         *        was added to queue, or false if timed out
         * 
         * @param item Item to add to queue
         * @param timeout Timeout in milliseconds (max MaxTimeout)
         * @return true Item was added to queue
         * @return false Queue is full and timed out
         */
        bool Enqueue(T *item, const uint32_t timeout = MaxTimeout) {
            TickType_t ticks = pdMS_TO_TICKS(timeout > MaxTimeout ? MaxTimeout : timeout);
            return xQueueSend(m_handle, item, ticks) == pdTRUE;
        }


        /**
         * @brief Add item to queue from an interrupt
         * 
         * @param item Item to add to queue
         * @return true Item was added to queue
         * @return false Queue is full
         */
        bool EnqueueFromInterrupt(T *item) {
            return xQueueSendFromISR(m_handle, item, NULL) == pdTRUE;
        }


        /**
         * @brief Get item from the queue. If queue is empty thread will be paused until
         *        there is an item to get or until timeout has elapsed
         * 
         * @param item Pointer to the item to get
         * @param timeout Timeout in milliseconds (max MaxTimeout)
         * @return true Item was retrieved
         * @return false Queue was empty and timed out
         */
        bool Dequeue(T *item, const uint32_t timeout = MaxTimeout) {
            TickType_t ticks = pdMS_TO_TICKS(timeout > MaxTimeout ? MaxTimeout : timeout);
            return xQueueReceive(m_handle, item, ticks) == pdTRUE;
        }


        /**
         * @brief Number of milliseconds for no timeout (defined as 24 H)
         * 
         */
        static constexpr uint32_t MaxTimeout = pdMS_TO_TICKS(86400000);


        /**
         * @brief Instant timeout (0 milliseconds)
         * 
         */
        static constexpr uint32_t InstantTimeout = 0;

    private:
        QueueHandle_t m_handle;
    };
} // namespace FreeRTOS


#endif 