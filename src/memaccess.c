#include <stdio.h>
#include "memaccess.h"
#include "macros.h"

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
    return true;
}
