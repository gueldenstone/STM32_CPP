/**
 * @file: isr.cpp
 *
 * @date: 2020-05-03
 *
 * @author: Lukas Güldenstein
 *
 * @brief: Functions for Interrupts
 */

/* -------------------------------- includes -------------------------------- */
#include "stm32f303xe_it.hpp"
Interrupt::Interrupt() {}

Interrupt *Interrupt::ISRVectorTable[];

// Static Member Functions of Interrupt Class calling registerd function of
// other classes
void Interrupt::WWDG_IRQHandler(void) { ISRVectorTable[WWDG_IRQn]->ISR(); }
void Interrupt::PVD_IRQHandler(void) { ISRVectorTable[PVD_IRQn]->ISR(); }
void Interrupt::TAMP_STAMP_IRQHandler(void) { ISRVectorTable[TAMP_STAMP_IRQn]->ISR(); }
void Interrupt::RTC_WKUP_IRQHandler(void) { ISRVectorTable[RTC_WKUP_IRQn]->ISR(); }
void Interrupt::FLASH_IRQHandler(void) { ISRVectorTable[FLASH_IRQn]->ISR(); }
void Interrupt::RCC_IRQHandler(void) { ISRVectorTable[RCC_IRQn]->ISR(); }
void Interrupt::EXTI0_IRQHandler(void) { ISRVectorTable[EXTI0_IRQn]->ISR(); }
void Interrupt::EXTI1_IRQHandler(void) { ISRVectorTable[EXTI1_IRQn]->ISR(); }
void Interrupt::EXTI2_TSC_IRQHandler(void) { ISRVectorTable[EXTI2_TSC_IRQn]->ISR(); }
void Interrupt::EXTI3_IRQHandler(void) { ISRVectorTable[EXTI3_IRQn]->ISR(); }
void Interrupt::EXTI4_IRQHandler(void) { ISRVectorTable[EXTI4_IRQn]->ISR(); }
void Interrupt::DMA1_Channel1_IRQHandler(void) { ISRVectorTable[DMA1_Channel1_IRQn]->ISR(); }
void Interrupt::DMA1_Channel2_IRQHandler(void) { ISRVectorTable[DMA1_Channel2_IRQn]->ISR(); }
void Interrupt::DMA1_Channel3_IRQHandler(void) { ISRVectorTable[DMA1_Channel3_IRQn]->ISR(); }
void Interrupt::DMA1_Channel4_IRQHandler(void) { ISRVectorTable[DMA1_Channel4_IRQn]->ISR(); }
void Interrupt::DMA1_Channel5_IRQHandler(void) { ISRVectorTable[DMA1_Channel5_IRQn]->ISR(); }
void Interrupt::DMA1_Channel6_IRQHandler(void) { ISRVectorTable[DMA1_Channel6_IRQn]->ISR(); }
void Interrupt::DMA1_Channel7_IRQHandler(void) { ISRVectorTable[DMA1_Channel7_IRQn]->ISR(); }
void Interrupt::ADC1_2_IRQHandler(void) { ISRVectorTable[ADC1_2_IRQn]->ISR(); }
void Interrupt::USB_HP_CAN_TX_IRQHandler(void) { ISRVectorTable[USB_HP_CAN_TX_IRQn]->ISR(); }
void Interrupt::USB_LP_CAN_RX0_IRQHandler(void) { ISRVectorTable[USB_LP_CAN_RX0_IRQn]->ISR(); }
void Interrupt::CAN_RX1_IRQHandler(void) { ISRVectorTable[CAN_RX1_IRQn]->ISR(); }
void Interrupt::CAN_SCE_IRQHandler(void) { ISRVectorTable[CAN_SCE_IRQn]->ISR(); }
void Interrupt::EXTI9_5_IRQHandler(void) { ISRVectorTable[EXTI9_5_IRQn]->ISR(); }
void Interrupt::TIM1_BRK_TIM15_IRQHandler(void) { ISRVectorTable[TIM1_BRK_TIM15_IRQn]->ISR(); }
void Interrupt::TIM1_UP_TIM16_IRQHandler(void) { ISRVectorTable[TIM1_UP_TIM16_IRQn]->ISR(); }
void Interrupt::TIM1_TRG_COM_TIM17_IRQHandler(void) { ISRVectorTable[TIM1_TRG_COM_TIM17_IRQn]->ISR(); }
void Interrupt::TIM1_CC_IRQHandler(void) { ISRVectorTable[TIM1_CC_IRQn]->ISR(); }
void Interrupt::TIM2_IRQHandler(void) { ISRVectorTable[TIM2_IRQn]->ISR(); }
void Interrupt::TIM3_IRQHandler(void) { ISRVectorTable[TIM3_IRQn]->ISR(); }
void Interrupt::TIM4_IRQHandler(void) { ISRVectorTable[TIM4_IRQn]->ISR(); }
void Interrupt::I2C1_EV_IRQHandler(void) { ISRVectorTable[I2C1_EV_IRQn]->ISR(); }
void Interrupt::I2C1_ER_IRQHandler(void) { ISRVectorTable[I2C1_ER_IRQn]->ISR(); }
void Interrupt::I2C2_EV_IRQHandler(void) { ISRVectorTable[I2C2_EV_IRQn]->ISR(); }
void Interrupt::I2C2_ER_IRQHandler(void) { ISRVectorTable[I2C2_ER_IRQn]->ISR(); }
void Interrupt::SPI1_IRQHandler(void) { ISRVectorTable[SPI1_IRQn]->ISR(); }
void Interrupt::SPI2_IRQHandler(void) { ISRVectorTable[SPI2_IRQn]->ISR(); }
void Interrupt::USART1_IRQHandler(void) { ISRVectorTable[USART1_IRQn]->ISR(); }
void Interrupt::USART2_IRQHandler(void) { ISRVectorTable[USART2_IRQn]->ISR(); }
void Interrupt::USART3_IRQHandler(void) { ISRVectorTable[USART3_IRQn]->ISR(); }
void Interrupt::EXTI15_10_IRQHandler(void) { ISRVectorTable[EXTI15_10_IRQn]->ISR(); }
void Interrupt::RTC_Alarm_IRQHandler(void) { ISRVectorTable[RTC_Alarm_IRQn]->ISR(); }
void Interrupt::USBWakeUp_IRQHandler(void) { ISRVectorTable[USBWakeUp_IRQn]->ISR(); }
void Interrupt::TIM8_BRK_IRQHandler(void) { ISRVectorTable[TIM8_BRK_IRQn]->ISR(); }
void Interrupt::TIM8_UP_IRQHandler(void) { ISRVectorTable[TIM8_UP_IRQn]->ISR(); }
void Interrupt::TIM8_TRG_COM_IRQHandler(void) { ISRVectorTable[TIM8_TRG_COM_IRQn]->ISR(); }
void Interrupt::TIM8_CC_IRQHandler(void) { ISRVectorTable[TIM8_CC_IRQn]->ISR(); }
void Interrupt::ADC3_IRQHandler(void) { ISRVectorTable[ADC3_IRQn]->ISR(); }
void Interrupt::FMC_IRQHandler(void) { ISRVectorTable[FMC_IRQn]->ISR(); }
void Interrupt::SPI3_IRQHandler(void) { ISRVectorTable[SPI3_IRQn]->ISR(); }
void Interrupt::UART4_IRQHandler(void) { ISRVectorTable[UART4_IRQn]->ISR(); }
void Interrupt::UART5_IRQHandler(void) { ISRVectorTable[UART5_IRQn]->ISR(); }
void Interrupt::TIM6_DAC_IRQHandler(void) { ISRVectorTable[TIM6_DAC_IRQn]->ISR(); }
void Interrupt::TIM7_IRQHandler(void) { ISRVectorTable[TIM7_IRQn]->ISR(); }
void Interrupt::DMA2_Channel1_IRQHandler(void) { ISRVectorTable[DMA2_Channel1_IRQn]->ISR(); }
void Interrupt::DMA2_Channel2_IRQHandler(void) { ISRVectorTable[DMA2_Channel2_IRQn]->ISR(); }
void Interrupt::DMA2_Channel3_IRQHandler(void) { ISRVectorTable[DMA2_Channel3_IRQn]->ISR(); }
void Interrupt::DMA2_Channel4_IRQHandler(void) { ISRVectorTable[DMA2_Channel4_IRQn]->ISR(); }
void Interrupt::DMA2_Channel5_IRQHandler(void) { ISRVectorTable[DMA2_Channel5_IRQn]->ISR(); }
void Interrupt::ADC4_IRQHandler(void) { ISRVectorTable[ADC4_IRQn]->ISR(); }
void Interrupt::COMP1_2_3_IRQHandler(void) { ISRVectorTable[COMP1_2_3_IRQn]->ISR(); }
void Interrupt::COMP4_5_6_IRQHandler(void) { ISRVectorTable[COMP4_5_6_IRQn]->ISR(); }
void Interrupt::COMP7_IRQHandler(void) { ISRVectorTable[COMP7_IRQn]->ISR(); }
void Interrupt::I2C3_EV_IRQHandler(void) { ISRVectorTable[I2C3_EV_IRQn]->ISR(); }
void Interrupt::I2C3_ER_IRQHandler(void) { ISRVectorTable[I2C3_ER_IRQn]->ISR(); }
void Interrupt::USB_HP_IRQHandler(void) { ISRVectorTable[USB_HP_IRQn]->ISR(); }
void Interrupt::USB_LP_IRQHandler(void) { ISRVectorTable[USB_LP_IRQn]->ISR(); }
void Interrupt::USBWakeUp_RMP_IRQHandler(void) { ISRVectorTable[USBWakeUp_RMP_IRQn]->ISR(); }
void Interrupt::TIM20_BRK_IRQHandler(void) { ISRVectorTable[TIM20_BRK_IRQn]->ISR(); }
void Interrupt::TIM20_UP_IRQHandler(void) { ISRVectorTable[TIM20_UP_IRQn]->ISR(); }
void Interrupt::TIM20_TRG_COM_IRQHandler(void) { ISRVectorTable[TIM20_TRG_COM_IRQn]->ISR(); }
void Interrupt::TIM20_CC_IRQHandler(void) { ISRVectorTable[TIM20_CC_IRQn]->ISR(); }
void Interrupt::FPU_IRQHandler(void) { ISRVectorTable[FPU_IRQn]->ISR(); }
void Interrupt::SPI4_IRQHandler(void) { ISRVectorTable[SPI4_IRQn]->ISR(); }

// Register method
void Interrupt::Register(IRQn_Type interrupt_number, Interrupt *intThisPtr) {
  ISRVectorTable[interrupt_number] = intThisPtr;
}