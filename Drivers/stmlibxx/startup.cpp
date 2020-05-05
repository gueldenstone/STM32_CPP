/**
 * @file: startup.cpp
 *
 * @date: 2020-05-03
 *
 * @author: Lukas Güldenstein
 *
 * @brief: Startup Code for the STM32F303xE
 */

/* -------------------------------- includes -------------------------------- */
#include <algorithm>
#include <cstdint>

#include "stm32f303xe_it.hpp"
#include "timer.hpp"
#define DEFINE_DEFAULT_ISR(name)                                                                      \
  extern "C" __attribute__((interrupt)) __attribute__((weak)) __attribute__((noreturn)) void name() { \
    while (true)                                                                                      \
      ;                                                                                               \
  }

DEFINE_DEFAULT_ISR(defaultISR)
DEFINE_DEFAULT_ISR(NMI_Handler)
DEFINE_DEFAULT_ISR(HardFault_Handler)
DEFINE_DEFAULT_ISR(MemManage_Handler)
DEFINE_DEFAULT_ISR(BusFault_Handler)
DEFINE_DEFAULT_ISR(UsageFault_Handler)
DEFINE_DEFAULT_ISR(SVC_Handler)
DEFINE_DEFAULT_ISR(DebugMon_Handler)
DEFINE_DEFAULT_ISR(PendSV_Handler)
DEFINE_DEFAULT_ISR(SysTick_Handler)
DEFINE_DEFAULT_ISR(WWDG_IRQHandler)
DEFINE_DEFAULT_ISR(PVD_IRQHandler)
DEFINE_DEFAULT_ISR(TAMP_STAMP_IRQHandler)
DEFINE_DEFAULT_ISR(RTC_WKUP_IRQHandler)
DEFINE_DEFAULT_ISR(FLASH_IRQHandler)
DEFINE_DEFAULT_ISR(RCC_IRQHandler)
DEFINE_DEFAULT_ISR(EXTI0_IRQHandler)
DEFINE_DEFAULT_ISR(EXTI1_IRQHandler)
DEFINE_DEFAULT_ISR(EXTI2_TSC_IRQHandler)
DEFINE_DEFAULT_ISR(EXTI3_IRQHandler)
DEFINE_DEFAULT_ISR(EXTI4_IRQHandler)
DEFINE_DEFAULT_ISR(DMA1_Channel1_IRQHandler)
DEFINE_DEFAULT_ISR(DMA1_Channel2_IRQHandler)
DEFINE_DEFAULT_ISR(DMA1_Channel3_IRQHandler)
DEFINE_DEFAULT_ISR(DMA1_Channel4_IRQHandler)
DEFINE_DEFAULT_ISR(DMA1_Channel5_IRQHandler)
DEFINE_DEFAULT_ISR(DMA1_Channel6_IRQHandler)
DEFINE_DEFAULT_ISR(DMA1_Channel7_IRQHandler)
DEFINE_DEFAULT_ISR(ADC1_2_IRQHandler)
DEFINE_DEFAULT_ISR(USB_HP_CAN_TX_IRQHandler)
DEFINE_DEFAULT_ISR(USB_LP_CAN_RX0_IRQHandler)
DEFINE_DEFAULT_ISR(CAN_RX1_IRQHandler)
DEFINE_DEFAULT_ISR(CAN_SCE_IRQHandler)
DEFINE_DEFAULT_ISR(EXTI9_5_IRQHandler)
DEFINE_DEFAULT_ISR(TIM1_BRK_TIM15_IRQHandler)
DEFINE_DEFAULT_ISR(TIM1_UP_TIM16_IRQHandler)
DEFINE_DEFAULT_ISR(TIM1_TRG_COM_TIM17_IRQHandler)
DEFINE_DEFAULT_ISR(TIM1_CC_IRQHandler)
DEFINE_DEFAULT_ISR(TIM2_IRQHandler)
DEFINE_DEFAULT_ISR(TIM3_IRQHandler)
DEFINE_DEFAULT_ISR(TIM4_IRQHandler)
DEFINE_DEFAULT_ISR(I2C1_EV_IRQHandler)
DEFINE_DEFAULT_ISR(I2C1_ER_IRQHandler)
DEFINE_DEFAULT_ISR(I2C2_EV_IRQHandler)
DEFINE_DEFAULT_ISR(I2C2_ER_IRQHandler)
DEFINE_DEFAULT_ISR(SPI1_IRQHandler)
DEFINE_DEFAULT_ISR(SPI2_IRQHandler)
DEFINE_DEFAULT_ISR(USART1_IRQHandler)
DEFINE_DEFAULT_ISR(USART2_IRQHandler)
DEFINE_DEFAULT_ISR(USART3_IRQHandler)
DEFINE_DEFAULT_ISR(EXTI15_10_IRQHandler)
DEFINE_DEFAULT_ISR(RTC_Alarm_IRQHandler)
DEFINE_DEFAULT_ISR(USBWakeUp_IRQHandler)
DEFINE_DEFAULT_ISR(TIM8_BRK_IRQHandler)
DEFINE_DEFAULT_ISR(TIM8_UP_IRQHandler)
DEFINE_DEFAULT_ISR(TIM8_TRG_COM_IRQHandler)
DEFINE_DEFAULT_ISR(TIM8_CC_IRQHandler)
DEFINE_DEFAULT_ISR(ADC3_IRQHandler)
DEFINE_DEFAULT_ISR(FMC_IRQHandler)
DEFINE_DEFAULT_ISR(SPI3_IRQHandler)
DEFINE_DEFAULT_ISR(UART4_IRQHandler)
DEFINE_DEFAULT_ISR(UART5_IRQHandler)
DEFINE_DEFAULT_ISR(TIM6_DAC_IRQHandler)
DEFINE_DEFAULT_ISR(TIM7_IRQHandler)
DEFINE_DEFAULT_ISR(DMA2_Channel1_IRQHandler)
DEFINE_DEFAULT_ISR(DMA2_Channel2_IRQHandler)
DEFINE_DEFAULT_ISR(DMA2_Channel3_IRQHandler)
DEFINE_DEFAULT_ISR(DMA2_Channel4_IRQHandler)
DEFINE_DEFAULT_ISR(DMA2_Channel5_IRQHandler)
DEFINE_DEFAULT_ISR(ADC4_IRQHandler)
DEFINE_DEFAULT_ISR(COMP1_2_3_IRQHandler)
DEFINE_DEFAULT_ISR(COMP4_5_6_IRQHandler)
DEFINE_DEFAULT_ISR(COMP7_IRQHandler)
DEFINE_DEFAULT_ISR(I2C3_EV_IRQHandler)
DEFINE_DEFAULT_ISR(I2C3_ER_IRQHandler)
DEFINE_DEFAULT_ISR(USB_HP_IRQHandler)
DEFINE_DEFAULT_ISR(USB_LP_IRQHandler)
DEFINE_DEFAULT_ISR(USBWakeUp_RMP_IRQHandler)
DEFINE_DEFAULT_ISR(TIM20_BRK_IRQHandler)
DEFINE_DEFAULT_ISR(TIM20_UP_IRQHandler)
DEFINE_DEFAULT_ISR(TIM20_TRG_COM_IRQHandler)
DEFINE_DEFAULT_ISR(TIM20_CC_IRQHandler)
DEFINE_DEFAULT_ISR(FPU_IRQHandler)
DEFINE_DEFAULT_ISR(SPI4_IRQHandler)

