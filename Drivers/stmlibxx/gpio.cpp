/**
 * @file: gpio.cpp
 *
 * @date: 2020-04-24
 *
 * @author: Lukas Güldenstein
 *
 * @brief: Implementation of the GPIO specific functions
 */

/* -------------------------------- includes -------------------------------- */
#include "gpio.hpp"
/* -------------------------------------------------------------------------- */

/* --------------------- GPIO peripheral class methods. --------------------- */
// Default constructor.
pGPIO::pGPIO() {}

// Convenience initialization constructor.
pGPIO::pGPIO(GPIO_TypeDef* bank) {
  gpio = bank;
  // Gather required register addresses for the GPIO bank.
#ifdef GPIOA
  if (bank == GPIOA) {
    enable_reg = &(RCC->AHBENR);
    enable_bit = RCC_AHBENR_GPIOAEN;
    reset_reg = &(RCC->AHBENR);
    reset_bit = RCC_AHBRSTR_GPIOARST;
  }
#endif
#ifdef GPIOB
  else if (bank == GPIOB) {
    enable_reg = &(RCC->AHBENR);
    enable_bit = RCC_AHBENR_GPIOBEN;
    reset_reg = &(RCC->AHBENR);
    reset_bit = RCC_AHBRSTR_GPIOBRST;
  }
#endif
#ifdef GPIOC
  else if (bank == GPIOC) {
    enable_reg = &(RCC->AHBENR);
    enable_bit = RCC_AHBENR_GPIOCEN;
    reset_reg = &(RCC->AHBENR);
    reset_bit = RCC_AHBRSTR_GPIOCRST;
  }
#endif
#ifdef GPIOD
  else if (bank == GPIOD) {
    enable_reg = &(RCC->AHBENR);
    enable_bit = RCC_AHBENR_GPIODEN;
    reset_reg = &(RCC->AHBENR);
    reset_bit = RCC_AHBRSTR_GPIODRST;
  }
#endif
#ifdef GPIOE
  else if (bank == GPIOE) {
    enable_reg = &(RCC->AHBENR);
    enable_bit = RCC_AHBENR_GPIOEEN;
    reset_reg = &(RCC->AHBENR);
    reset_bit = RCC_AHBRSTR_GPIOERST;
  }
#endif
#ifdef GPIOF
  else if (bank == GPIOF) {
    enable_reg = &(RCC->AHBENR);
    enable_bit = RCC_AHBENR_GPIOFEN;
    reset_reg = &(RCC->AHBENR);
    reset_bit = RCC_AHBRSTR_GPIOFRST;
  }
#endif
#ifdef GPIOG
  else if (bank == GPIOG) {
    enable_reg = &(RCC->AHBENR);
    enable_bit = RCC_AHBENR_GPIOGEN;
    reset_reg = &(RCC->AHBENR);
    reset_bit = RCC_AHBRSTR_GPIOGRST;
  }
#endif
#ifdef GPIOH
  else if (bank == GPIOH) {
    enable_reg = &(RCC->AHBENR);
    enable_bit = RCC_AHBENR_GPIOHEN;
    reset_reg = &(RCC->AHBENR);
    reset_bit = RCC_AHBRSTR_GPIOHRST;
  }
#endif
  else {
    // (Unrecognized GPIO bank.)
    status = pSTATUS_ERR;
    return;
  }
  status = pSTATUS_SET;
}

/*
 * Read the entire 16 bits/pins in the GPIO bank.
 */
unsigned pGPIO::read(void) {
  if (status == pSTATUS_ERR) {
    return 0;
  }
  // Return the current value of all 16 pins.
  return gpio->IDR;
}

/*
 * Write all 16 bits/pins in the GPIO bank.
 * This will set all 16 pins to the provided value, 0s included.
 */
void pGPIO::write(unsigned dat) {
  if (status == pSTATUS_ERR) {
    return;
  }
  // Write to all pins at once.
  gpio->ODR = dat & 0xFFFF;
}

/*
 * Stream a series of values to the GPIO pins.
 * I don't see why you would, but maybe I can add timed delays.
 */
void pGPIO::stream(volatile void* buf, int len) {
  volatile uint32_t* gpiobuf = (volatile uint32_t*)buf;
  if (status == pSTATUS_ERR) {
    return;
  }
  // Write all of the values, one by one.
  for (int si = 0; si < len; ++si) {
    write(gpiobuf[si]);
  }
}

