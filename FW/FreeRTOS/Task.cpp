#include "Task.hpp"
#include "string.h"


namespace FreeRTOS
{
    Task::Task(const char *name, const uint16_t stackSize, const UBaseType_t priority) {
        strncpy(m_name, name, configMAX_TASK_NAME_LEN);
        // strncpy() does not guarantee null-termination.
        m_name[configMAX_TASK_NAME_LEN - 1] = '\0';

        m_stackSize = stackSize;
        m_priority = priority;
        m_periodInitialized = false;
    }

    Task::~Task() {
        vTaskDelete(m_handle);
    }

    void Task::Start() {
        xTaskCreate(Task::TaskFunction, m_name, m_stackSize, this, m_priority, &m_handle);
    }


    /**
     * @brief Initialize a periodic delay, useful for having a periodic execution in task
     *        Use EndPeriod() to wait for next period
     * 
     * @param milliseconds 
     */
    void Task::InitPeriod(uint32_t milliseconds) {
        m_period = (configTICK_RATE_HZ * milliseconds) / 1000;
        m_previousPeriod = xTaskGetTickCount();
        m_periodInitialized = true;
    }


    /**
     * @brief Wait until end of period
     * 
     */
    void Task::EndPeriod() {
        vTaskDelayUntil(&m_previousPeriod, m_period);
    }


    /**
     * @brief Delay Task a specific number of milliseconds
     * 
     * @param milliseconds Number of milliseconds to delay
     */
    void Task::Delay(uint32_t milliseconds) {
        TickType_t ticks = (configTICK_RATE_HZ * milliseconds) / 1000;
        vTaskDelay(ticks);
    }


    /**
     * @brief Wrapper function from FreeRTOS C API to C++
     * 
     * @param instance Instance of this task
     */
    void Task::TaskFunction(void *instance) {
        Task *task = (Task*)instance;

        task->Run();

        vTaskDelete(task->m_handle);
    }


} // namespace FreeRTOS
