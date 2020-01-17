#include <stdint.h>
#include "stm32l0xx.h"
#include "App.hpp"
#include "System.hpp"
#include "UART.hpp"
#include "FreeRTOS.h"
#include "task.h"

static App Application;

// Externs generated by linker describing where memory sectors start and end
extern uint32_t _sdata;
extern uint32_t _sidata;
extern uint32_t _edata;
extern uint32_t _sbss;
extern uint32_t _ebss;
extern uint32_t _estack;

// Part of libc, initializes static constructors (is a C functions, hence the extern "C")
extern "C" void __libc_init_array(void);

// Reset handler, GCC linker throws an error if no function called Reset_Handler exists, hence extern "C"
extern "C" void Reset_Handler(void) {
    // Initialize data segment
    uint32_t *dataInitPtr = &_sidata;
    uint32_t *dataPtr = &_sdata;
    while(dataPtr < &_edata)
        *dataPtr++ = *dataInitPtr++;


    // Set BSS segment to zero, use uint32_t since it is 4-byte aligned in linker script
    uint32_t *bssPtr = &_sbss;
    while(bssPtr < &_ebss)
        *bssPtr++ = 0;

    SystemInit();

    //Initiate static constructors
    __libc_init_array();

    // Start application task
    Application.Start();

    // Start FreeRTOS sceduler
    FreeRTOS::Task<0>::StartScheduler();

    // Should not get here

    // Reset if main returns?
    System::System::Reset();

    while(1);
}

void NMI_Handler(void) {
}

void HardFault_Handler(void) {
    while(1);
}

// void SVC_Handler(void) {
// }

// void PendSV_Handler(void) {
// }

// extern void SVC_Handler();
// extern void PendSV_Handler();
// extern void SysTick_Handler();

void Default_Handler(void) {
    while(1);
}


// Interrupt vector, can be found in family reference manual.
// replace Default_Handler with your interrupt implementation
__attribute__ ((section(".isr_vector")))
const void (*VectorTable[])(void) = {
    (const void (*)())&_estack,                         // Initial stack pointer address received from linker script
    (const void (*)())Reset_Handler,                    // The reset handler above
    (const void (*)())NMI_Handler,                      // Non maskable interrupt. The RCC Clock Security System (CSS) is linked to the NMI vector.
    (const void (*)())HardFault_Handler,                // All class of fault
    nullptr,                                            // Reserved
    nullptr,                                            // Reserved
    nullptr,                                            // Reserved
    nullptr,                                            // Reserved
    nullptr,                                            // Reserved
    nullptr,                                            // Reserved
    nullptr,                                            // Reserved
    (const void (*)())SVC_Handler,                      // System service call via SWI instruction
    nullptr,                                            // Reserved
    nullptr,                                            // Reserved
    (const void (*)())PendSV_Handler,                   // Pendable request for system service
    (const void (*)())SysTick_Handler,                  // Systick
    (const void (*)())Default_Handler,                  // WWDG
    (const void (*)())Default_Handler,                  // PVD
    (const void (*)())Default_Handler,                  // RTC
    (const void (*)())Default_Handler,                  // FLASH
    (const void (*)())Default_Handler,                  // RCC
    (const void (*)())Default_Handler,                  // EXTI 0 & 1
    (const void (*)())Default_Handler,                  // EXTI 2 & 3
    (const void (*)())Default_Handler,                  // EXTI 4 - 15
    nullptr,                                            // Reserved
    (const void (*)())Default_Handler,                  // DMA1 Channel 1
    (const void (*)())Default_Handler,                  // DMA1 Channel 2 & 3
    (const void (*)())Default_Handler,                  // DMA1 Channel 4 - 7
    (const void (*)())Default_Handler,                  // ADC1, COMP1 & COMP2
    (const void (*)())Default_Handler,                  // LPTIM1
    (const void (*)())Default_Handler,                  // USART4 & USART5
    (const void (*)())Default_Handler,                  // TIM2
    (const void (*)())Default_Handler,                  // TIM3
    (const void (*)())Default_Handler,                  // TIM6 & DAC
    (const void (*)())Default_Handler,                  // TIM7
    nullptr,                                            // Reserved
    (const void (*)())Default_Handler,                  // TIM21
    (const void (*)())Default_Handler,                  // I2C3
    (const void (*)())Default_Handler,                  // TIM22
    (const void (*)())Default_Handler,                  // I2C1
    (const void (*)())Default_Handler,                  // I2C2
    (const void (*)())Default_Handler,                  // SPI1
    (const void (*)())Default_Handler,                  // SPI2
    (const void (*)())UART::SerialPort::UART1Interrupt, // USART1
    (const void (*)())Default_Handler,                  // USART2
    (const void (*)())Default_Handler,                  // LPUART1
    nullptr,                                            // Reserved
    nullptr                                             // Reserved
};