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

#include <cstddef>

#include "gpio.hpp"
#include "util.h"
/* -------------------------------------------------------------------------- */

/* ----------------------------- project defines ---------------------------- */
#define LED_BANK (GPIOA)
#define LED_PIN (5)
#define DEBUG 1
/* -------------------------------------------------------------------------- */

/* --------------------------- peripheral structs --------------------------- */
pGPIO led_gpio;
pGPIO_pin board_led;
/* -------------------------------------------------------------------------- */

volatile int done = 0;
/* -------------------------------- functions ------------------------------- */
int main() {
  // setupClock();
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
extern "C" {
void TIM7_IRQHandler(void) {
  done = 1;
  TIM7->SR &= ~TIM_SR_UIF;
}
}
