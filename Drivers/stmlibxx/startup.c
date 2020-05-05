#include "stm32f3xx.h"

/*
 * Define some attributes to attach to force functions
 * or other objects into certain specific locations.
 * These section names are defined in the linker script.
 */
#define SECT_VECTABLE __attribute__((section(".isr_vector"), __used__))
#define WEAK __attribute__((weak))
#define NAKED __attribute__((naked))

/**
 * Symbols defined by linker script.
 */
extern volatile uint32_t _sidata[], _sdata[], _edata[], _sbss[], _ebss[],
    _estack[];

/**
 * Reference to main.
 */
extern int main(void);

/**
 * SystemCoreClock must exist
 */
uint32_t SystemCoreClock;

/**
 * Prototype of the SystemInit
 */
WEAK void SystemInit(void);
WEAK void SystemCoreClockUpdate(void);
WEAK void __libc_init_array(void);

/**
 * Initialize bss section with zero and initialize the data section.
 */

static void ram_init(void) {
  for (volatile uint32_t* dest = _sbss; dest < _ebss; ++dest) {
    *dest = 0;
  }

  uint32_t* src = _sidata;
  for (uint32_t* dest = _sdata; dest < _edata; ++dest) {
    *dest = *src++;
  }
}

NAKED void Reset_Handler(void) {
  asm("bl  ram_init" ::"i"(ram_init));
  asm("bl  SystemInit" ::"i"(SystemInit));
  asm("bl  __libc_init_array" ::"i"(__libc_init_array));
  asm("bl  main" ::"i"(main));
  while (1)
    ;
}

WEAK void Default_Handler(void) {
  while (1)
    ;
}
// NAKED void Reset_Handler() {
//   memcpy(&_sdata, &_sidata, &_edata - &_sdata);
//   memset(&_sbss, 0, &_ebss - &_sbss);
//   __libc_init_array();
//   main();
// }

/**
 * Declare weak symbols with the names of all handlers. This does not yet
 * produce any code, its just a bunch of declarations of aliases that all
 * point to the same empty default handler. The application can define
 * functions with these names in which case the linker will replace the
 * the weak aliases with these existing functions.
 */
