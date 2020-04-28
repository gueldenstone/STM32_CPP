/**
 * @file: main.hpp
 *
 * @date: 2020-04-24
 *
 * @author: Lukas Güldenstein
 */

#ifndef _MAIN_HPP
#define _MAIN_HPP

/* -------------------------------- includes -------------------------------- */

/* --------------------------- external functions --------------------------- */
// C++ memory regions for initializing statics.
// ('fini_array' is ignored because static destructors are rarely
//  important in embedded programs, which never really 'exit'.)
extern void (*__preinit_array_start[])(void) __attribute__((weak));
extern void (*__preinit_array_end[])(void) __attribute__((weak));
extern void (*__init_array_start[])(void) __attribute__((weak));
extern void (*__init_array_end[])(void) __attribute__((weak));

/* --------------------------- function prototypes -------------------------- */

#endif /* _MAIN_HPP */