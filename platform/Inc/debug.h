#ifndef PLATFORM_DEBUG_H_
#define PLATFORM_DEBUG_H_

#include "main.h"

/**
 * @brief Initializes debug pin
*/
void initDebugPin(void);

/**
 * @brief switches the debug pin to work as analog input (default state)
*/
void deinitDebugPin(void);

/**
 * @brief toggles the debug pin
*/
void DebugPinBlink(void);

#endif