#define WEAK_DEFAULT __attribute__((weak, alias("Default_Handler")))
WEAK_DEFAULT void NMI_Handler(void);
WEAK_DEFAULT void HardFault_Handler(void);
WEAK_DEFAULT void MemManage_Handler(void);
WEAK_DEFAULT void BusFault_Handler(void);
WEAK_DEFAULT void UsageFault_Handler(void);
WEAK_DEFAULT void SVC_Handler(void);
WEAK_DEFAULT void DebugMon_Handler(void);
WEAK_DEFAULT void PendSV_Handler(void);
WEAK_DEFAULT void SysTick_Handler(void);
WEAK_DEFAULT void WWDG_IRQHandler(void);
WEAK_DEFAULT void PVD_IRQHandler(void);
WEAK_DEFAULT void TAMP_STAMP_IRQHandler(void);
WEAK_DEFAULT void RTC_WKUP_IRQHandler(void);
WEAK_DEFAULT void FLASH_IRQHandler(void);
WEAK_DEFAULT void RCC_IRQHandler(void);
WEAK_DEFAULT void EXTI0_IRQHandler(void);
WEAK_DEFAULT void EXTI1_IRQHandler(void);
WEAK_DEFAULT void EXTI2_TSC_IRQHandler(void);
WEAK_DEFAULT void EXTI3_IRQHandler(void);
WEAK_DEFAULT void EXTI4_IRQHandler(void);
WEAK_DEFAULT void DMA1_Channel1_IRQHandler(void);
WEAK_DEFAULT void DMA1_Channel2_IRQHandler(void);
WEAK_DEFAULT void DMA1_Channel3_IRQHandler(void);
WEAK_DEFAULT void DMA1_Channel4_IRQHandler(void);
WEAK_DEFAULT void DMA1_Channel5_IRQHandler(void);
WEAK_DEFAULT void DMA1_Channel6_IRQHandler(void);
WEAK_DEFAULT void DMA1_Channel7_IRQHandler(void);
WEAK_DEFAULT void ADC1_2_IRQHandler(void);
WEAK_DEFAULT void USB_HP_CAN_TX_IRQHandler(void);
WEAK_DEFAULT void USB_LP_CAN_RX0_IRQHandler(void);
WEAK_DEFAULT void CAN_RX1_IRQHandler(void);
WEAK_DEFAULT void CAN_SCE_IRQHandler(void);
WEAK_DEFAULT void EXTI9_5_IRQHandler(void);
WEAK_DEFAULT void TIM1_BRK_TIM15_IRQHandler(void);
WEAK_DEFAULT void TIM1_UP_TIM16_IRQHandler(void);
WEAK_DEFAULT void TIM1_TRG_COM_TIM17_IRQHandler(void);
WEAK_DEFAULT void TIM1_CC_IRQHandler(void);
WEAK_DEFAULT void TIM2_IRQHandler(void);
WEAK_DEFAULT void TIM3_IRQHandler(void);
WEAK_DEFAULT void TIM4_IRQHandler(void);
WEAK_DEFAULT void I2C1_EV_IRQHandler(void);
WEAK_DEFAULT void I2C1_ER_IRQHandler(void);
WEAK_DEFAULT void I2C2_EV_IRQHandler(void);
WEAK_DEFAULT void I2C2_ER_IRQHandler(void);
WEAK_DEFAULT void SPI1_IRQHandler(void);
WEAK_DEFAULT void SPI2_IRQHandler(void);
WEAK_DEFAULT void USART1_IRQHandler(void);
WEAK_DEFAULT void USART2_IRQHandler(void);
WEAK_DEFAULT void USART3_IRQHandler(void);
WEAK_DEFAULT void EXTI15_10_IRQHandler(void);
WEAK_DEFAULT void RTC_Alarm_IRQHandler(void);
WEAK_DEFAULT void USBWakeUp_IRQHandler(void);
WEAK_DEFAULT void TIM8_BRK_IRQHandler(void);
WEAK_DEFAULT void TIM8_UP_IRQHandler(void);
WEAK_DEFAULT void TIM8_TRG_COM_IRQHandler(void);
WEAK_DEFAULT void TIM8_CC_IRQHandler(void);
WEAK_DEFAULT void ADC3_IRQHandler(void);
WEAK_DEFAULT void FMC_IRQHandler(void);
WEAK_DEFAULT void SPI3_IRQHandler(void);
WEAK_DEFAULT void UART4_IRQHandler(void);
WEAK_DEFAULT void UART5_IRQHandler(void);
WEAK_DEFAULT void TIM6_DAC_IRQHandler(void);
WEAK_DEFAULT void TIM7_IRQHandler(void);
WEAK_DEFAULT void DMA2_Channel1_IRQHandler(void);
WEAK_DEFAULT void DMA2_Channel2_IRQHandler(void);
WEAK_DEFAULT void DMA2_Channel3_IRQHandler(void);
WEAK_DEFAULT void DMA2_Channel4_IRQHandler(void);
WEAK_DEFAULT void DMA2_Channel5_IRQHandler(void);
WEAK_DEFAULT void ADC4_IRQHandler(void);
WEAK_DEFAULT void COMP1_2_3_IRQHandler(void);
WEAK_DEFAULT void COMP4_5_6_IRQHandler(void);
WEAK_DEFAULT void COMP7_IRQHandler(void);
WEAK_DEFAULT void I2C3_EV_IRQHandler(void);
WEAK_DEFAULT void I2C3_ER_IRQHandler(void);
WEAK_DEFAULT void USB_HP_IRQHandler(void);
WEAK_DEFAULT void USB_LP_IRQHandler(void);
WEAK_DEFAULT void USBWakeUp_RMP_IRQHandler(void);
WEAK_DEFAULT void TIM20_BRK_IRQHandler(void);
WEAK_DEFAULT void TIM20_UP_IRQHandler(void);
WEAK_DEFAULT void TIM20_TRG_COM_IRQHandler(void);
WEAK_DEFAULT void TIM20_CC_IRQHandler(void);
WEAK_DEFAULT void FPU_IRQHandler(void);
WEAK_DEFAULT void SPI4_IRQHandler(void);

