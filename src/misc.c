#include <stdio.h>
#include <stdbool.h>
#include "emulator.h"
#include "macros.h"

bool EmulateMisc(EmulatorState *state, uint8_t *op)
{
    // NOTE: PC will not be incremented automatically
    switch (*op) {
    case 0x27: break; // DAA (Not used by space invaders)
    case 0x76: // HLT
        HALTED = true;
        PC++;
        break;
    case 0xd3: break; // OUT D8
    case 0xdb: break; // IN D8
    case 0xf3: break; // DI
    case 0xfb: break; // EI
    default:
        printf("In misc.c: default\n");
        return false;
    }

    return true;
}