/*
 * Read a single pin's state.
 */
bool pGPIO::read_pin(unsigned pin_num) {
  if (status == pSTATUS_ERR) {
    return 0;
  }
  return (gpio->IDR & (1 << pin_num));
}

/*
 * Turn a single pin on.
 */
void pGPIO::pin_on(unsigned pin_num) {
  if (status == pSTATUS_ERR) {
    return;
  }
  gpio->ODR |= (1 << pin_num);
}

/*
 * Turn all of the requested pins on, leaving the rest unaffected.
 */
void pGPIO::pins_on(uint16_t pin_mask) {
  if (status == pSTATUS_ERR) {
    return;
  }
  // Turn on all of the requested pins.
  gpio->ODR |= pin_mask;
}

/*
 * Turn a single pin off.
 */
void pGPIO::pin_off(unsigned pin_num) {
  if (status == pSTATUS_ERR) {
    return;
  }
  // Pull a single pin to ground.
  gpio->ODR &= ~(1 << pin_num);
}

/*
 * Turn off all requested pins, leaving the rest unaffected.
 */
void pGPIO::pins_off(uint16_t pin_mask) {
  if (status == pSTATUS_ERR) {
    return;
  }
  // Pull all of the requested pins down.
  gpio->ODR &= ~(pin_mask);
}

/*
 * Toggle a single pin between an on/off state.
 */
void pGPIO::pin_toggle(unsigned pin_num) {
  if (status == pSTATUS_ERR) {
    return;
  }
  gpio->ODR ^= (1 << pin_num);
}

/*
 * Toggle all requested pins, leaving the rest unaffected.
 */
void pGPIO::pins_toggle(uint16_t pin_mask) {
  if (status == pSTATUS_ERR) {
    return;
  }
  // Toggle all of the requested pins between on/off states.
  gpio->ODR ^= pin_mask;
}

/*
 * Set the MODER register to choose between:
 * 0: Input mode (reset state)
 * 1: Output mode
 * 2: Alternate function mode
 * 3: Analog-Digital Converter input mode
 */
void pGPIO::set_pin_mode(unsigned pin_num, unsigned mode) {
  if (status == pSTATUS_ERR) {
    return;
  }
  gpio->MODER &= ~(3 << (pin_num * 2));
  gpio->MODER |= (mode << (pin_num * 2));
}

/*
 * Set the OTYPER register to choose between:
 * 0: Push-pull output.
 * 1: Open-drain output.
 * (Only applicable to 'output' and 'alternate function' modes.)
 */
void pGPIO::set_pin_type(unsigned pin_num, unsigned otype) {
  if (status == pSTATUS_ERR) {
    return;
  }
  gpio->OTYPER &= ~(1 << pin_num);
  gpio->OTYPER |= (otype << pin_num);
}

/*
 * Set the OSPEEDR register to choose between:
 * 0: Low-speed (<= 2MHz)
 * 1: Mid-speed (<= 10MHz)
 * 2: Low-speed (<= 2MHz)
 * 3: Hi-speed  (<= 50MHz)
 * (Only applicable to 'output' and 'alternate function' modes.)
 */
void pGPIO::set_pin_speed(unsigned pin_num, unsigned ospeed) {
  if (status == pSTATUS_ERR) {
    return;
  }
  gpio->OSPEEDR &= ~(3 << (pin_num * 2));
  gpio->OSPEEDR |= (ospeed << (pin_num * 2));
}

/*
 * Set the PUPDR register to choose whether to use an internal
 * pull-up or pull-down resistor:
 * 0: No pull-up or pull-down resistor.
 * 1: Use a pull-up resistor. (~47K?)
 * 2: Use a pull-down resistor. (~47K?)
 * 3: Reserved (do not use.)
 * (Not applicable to 'analog input' mode.)
 */
void pGPIO::set_pin_pupd(unsigned pin_num, unsigned pupd) {
  if (status == pSTATUS_ERR) {
    return;
  }
  gpio->PUPDR &= ~(3 << (pin_num * 2));
  gpio->PUPDR |= (pupd << (pin_num * 2));
}

