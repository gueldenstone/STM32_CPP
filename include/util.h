/**
 * @file: util.h
 *
 * @date: 2020-04-25
 *
 * @author: Lukas Güldenstein
 */

#ifndef _UTIL_H
#define _UTIL_H

/* -------------------------------- includes -------------------------------- */
#include "stm32f3xx.h"
/* --------------------------- function prototypes -------------------------- */
#ifdef __cplusplus
extern "C" {
#endif
void setupClock(void);
void initDelay(void);
void delay(uint32_t);
#ifdef __cplusplus
};
#endif
#endif /* _UTIL_H */