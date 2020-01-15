#ifndef _FREERTOS_TASK_HPP
#define _FREERTOS_TASK_HPP 

#include "FreeRTOS.h"
#include "Task.h"

namespace FreeRTOS
{
    class Task {
    public:
        Task(const char *name, const uint16_t stackSize, UBaseType_t priority);
        ~Task();

        void Start();
    protected:
        virtual void Run() = 0;
        void InitPeriod(uint32_t milliseconds);
        void EndPeriod();
        void Delay(uint32_t milliseconds);
    private:
        static void TaskFunction(void *instance);
        TaskHandle_t m_handle;
        char m_name[configMAX_TASK_NAME_LEN];
        uint16_t m_stackSize;
        UBaseType_t m_priority;
        bool m_periodInitialized;
        TickType_t m_previousPeriod;
        TickType_t m_period;
    };
} // namespace FreeRTOS



#endif