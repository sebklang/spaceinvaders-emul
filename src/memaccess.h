#ifndef MEMACCESS_H
#define MEMACCESS_H

#include <stdint.h>
#include <stdbool.h>
#include "emulator.h"

uint8_t *GetMem(EmulatorState* state, uint16_t loc);
bool     SetMem(EmulatorState* state, uint16_t loc, uint8_t val);
bool     SetMemDirect(EmulatorState* state, uint16_t loc, uint8_t val);

#endif
