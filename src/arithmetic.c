#include "emulator.h"

/// @brief Emulate one of the 8080's arithmetic instructions
/// @param state Pointer to state initialized using InitEmulator(...)
/// @param op Direct pointer to instruction inside ROM memory
void EmulateArithmetic(EmulatorState *state, uint8_t *op)
{
    switch(*op) {
    case 0x03: // INX B
        state->c++;
        if (state->c == 0)
            state->b++;
        break;
    }
}
