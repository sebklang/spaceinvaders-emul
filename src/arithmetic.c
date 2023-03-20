#include "emulator.h"
#include "macros.h"

/// @brief Emulate one of the 8080's arithmetic instructions
/// @param state Pointer to state initialized using InitEmulator(...)
/// @param op Direct pointer to instruction inside ROM memory
void EmulateArithmetic(EmulatorState *state, uint8_t *op)
{
    switch(*op) {
    case 0x03: // INX B
        C++;
        if (C == 0)
            B++;
        break;
    }
}
