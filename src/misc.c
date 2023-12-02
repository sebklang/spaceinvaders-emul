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
        break;
    case 0xd3: // OUT D8
        if (state->outputHandler != NULL)
            state->outputHandler(DATA_BYTE, A);
        PC++;
        break;
    case 0xdb: // IN D8
        if (state->inputHandler != NULL)
            A = state->inputHandler(DATA_BYTE);
        PC++;
        break;
    case 0xf3: // DI
        INT_ENABLE = false;
        break;
    case 0xfb: // EI
        INT_ENABLE = true;
        break;
    default:
        printf("In misc.c: default\n");
        return false;
    }

    return true;
}

