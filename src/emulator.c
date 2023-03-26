#include <stdio.h>
#include <stdbool.h>
#include "emulator.h"
#include "macros.h"

bool EmulateDataTransfer (EmulatorState *state, uint8_t *op);
bool EmulateArithmetic   (EmulatorState *state, uint8_t *op);
bool EmulateBranch       (EmulatorState *state, uint8_t *op);
bool EmulateLogic        (EmulatorState *state, uint8_t *op);
bool EmulateStack        (EmulatorState *state, uint8_t *op);
bool EmulateMisc         (EmulatorState *state, uint8_t *op);

/// @brief Initialize an emulator, represented by a state object
/// @param memory Pointer to pre-initialized memory of the emulator
/// @param memsize The number of bytes allocated to memory (max 65536)
/// @param ih Pointer to input handler function accepting a device code as parameter and returning the input to be stored in the accumulator. May be null if input is not used.
/// @param oh Pointer to output handler function accepting a device code and a byte of output as parameters and returning void. May be null if output is not used.
/// @param state Pointer to state to be initialized
void InitEmulator(EmulatorState *state, uint8_t *memory, memsize_t memsize, InputHandler ih, OutputHandler oh)
{
    A = 0;
    BC = 0;
    DE = 0;
    HL = 0;
    SP = 0;
    PC = 0;
    MEM = memory;
    MEMSIZE = memsize;
    SET_FLAG_S(0);
    SET_FLAG_Z(0);
    SET_FLAG_P(0);
    SET_FLAG_C(0);
    SET_FLAG_AC(0);
    HALTED = false;
    INT_ENABLE = false; // TODO i have no idea what to initialize this to
    state->inputHandler = ih;
    state->outputHandler = oh;
}

/// @brief Emulate the next instruction
/// @param state State/emulator to run
bool EmulateInstruction(EmulatorState *state)
{
    if (HALTED) return true;

    uint8_t *op = &MEM[PC];
    bool opIsBranch = false; // PC will not be automatically incremented in these ops!

    switch (*op) {
    case 0x00: // NOP
        break;

    // Data Transfer
    case 0x01: case 0x02: case 0x06:
    case 0x0a: case 0x0e: case 0x11:
    case 0x12: case 0x16: case 0x1a: 
    case 0x1e: case 0x21: case 0x22:
    case 0x26: case 0x2a: case 0x2e:
    case 0x31: case 0x32: case 0x36:
    case 0x3a: case 0x3e: case 0xeb:
        return EmulateDataTransfer(state, op);
        break;

    // Arithmetic
    case 0x03: case 0x04: case 0x05: case 0x09:
    case 0x0b: case 0x0c: case 0x0d: case 0x13:
    case 0x14: case 0x15: case 0x19: case 0x1b:
    case 0x1c: case 0x1d: case 0x23: case 0x24:
    case 0x25: case 0x29: case 0x2b: case 0x2c:
    case 0x2d: case 0x33: case 0x34: case 0x35:
    case 0x39: case 0x3b: case 0x3c: case 0x3d:
    case 0xc6: case 0xce: case 0xd6: case 0xde:
        return EmulateArithmetic(state, op);
        break;
    
    // Logical
    case 0x07: case 0x0f: case 0x17: case 0x1f:
    case 0x2f: case 0x37: case 0x3f: case 0xe6:
    case 0xee: case 0xf6: case 0xfe:
        return EmulateLogic(state, op);
        break;

    // Branch
    case 0xc0: case 0xc2: case 0xc3: case 0xc4:
    case 0xc7: case 0xc8: case 0xc9: case 0xca:
    case 0xcc: case 0xcd: case 0xcf: case 0xd0:
    case 0xd2: case 0xd4: case 0xd7: case 0xd8:
    case 0xda: case 0xdc: case 0xdf: case 0xe0:
    case 0xe2: case 0xe4: case 0xe7: case 0xe8:
    case 0xe9: case 0xea: case 0xec: case 0xef:
    case 0xf0: case 0xf2: case 0xf4: case 0xf7:
    case 0xf8: case 0xfa: case 0xfc: case 0xff:
        opIsBranch = true;
        return EmulateBranch(state, op);
        break;

    // Stack
    case 0xc1: case 0xc5: case 0xd1: case 0xd5: case 0xe1:
    case 0xe3: case 0xe5: case 0xf1: case 0xf5: case 0xf9: 
        return EmulateStack(state, op);
        break;

    // IO and special instructions ("miscellaneous")
    case 0x27: case 0x76: case 0xd3:
    case 0xdb: case 0xf3: case 0xfb:
        return EmulateMisc(state, op);
        break;

    default:
        if (*op >= 0x40 && *op <= 0x7f && *op != 0x76) {
            return EmulateDataTransfer(state, op);
        }
        else if (*op >= 0x80 && *op <= 0x9f) {
            return EmulateArithmetic(state, op);
        }
        else if (*op >= 0xa0 && *op <= 0xbf) {
            return EmulateLogic(state, op);
        }
        else {
            printf("WARNING: default encountered. Instruction will be skipped. (*op = 0x%02x)\n", *op);
        }
        break;
    }

    if (!opIsBranch)
        PC++;
    
    return true;
}