extern std::uint32_t _estack;
extern "C" void ResetHandler();

std::uintptr_t g_pfnVectors[] __attribute__((section(".isr_vector"))){
    // Stack Ptr initialization
    reinterpret_cast<std::uintptr_t>(&_estack),
    // Entry point
    reinterpret_cast<std::uintptr_t>(ResetHandler),
    // Exceptions
    reinterpret_cast<std::uintptr_t>(NMI_Handler),
    /* NMI_Handler
     */
    reinterpret_cast<std::uintptr_t>(HardFault_Handler),  /* HardFault_Handler */
    reinterpret_cast<std::uintptr_t>(MemManage_Handler),  /* MemManage_Handler */
    reinterpret_cast<std::uintptr_t>(BusFault_Handler),   /* BusFault_Handler */
    reinterpret_cast<std::uintptr_t>(UsageFault_Handler), /* UsageFault_Handler
                                                           */
    reinterpret_cast<std::uintptr_t>(nullptr),            /* 0 */
    reinterpret_cast<std::uintptr_t>(nullptr),            /* 0 */
    reinterpret_cast<std::uintptr_t>(nullptr),            /* 0 */
    reinterpret_cast<std::uintptr_t>(nullptr),            /* 0 */
    reinterpret_cast<std::uintptr_t>(SVC_Handler),
    /* SVC_Handler
     */
    reinterpret_cast<std::uintptr_t>(DebugMon_Handler), /* DebugMon_Handler */
    reinterpret_cast<std::uintptr_t>(nullptr),          /* 0 */
    reinterpret_cast<std::uintptr_t>(PendSV_Handler),
    /* PendSV_Handler
     */
    reinterpret_cast<std::uintptr_t>(SysTick_Handler), /* SysTick_Handler */
    reinterpret_cast<std::uintptr_t>(Interrupt::WWDG_IRQHandler),
    reinterpret_cast<std::uintptr_t>(Interrupt::PVD_IRQHandler),
    reinterpret_cast<std::uintptr_t>(Interrupt::TAMP_STAMP_IRQHandler),
    reinterpret_cast<std::uintptr_t>(Interrupt::RTC_WKUP_IRQHandler),
    reinterpret_cast<std::uintptr_t>(Interrupt::FLASH_IRQHandler),
    reinterpret_cast<std::uintptr_t>(Interrupt::RCC_IRQHandler),
    reinterpret_cast<std::uintptr_t>(Interrupt::EXTI0_IRQHandler),
    reinterpret_cast<std::uintptr_t>(Interrupt::EXTI1_IRQHandler),
    reinterpret_cast<std::uintptr_t>(Interrupt::EXTI2_TSC_IRQHandler),
    reinterpret_cast<std::uintptr_t>(Interrupt::EXTI3_IRQHandler),
    reinterpret_cast<std::uintptr_t>(Interrupt::EXTI4_IRQHandler),
    reinterpret_cast<std::uintptr_t>(Interrupt::DMA1_Channel1_IRQHandler),
    reinterpret_cast<std::uintptr_t>(Interrupt::DMA1_Channel2_IRQHandler),
    reinterpret_cast<std::uintptr_t>(Interrupt::DMA1_Channel3_IRQHandler),
    reinterpret_cast<std::uintptr_t>(Interrupt::DMA1_Channel4_IRQHandler),
    reinterpret_cast<std::uintptr_t>(Interrupt::DMA1_Channel5_IRQHandler),
    reinterpret_cast<std::uintptr_t>(Interrupt::DMA1_Channel6_IRQHandler),
    reinterpret_cast<std::uintptr_t>(Interrupt::DMA1_Channel7_IRQHandler),
    reinterpret_cast<std::uintptr_t>(Interrupt::ADC1_2_IRQHandler),
    reinterpret_cast<std::uintptr_t>(Interrupt::USB_HP_CAN_TX_IRQHandler),
    reinterpret_cast<std::uintptr_t>(Interrupt::USB_LP_CAN_RX0_IRQHandler),
    reinterpret_cast<std::uintptr_t>(Interrupt::CAN_RX1_IRQHandler),
    reinterpret_cast<std::uintptr_t>(Interrupt::CAN_SCE_IRQHandler),
    reinterpret_cast<std::uintptr_t>(Interrupt::EXTI9_5_IRQHandler),
    reinterpret_cast<std::uintptr_t>(Interrupt::TIM1_BRK_TIM15_IRQHandler),
    reinterpret_cast<std::uintptr_t>(Interrupt::TIM1_UP_TIM16_IRQHandler),
    reinterpret_cast<std::uintptr_t>(Interrupt::TIM1_TRG_COM_TIM17_IRQHandler),
    reinterpret_cast<std::uintptr_t>(Interrupt::TIM1_CC_IRQHandler),
    reinterpret_cast<std::uintptr_t>(Interrupt::TIM2_IRQHandler),
    reinterpret_cast<std::uintptr_t>(Interrupt::TIM3_IRQHandler),
    reinterpret_cast<std::uintptr_t>(Interrupt::TIM4_IRQHandler),
    reinterpret_cast<std::uintptr_t>(Interrupt::I2C1_EV_IRQHandler),
    reinterpret_cast<std::uintptr_t>(Interrupt::I2C1_ER_IRQHandler),
    reinterpret_cast<std::uintptr_t>(Interrupt::I2C2_EV_IRQHandler),
    reinterpret_cast<std::uintptr_t>(Interrupt::I2C2_ER_IRQHandler),
    reinterpret_cast<std::uintptr_t>(Interrupt::SPI1_IRQHandler),
    reinterpret_cast<std::uintptr_t>(Interrupt::SPI2_IRQHandler),
    reinterpret_cast<std::uintptr_t>(Interrupt::USART1_IRQHandler),
    reinterpret_cast<std::uintptr_t>(Interrupt::USART2_IRQHandler),
    reinterpret_cast<std::uintptr_t>(Interrupt::USART3_IRQHandler),
    reinterpret_cast<std::uintptr_t>(Interrupt::EXTI15_10_IRQHandler),
    reinterpret_cast<std::uintptr_t>(Interrupt::RTC_Alarm_IRQHandler),
    reinterpret_cast<std::uintptr_t>(Interrupt::USBWakeUp_IRQHandler),
    reinterpret_cast<std::uintptr_t>(Interrupt::TIM8_BRK_IRQHandler),
    reinterpret_cast<std::uintptr_t>(Interrupt::TIM8_UP_IRQHandler),
    reinterpret_cast<std::uintptr_t>(Interrupt::TIM8_TRG_COM_IRQHandler),
    reinterpret_cast<std::uintptr_t>(Interrupt::TIM8_CC_IRQHandler),
    reinterpret_cast<std::uintptr_t>(Interrupt::ADC3_IRQHandler),
    reinterpret_cast<std::uintptr_t>(Interrupt::FMC_IRQHandler),
    reinterpret_cast<std::uintptr_t>(nullptr),
    reinterpret_cast<std::uintptr_t>(nullptr),
    reinterpret_cast<std::uintptr_t>(Interrupt::SPI3_IRQHandler),
    reinterpret_cast<std::uintptr_t>(Interrupt::UART4_IRQHandler),
    reinterpret_cast<std::uintptr_t>(Interrupt::UART5_IRQHandler),
    reinterpret_cast<std::uintptr_t>(Interrupt::TIM6_DAC_IRQHandler),
    reinterpret_cast<std::uintptr_t>(Interrupt::TIM7_IRQHandler),
    reinterpret_cast<std::uintptr_t>(Interrupt::DMA2_Channel1_IRQHandler),
    reinterpret_cast<std::uintptr_t>(Interrupt::DMA2_Channel2_IRQHandler),
    reinterpret_cast<std::uintptr_t>(Interrupt::DMA2_Channel3_IRQHandler),
    reinterpret_cast<std::uintptr_t>(Interrupt::DMA2_Channel4_IRQHandler),
    reinterpret_cast<std::uintptr_t>(Interrupt::DMA2_Channel5_IRQHandler),
    reinterpret_cast<std::uintptr_t>(Interrupt::ADC4_IRQHandler),
    reinterpret_cast<std::uintptr_t>(nullptr),
    reinterpret_cast<std::uintptr_t>(nullptr),
    reinterpret_cast<std::uintptr_t>(Interrupt::COMP1_2_3_IRQHandler),
    reinterpret_cast<std::uintptr_t>(Interrupt::COMP4_5_6_IRQHandler),
    reinterpret_cast<std::uintptr_t>(Interrupt::COMP7_IRQHandler),
    reinterpret_cast<std::uintptr_t>(nullptr),
    reinterpret_cast<std::uintptr_t>(nullptr),
    reinterpret_cast<std::uintptr_t>(nullptr),
    reinterpret_cast<std::uintptr_t>(nullptr),
    reinterpret_cast<std::uintptr_t>(nullptr),
    reinterpret_cast<std::uintptr_t>(Interrupt::I2C3_EV_IRQHandler),
    reinterpret_cast<std::uintptr_t>(Interrupt::I2C3_ER_IRQHandler),
    reinterpret_cast<std::uintptr_t>(Interrupt::USB_HP_IRQHandler),
    reinterpret_cast<std::uintptr_t>(Interrupt::USB_LP_IRQHandler),
    reinterpret_cast<std::uintptr_t>(Interrupt::USBWakeUp_RMP_IRQHandler),
    reinterpret_cast<std::uintptr_t>(Interrupt::TIM20_BRK_IRQHandler),
    reinterpret_cast<std::uintptr_t>(Interrupt::TIM20_UP_IRQHandler),
    reinterpret_cast<std::uintptr_t>(Interrupt::TIM20_TRG_COM_IRQHandler),
    reinterpret_cast<std::uintptr_t>(Interrupt::TIM20_CC_IRQHandler),
    reinterpret_cast<std::uintptr_t>(Interrupt::FPU_IRQHandler),
    reinterpret_cast<std::uintptr_t>(nullptr),
    reinterpret_cast<std::uintptr_t>(nullptr),
    reinterpret_cast<std::uintptr_t>(Interrupt::SPI4_IRQHandler),
};

extern "C" void ResetHandler() {
  // Initialize data section
  extern std::uint8_t _sdata;
  extern std::uint8_t _edata;
  extern std::uint8_t _etext;
  std::size_t size = static_cast<size_t>(&_edata - &_sdata);
  std::copy(&_etext, &_etext + size, &_sdata);

  // Initialize bss section
  extern std::uint8_t _sbss;
  extern std::uint8_t _ebss;
  std::fill(&_sbss, &_ebss, UINT8_C(0x00));

  /* Call the clock system intitialization function.*/
  asm("bl SystemInit");
  /* Call static constructors */
  asm("bl __libc_init_array");
  /* Call the application's entry point.*/
  asm("bl main");
}