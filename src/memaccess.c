#include <stdio.h>
#include "memaccess.h"
#include "macros.h"

void _SetMem(uint16_t loc, uint8_t val); // Defined in guimain.cpp

#ifndef __cplusplus
void _SetMem(uint16_t loc, uint8_t val) {}
#endif

uint8_t *GetMem(EmulatorState *state, uint16_t loc)
{
    if (loc >= MEMSIZE) {
        printf("Error: GetMem received loc = %04x where memsize = %04x\n", loc, MEMSIZE);
        return NULL;
    }

    return &MEM[loc];
}

bool SetMem(EmulatorState *state, uint16_t loc, uint8_t val)
{
    if (loc >= MEMSIZE) {
        printf("Error: SetMem received loc = %04x where memsize = %04x\n", loc, MEMSIZE);
        return false;
    }
    
    MEM[loc] = val;
    _SetMem(loc, val);
    return true;
}