/*
 * Set the pin's alternate function mode. Any one pin on the STM32
 * can map to up to 15 peripherals in alternate-function mode.
 * This is how the chip knows that you want to use pins for
 * a specific peripheral like I2C, SPI, PWM, etc.
 * (Only applicable to 'alternate function' mode.)
 */
void pGPIO::set_pin_af(unsigned pin_num, unsigned af) {
  if (status == pSTATUS_ERR) {
    return;
  }
  if (pin_num < 8) {
    gpio->AFR[0] &= ~(0xF << (pin_num * 4));
    gpio->AFR[0] |= (af << (pin_num * 4));
  } else {
    gpio->AFR[1] &= ~(0xF << ((pin_num - 8) * 4));
    gpio->AFR[1] |= (af << ((pin_num - 8) * 4));
  }
}

/* GPIO Pin class methods. */
// Default constructor.
pGPIO_pin::pGPIO_pin() {}

// Convenience constructor.
pGPIO_pin::pGPIO_pin(pGPIO* pin_bank, uint8_t pin_num, pGPIO_pin_qinit q) {
  // Set basic values.
  bank = pin_bank;
  pin = pin_num;
  // Set the pin registers according to the quick reference.
  switch (q) {
    case pGPIO_IN_FLOATING:
      bank->set_pin_mode(pin, pGPIO_MODE_IN);
      bank->set_pin_pupd(pin, pGPIO_PUPD_NONE);
      break;
    case pGPIO_IN_PULLUP:
      bank->set_pin_mode(pin, pGPIO_MODE_IN);
      bank->set_pin_pupd(pin, pGPIO_PUPD_UP);
      break;
    case pGPIO_IN_PULLDOWN:
      bank->set_pin_mode(pin, pGPIO_MODE_IN);
      bank->set_pin_pupd(pin, pGPIO_PUPD_DOWN);
      break;
    case pGPIO_IN_ANALOG:
      bank->set_pin_mode(pin, pGPIO_MODE_AIN);
      break;
    case pGPIO_OUT_PP:
      bank->set_pin_mode(pin, pGPIO_MODE_OUT);
      bank->set_pin_type(pin, pGPIO_OTYPE_PP);
      bank->set_pin_speed(pin, pGPIO_SPEED_LOW);
      bank->set_pin_pupd(pin, pGPIO_PUPD_NONE);
      break;
    case pGPIO_OUT_OD:
      bank->set_pin_mode(pin, pGPIO_MODE_OUT);
      bank->set_pin_type(pin, pGPIO_OTYPE_OD);
      bank->set_pin_speed(pin, pGPIO_SPEED_LOW);
      bank->set_pin_pupd(pin, pGPIO_PUPD_NONE);
      break;
    case pGPIO_AF_PP:
      bank->set_pin_mode(pin, pGPIO_MODE_ALT);
      bank->set_pin_type(pin, pGPIO_OTYPE_PP);
      bank->set_pin_speed(pin, pGPIO_SPEED_LOW);
      bank->set_pin_pupd(pin, pGPIO_PUPD_NONE);
      break;
    case pGPIO_AF_OD:
      bank->set_pin_mode(pin, pGPIO_MODE_ALT);
      bank->set_pin_type(pin, pGPIO_OTYPE_OD);
      bank->set_pin_speed(pin, pGPIO_SPEED_LOW);
      bank->set_pin_pupd(pin, pGPIO_PUPD_NONE);
      break;
    case pGPIO_OUT_PP_PULLUP:
      bank->set_pin_mode(pin, pGPIO_MODE_OUT);
      bank->set_pin_type(pin, pGPIO_OTYPE_PP);
      bank->set_pin_speed(pin, pGPIO_SPEED_LOW);
      bank->set_pin_pupd(pin, pGPIO_PUPD_UP);
      break;
    case pGPIO_OUT_OD_PULLUP:
      bank->set_pin_mode(pin, pGPIO_MODE_OUT);
      bank->set_pin_type(pin, pGPIO_OTYPE_OD);
      bank->set_pin_speed(pin, pGPIO_SPEED_LOW);
      bank->set_pin_pupd(pin, pGPIO_PUPD_UP);
      break;
    case pGPIO_OUT_PP_PULLDOWN:
      bank->set_pin_mode(pin, pGPIO_MODE_OUT);
      bank->set_pin_type(pin, pGPIO_OTYPE_PP);
      bank->set_pin_speed(pin, pGPIO_SPEED_LOW);
      bank->set_pin_pupd(pin, pGPIO_PUPD_DOWN);
      break;
    case pGPIO_OUT_OD_PULLDOWN:
      bank->set_pin_mode(pin, pGPIO_MODE_OUT);
      bank->set_pin_type(pin, pGPIO_OTYPE_OD);
      bank->set_pin_speed(pin, pGPIO_SPEED_LOW);
      bank->set_pin_pupd(pin, pGPIO_PUPD_DOWN);
      break;
    case pGPIO_AF_PP_PULLUP:
      bank->set_pin_mode(pin, pGPIO_MODE_ALT);
      bank->set_pin_type(pin, pGPIO_OTYPE_PP);
      bank->set_pin_speed(pin, pGPIO_SPEED_LOW);
      bank->set_pin_pupd(pin, pGPIO_PUPD_UP);
      break;
    case pGPIO_AF_OD_PULLUP:
      bank->set_pin_mode(pin, pGPIO_MODE_ALT);
      bank->set_pin_type(pin, pGPIO_OTYPE_OD);
      bank->set_pin_speed(pin, pGPIO_SPEED_LOW);
      bank->set_pin_pupd(pin, pGPIO_PUPD_UP);
      break;
    case pGPIO_AF_PP_PULLDOWN:
      bank->set_pin_mode(pin, pGPIO_MODE_ALT);
      bank->set_pin_type(pin, pGPIO_OTYPE_PP);
      bank->set_pin_speed(pin, pGPIO_SPEED_LOW);
      bank->set_pin_pupd(pin, pGPIO_PUPD_DOWN);
      break;
    case pGPIO_AF_OD_PULLDOWN:
      bank->set_pin_mode(pin, pGPIO_MODE_ALT);
      bank->set_pin_type(pin, pGPIO_OTYPE_OD);
      bank->set_pin_speed(pin, pGPIO_SPEED_LOW);
      bank->set_pin_pupd(pin, pGPIO_PUPD_DOWN);
      break;
    default:
      status = pSTATUS_ERR;
      return;
  }
  // Mark the pin status as initialized.
  status = pSTATUS_SET;
}

