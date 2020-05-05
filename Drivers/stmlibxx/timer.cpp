/**
 * @file: timer.cpp
 *
 * @date: 2020-05-02
 *
 * @author: Lukas Güldenstein
 *
 * @brief: Driver for Timer Peripheral in C++
 */

/* -------------------------------- includes -------------------------------- */
#include "timer.hpp"

// #include <stdlib.h>

/* --------------------- Timer peripherial class methods -------------------- */

// Default Constructor for Timer class
Timer::Timer(void) { InterruptPtr = new TimerInterrupt(this); }

// Default Constructor for TimerInterrupt class
TimerInterrupt::TimerInterrupt(Timer* owner) {
  InterruptOwnerPtr = owner;
  // Allows interrupt to access owner's data
  Interrupt::Register(TIM7_IRQn, this);
}

void TimerInterrupt::ISR(void) {
  extern volatile int done;
  done = 1;
  InterruptOwnerPtr->Count = InterruptOwnerPtr->Count + 1;
  TIM7->SR &= ~TIM_SR_UIF;
}