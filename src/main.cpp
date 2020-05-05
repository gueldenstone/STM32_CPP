/**
 * @file: main.cpp
 *
 * @date: 2020-04-24
 *
 * @author: Lukas Güldenstein
 *
 * @brief: brief description of the files contents
 */

/* -------------------------------- includes -------------------------------- */
#include "main.hpp"

// #include <cstddef>
#include <cstdio>
#include <cstdlib>

#include "gpio.hpp"
#include "stm32f303xe_it.hpp"
#include "timer.hpp"
#include "util.h"
/* -------------------------------------------------------------------------- */

/* ----------------------------- project defines ---------------------------- */
#define LED_BANK (GPIOA)
#define LED_PIN (5)
#define DEBUG 1
// #define VECT_TAB_SRAM
/* -------------------------------------------------------------------------- */

/* --------------------------- peripheral structs --------------------------- */
pGPIO led_gpio;
pGPIO_pin board_led;
// TimerInterrupt timer7interrupt;
Timer timer7;
/* -------------------------------------------------------------------------- */

volatile int done = 0;
/* -------------------------------- functions ------------------------------- */

int main() {
  setupClock();
  initDelay();
  // initialize the LED pin's GPIO bank
  led_gpio = pGPIO(LED_BANK);
  led_gpio.clock_en();
  // initialize the LED pin
  board_led = pGPIO_pin(&led_gpio, LED_PIN, pGPIO_OUT_PP);
  while (1) {
    board_led.toggle();
    delay(250);
  }
}

void delay(uint32_t ms) {
  done = 0;
  TIM7->ARR = ms * 10;
  TIM7->CR1 |= TIM_CR1_CEN;
  while (!done) {
    ;
  }
}
extern "C" {
void TIM7_IRQHandler(void) {
  extern volatile int done;
  done = 1;
  TIM7->SR &= ~TIM_SR_UIF;
}
}