typedef struct {
  uint32_t* initial_stack;
  void (*vectors[])(void);
} vector_table_t;

SECT_VECTABLE const vector_table_t __vector_table = {
    .initial_stack = _estack,
    .vectors = {
        Reset_Handler,
        NMI_Handler,
        HardFault_Handler,
        MemManage_Handler,
        BusFault_Handler,
        UsageFault_Handler,
        0,
        0,
        0,
        0,
        SVC_Handler,
        DebugMon_Handler,
        0,
        PendSV_Handler,
        SysTick_Handler,
        WWDG_IRQHandler,
        PVD_IRQHandler,
        TAMP_STAMP_IRQHandler,
        RTC_WKUP_IRQHandler,
        FLASH_IRQHandler,
        RCC_IRQHandler,
        EXTI0_IRQHandler,
        EXTI1_IRQHandler,
        EXTI2_TSC_IRQHandler,
        EXTI3_IRQHandler,
        EXTI4_IRQHandler,
        DMA1_Channel1_IRQHandler,
        DMA1_Channel2_IRQHandler,
        DMA1_Channel3_IRQHandler,
        DMA1_Channel4_IRQHandler,
        DMA1_Channel5_IRQHandler,
        DMA1_Channel6_IRQHandler,
        DMA1_Channel7_IRQHandler,
        ADC1_2_IRQHandler,
        USB_HP_CAN_TX_IRQHandler,
        USB_LP_CAN_RX0_IRQHandler,
        CAN_RX1_IRQHandler,
        CAN_SCE_IRQHandler,
        EXTI9_5_IRQHandler,
        TIM1_BRK_TIM15_IRQHandler,
        TIM1_UP_TIM16_IRQHandler,
        TIM1_TRG_COM_TIM17_IRQHandler,
        TIM1_CC_IRQHandler,
        TIM2_IRQHandler,
        TIM3_IRQHandler,
        TIM4_IRQHandler,
        I2C1_EV_IRQHandler,
        I2C1_ER_IRQHandler,
        I2C2_EV_IRQHandler,
        I2C2_ER_IRQHandler,
        SPI1_IRQHandler,
        SPI2_IRQHandler,
        USART1_IRQHandler,
        USART2_IRQHandler,
        USART3_IRQHandler,
        EXTI15_10_IRQHandler,
        RTC_Alarm_IRQHandler,
        USBWakeUp_IRQHandler,
        TIM8_BRK_IRQHandler,
        TIM8_UP_IRQHandler,
        TIM8_TRG_COM_IRQHandler,
        TIM8_CC_IRQHandler,
        ADC3_IRQHandler,
        FMC_IRQHandler,
        0,
        0,
        SPI3_IRQHandler,
        UART4_IRQHandler,
        UART5_IRQHandler,
        TIM6_DAC_IRQHandler,
        TIM7_IRQHandler,
        DMA2_Channel1_IRQHandler,
        DMA2_Channel2_IRQHandler,
        DMA2_Channel3_IRQHandler,
        DMA2_Channel4_IRQHandler,
        DMA2_Channel5_IRQHandler,
        ADC4_IRQHandler,
        0,
        0,
        COMP1_2_3_IRQHandler,
        COMP4_5_6_IRQHandler,
        COMP7_IRQHandler,
        0,
        0,
        0,
        0,
        0,
        I2C3_EV_IRQHandler,
        I2C3_ER_IRQHandler,
        USB_HP_IRQHandler,
        USB_LP_IRQHandler,
        USBWakeUp_RMP_IRQHandler,
        TIM20_BRK_IRQHandler,
        TIM20_UP_IRQHandler,
        TIM20_TRG_COM_IRQHandler,
        TIM20_CC_IRQHandler,
        FPU_IRQHandler,
        0,
        0,
        SPI4_IRQHandler,
    }};