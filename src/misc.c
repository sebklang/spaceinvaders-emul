#include <stdio.h>
#include <stdbool.h>
#include "emulator.h"
#include "macros.h"

bool EmulateMisc(EmulatorState *state, uint8_t *op)
{
    // NOTE: PC will not be incremented automatically
    switch (*op) {
    case 0x27: // DAA (Not used by space invaders)
        break;
    case 0x76: // HLT
        HALTED = true;
        PC++;
        break;
    case 0xd3: // OUT D8
        break;
    case 0xdb: // IN D8
        break;
    case 0xf3: // DI
        break;
    case 0xfb: // EI
        break;
    default:
        printf("In misc.c: default\n");
        return false;
    }

    return true;
}
