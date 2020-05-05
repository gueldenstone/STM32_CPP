/**
 * @file: stm32f303xe_it.hpp
 *
 * @date: 2020-05-02
 *
 * @author: Lukas Güldenstein
 */

#ifndef _ISR_HPP
#define _ISR_HPP

#ifdef STM32F303xE
#define MAX_INTERRUPTS 100
#include "stm32f3xx.h"
#endif

class Interrupt {
 public:
  // Constructor
  Interrupt();
  // Register function
  static void Register(IRQn_Type interrupt_number, Interrupt* intThisPtr);
  // ISR functions
  static void __attribute__((weak)) WWDG_IRQHandler(void);
  static void __attribute__((weak)) PVD_IRQHandler(void);
  static void __attribute__((weak)) TAMP_STAMP_IRQHandler(void);
  static void __attribute__((weak)) RTC_WKUP_IRQHandler(void);
  static void __attribute__((weak)) FLASH_IRQHandler(void);
  static void __attribute__((weak)) RCC_IRQHandler(void);
  static void __attribute__((weak)) EXTI0_IRQHandler(void);
  static void __attribute__((weak)) EXTI1_IRQHandler(void);
  static void __attribute__((weak)) EXTI2_TSC_IRQHandler(void);
  static void __attribute__((weak)) EXTI3_IRQHandler(void);
  static void __attribute__((weak)) EXTI4_IRQHandler(void);
  static void __attribute__((weak)) DMA1_Channel1_IRQHandler(void);
  static void __attribute__((weak)) DMA1_Channel2_IRQHandler(void);
  static void __attribute__((weak)) DMA1_Channel3_IRQHandler(void);
  static void __attribute__((weak)) DMA1_Channel4_IRQHandler(void);
  static void __attribute__((weak)) DMA1_Channel5_IRQHandler(void);
  static void __attribute__((weak)) DMA1_Channel6_IRQHandler(void);
  static void __attribute__((weak)) DMA1_Channel7_IRQHandler(void);
  static void __attribute__((weak)) ADC1_2_IRQHandler(void);
  static void __attribute__((weak)) USB_HP_CAN_TX_IRQHandler(void);
  static void __attribute__((weak)) USB_LP_CAN_RX0_IRQHandler(void);
  static void __attribute__((weak)) CAN_RX1_IRQHandler(void);
  static void __attribute__((weak)) CAN_SCE_IRQHandler(void);
  static void __attribute__((weak)) EXTI9_5_IRQHandler(void);
  static void __attribute__((weak)) TIM1_BRK_TIM15_IRQHandler(void);
  static void __attribute__((weak)) TIM1_UP_TIM16_IRQHandler(void);
  static void __attribute__((weak)) TIM1_TRG_COM_TIM17_IRQHandler(void);
  static void __attribute__((weak)) TIM1_CC_IRQHandler(void);
  static void __attribute__((weak)) TIM2_IRQHandler(void);
  static void __attribute__((weak)) TIM3_IRQHandler(void);
  static void __attribute__((weak)) TIM4_IRQHandler(void);
  static void __attribute__((weak)) I2C1_EV_IRQHandler(void);
  static void __attribute__((weak)) I2C1_ER_IRQHandler(void);
  static void __attribute__((weak)) I2C2_EV_IRQHandler(void);
  static void __attribute__((weak)) I2C2_ER_IRQHandler(void);
  static void __attribute__((weak)) SPI1_IRQHandler(void);
  static void __attribute__((weak)) SPI2_IRQHandler(void);
  static void __attribute__((weak)) USART1_IRQHandler(void);
  static void __attribute__((weak)) USART2_IRQHandler(void);
  static void __attribute__((weak)) USART3_IRQHandler(void);
  static void __attribute__((weak)) EXTI15_10_IRQHandler(void);
  static void __attribute__((weak)) RTC_Alarm_IRQHandler(void);
  static void __attribute__((weak)) USBWakeUp_IRQHandler(void);
  static void __attribute__((weak)) TIM8_BRK_IRQHandler(void);
  static void __attribute__((weak)) TIM8_UP_IRQHandler(void);
  static void __attribute__((weak)) TIM8_TRG_COM_IRQHandler(void);
  static void __attribute__((weak)) TIM8_CC_IRQHandler(void);
  static void __attribute__((weak)) ADC3_IRQHandler(void);
  static void __attribute__((weak)) FMC_IRQHandler(void);
  static void __attribute__((weak)) SPI3_IRQHandler(void);
  static void __attribute__((weak)) UART4_IRQHandler(void);
  static void __attribute__((weak)) UART5_IRQHandler(void);
  static void __attribute__((weak)) TIM6_DAC_IRQHandler(void);
  static void __attribute__((weak)) TIM7_IRQHandler(void);
  static void __attribute__((weak)) DMA2_Channel1_IRQHandler(void);
  static void __attribute__((weak)) DMA2_Channel2_IRQHandler(void);
  static void __attribute__((weak)) DMA2_Channel3_IRQHandler(void);
  static void __attribute__((weak)) DMA2_Channel4_IRQHandler(void);
  static void __attribute__((weak)) DMA2_Channel5_IRQHandler(void);
  static void __attribute__((weak)) ADC4_IRQHandler(void);
  static void __attribute__((weak)) COMP1_2_3_IRQHandler(void);
  static void __attribute__((weak)) COMP4_5_6_IRQHandler(void);
  static void __attribute__((weak)) COMP7_IRQHandler(void);
  static void __attribute__((weak)) I2C3_EV_IRQHandler(void);
  static void __attribute__((weak)) I2C3_ER_IRQHandler(void);
  static void __attribute__((weak)) USB_HP_IRQHandler(void);
  static void __attribute__((weak)) USB_LP_IRQHandler(void);
  static void __attribute__((weak)) USBWakeUp_RMP_IRQHandler(void);
  static void __attribute__((weak)) TIM20_BRK_IRQHandler(void);
  static void __attribute__((weak)) TIM20_UP_IRQHandler(void);
  static void __attribute__((weak)) TIM20_TRG_COM_IRQHandler(void);
  static void __attribute__((weak)) TIM20_CC_IRQHandler(void);
  static void __attribute__((weak)) FPU_IRQHandler(void);
  static void __attribute__((weak)) SPI4_IRQHandler(void);

  virtual void ISR(void) = 0;

 private:
  static Interrupt* ISRVectorTable[MAX_INTERRUPTS - NVIC_USER_IRQ_OFFSET];
};
#endif /* _ISR_HPP */