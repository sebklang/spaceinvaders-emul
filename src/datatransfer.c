#include "emulator.h"

/// @brief Emulate one of the 8080's data transfer instructions
/// @param state Pointer to state initialized using InitEmulator(...)
/// @param op Direct pointer to instruction inside ROM memory
void EmulateDataTransfer(EmulatorState *state, uint8_t *op)
{
    switch (*op) {
    case 0x01: // LXI B,D16
        state->b = op[2];
        state->c = op[1];
        state->pc += 2;
        break;

    case 0x02: // STAX B
        state->memory[(state->b << 8) | state->c] = state->a;
        break;
    }
}
