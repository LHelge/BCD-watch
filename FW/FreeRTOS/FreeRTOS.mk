FREERTOS_C_SOURCES = \
FreeRTOS/source/portable/GCC/ARM_CM0/port.c \
FreeRTOS/source/croutine.c \
FreeRTOS/source/event_groups.c \
FreeRTOS/source/list.c \
FreeRTOS/source/queue.c \
FreeRTOS/source/stream_buffer.c \
FreeRTOS/source/tasks.c \
FreeRTOS/source/timers.c \
FreeRTOS/Task.c
#FreeRTOS/source/portable/MemMang/heap_2.c


FREERTOS_CPP_SOURCES = \
FreeRTOS/Timer.cpp 



FREERTOS_INCLUDES = \
FreeRTOS \
FreeRTOS/source/include \
FreeRTOS/source/portable/GCC/ARM_CM0