/* Turn the GPIO pin on ('1') */
void pGPIO_pin::on(void) {
  if (status == pSTATUS_ERR) {
    return;
  }
  bank->pin_on(pin);
}

/* Turn the GPIO pin off ('0') */
void pGPIO_pin::off(void) {
  if (status == pSTATUS_ERR) {
    return;
  }
  bank->pin_off(pin);
}

/* Toggle the GPIO pin between on/off. */
void pGPIO_pin::toggle(void) {
  if (status == pSTATUS_ERR) {
    return;
  }
  bank->pin_toggle(pin);
}

/* Read the pin's current state. */
bool pGPIO_pin::read(void) {
  if (status == pSTATUS_ERR) {
    return 0;
  }
  return bank->read_pin(pin);
}

/* Getters/setters. */
// This checks if the pin is initialized; it
// does NOT read the value of an input pin.
int pGPIO_pin::get_status(void) { return status; }

// Set the pin's MODER bits.
void pGPIO_pin::set_mode(unsigned mode) {
  if (status == pSTATUS_ERR) {
    return;
  }
  bank->set_pin_mode(pin, mode);
}

// Set the pin's OTYPER bit.
void pGPIO_pin::set_type(unsigned type) {
  if (status == pSTATUS_ERR) {
    return;
  }
  bank->set_pin_type(pin, type);
}

// Set the pin's OSPEEDR bits.
void pGPIO_pin::set_speed(unsigned speed) {
  if (status == pSTATUS_ERR) {
    return;
  }
  bank->set_pin_speed(pin, speed);
}

// Set the pin's PUPDR bits.
void pGPIO_pin::set_pupd(unsigned pupd) {
  if (status == pSTATUS_ERR) {
    return;
  }
  bank->set_pin_pupd(pin, pupd);
}

// Set the pin's alternate function bits.
void pGPIO_pin::set_alt_func(unsigned af) {
  if (status == pSTATUS_ERR) {
    return;
  }
  bank->set_pin_af(pin, af);
}