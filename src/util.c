/**
 * @file: util.c
 *
 * @date: 2020-04-25
 *
 * @author: Lukas Güldenstein
 *
 * @brief: Utility Functions (Delay,...)
 */

/* -------------------------------- includes -------------------------------- */
#include "util.h"

/* -------------------------------- functions ------------------------------- */
/**
 * @brief Initialize Clock with 72Mhz
 */
void setupClock(void) {
  /* PLL Config */
  RCC->CR &= ~(RCC_CR_PLLON);  // Deactivate PLL
  while (RCC->CR & RCC_CR_PLLRDY) {
  }  // Wait for PLL to stop
     /* Set PLL to input HSI, Multiplicator = 9 => HCLK=72MHz */
  RCC->CFGR |= RCC_CFGR_PLLSRC_HSI_PREDIV | RCC_CFGR_PLLMUL9;
  RCC->CR |= RCC_CR_PLLON;  // Activate PLL
  while (!(RCC->CR & RCC_CR_PLLRDY)) {
    ;
  }  // Wait for PLL to lock

  /*FLASH wait states */
  FLASH->ACR &= ~(FLASH_ACR_LATENCY_Msk);        // Reset Flash Wait states
  FLASH->ACR |= 0b010 << FLASH_ACR_LATENCY_Pos;  // Set Flash wait states to 2

  /*SysClock anpassen */
  RCC->CFGR |= RCC_CFGR_PPRE1_DIV2;  // PreDiv for ABP1 /2 (ABP1 36MHz max)
  RCC->CFGR |= RCC_CFGR_SW_PLL;      // Set PLL as Sysclock
  while ((RCC->CFGR & RCC_CFGR_SWS) != RCC_CFGR_SWS_PLL) {
  }  // Wait for switch to PLL as clock source

  SystemCoreClockUpdate();

  /* Other */
  RCC->APB2ENR |= RCC_APB2ENR_SYSCFGEN;  // Clock to SYSCFG
}

/**
 * @brief Initialize Delay Timer with TIM7
 */
void initDelay(void) {
  RCC->APB1ENR |= RCC_APB1ENR_TIM7EN;         // enable Clock for TIM7
  TIM7->PSC = (SystemCoreClock / 10000) - 1;  // prescaler for ARR in ms
  TIM7->ARR = 0;
  TIM7->CR1 |= TIM_CR1_OPM;    // Enable one-pulse Mode
  TIM7->DIER |= TIM_DIER_UIE;  // Enable Interrupt on Update
  TIM7->CR1 &= ~TIM_CR1_CEN;   // disable Timer
  NVIC_EnableIRQ(TIM7_IRQn);
}
/**
 * @brief: lala
 *
 * @note: lalala
 *
 * @param: param1, param 2
 *
 * @retval none
 */
extern volatile int done;
// void delay(uint32_t ms) {
//   done = 0;
//   TIM7->ARR = ms;
//   TIM7->CR1 |= TIM_CR1_CEN;
//   while (!done) {
//     ;
//   }
// }