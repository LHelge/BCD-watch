#ifndef _FREERTOS_TASK_HPP
#define _FREERTOS_TASK_HPP 

#include "FreeRTOS.h"
#include "Task.h"
#include "string.h"

namespace FreeRTOS
{
    /**
     * @brief FreeRTOS task wrapper
     * @note Template stackSize have to be a multiple of sizeof(StackType_t)
     * 
     * @tparam stackSize 
     */
    template <size_t stackSize>
    class Task {
    public:

        /**
         * @brief Construct a new Task:: Task object
         * 
         * @param name Task name, will be truncated if longer than configMAX_TASK_LENGTH
         * @param stackSize Stack size in bytes, rounded up to nearest sizeof(portSTACK_TYPE)
         * @param priority Task priority
         */
        Task(const char *name, UBaseType_t priority) {
            // TODO: assert(stackSize % sizeof(StackType_t));

            strncpy(m_name, name, configMAX_TASK_NAME_LEN);
            // strncpy() does not guarantee null-termination.
            m_name[configMAX_TASK_NAME_LEN - 1] = '\0';

            // FreeRTOS takes stack size in words of length sizeof(portSTACK_TYPE)
            // round up
            m_stackSize = (configSTACK_DEPTH_TYPE)((stackSize + sizeof(portSTACK_TYPE) - 1) / sizeof(portSTACK_TYPE));

            m_priority = priority;
            m_periodInitialized = false;
        }


        /**
         * @brief Destroy the Task object
         * 
         */
        ~Task() {
            DeInit();
            vTaskDelete(m_handle);
        }


        /**
         * @brief Start executing task.
         * 
         */
        void Start()  {
           m_handle = xTaskCreateStatic(Task::TaskFunction, m_name, sizeof(m_stack) / sizeof(StackType_t), this, m_priority, m_stack, &m_buffer);
        }


         /**
         * @brief Start FreeRTOS scheduler. 
         *        NOTE! This function shall never return under normal circumstances.
         * 
         */
        static void StartScheduler() {
            vTaskStartScheduler();
        }


        // Four prio-levels should be enough for now
        static constexpr UBaseType_t IdlePriority   = tskIDLE_PRIORITY;
        static constexpr UBaseType_t LowPriority    = tskIDLE_PRIORITY + 1;
        static constexpr UBaseType_t MediumPriority = tskIDLE_PRIORITY + 2;
        static constexpr UBaseType_t HighPriority   = tskIDLE_PRIORITY + 3;
    protected:

        virtual void Init() {};
        virtual void Run() = 0;
        virtual void DeInit(){};
        
        
        /**
         * @brief Initialize a periodic delay, useful for having a periodic execution in task
         *        Use EndPeriod() to wait for next period
         * 
         * @param milliseconds 
         */
        void InitPeriod(uint32_t milliseconds)  {
            m_period = pdMS_TO_TICKS(milliseconds);
            m_previousPeriod = xTaskGetTickCount();
            m_periodInitialized = true;
        }


        /**
         * @brief Wait until end of period
         * 
         */
        void EndPeriod() {
            vTaskDelayUntil(&m_previousPeriod, m_period);
        }


        /**
         * @brief Delay Task a specific number of milliseconds
         * 
         * @param milliseconds Number of milliseconds to delay
         */
        static void Delay(uint32_t milliseconds)  {
            TickType_t ticks = pdMS_TO_TICKS(milliseconds);
            vTaskDelay(ticks);
        }
    private:

        /**
         * @brief Wrapper function from FreeRTOS C API to C++
         * 
         * @param instance Instance of this task
         */
        static void TaskFunction(void *instance)  {
            Task *task = (Task*)instance;

            task->Init();
            task->Run();
            task->DeInit();

            vTaskDelete(task->m_handle);
        }

        TaskHandle_t m_handle;
        char m_name[configMAX_TASK_NAME_LEN];
        configSTACK_DEPTH_TYPE m_stackSize;
        UBaseType_t m_priority;
        bool m_periodInitialized;
        TickType_t m_previousPeriod;
        TickType_t m_period;
        StackType_t m_stack[stackSize / sizeof(StackType_t)];
        StaticTask_t m_buffer;
    };
} // namespace FreeRTOS



#endif