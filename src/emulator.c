#include "emulator.h"

void InitEmulator(uint8_t *memory, EmulatorState *state)
{
    state->a = 0;
    state->b = 0;
    state->c = 0;
    state->d = 0;
    state->e = 0;
    state->h = 0;
    state->l = 0;
    state->sp = 0;
    state->pc = 0;
    state->memory = memory;
    state->flags.s = 0;
    state->flags.z = 0;
    state->flags.p = 0;
    state->flags.c = 0;
    state->flags.ac = 0;
}

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

void EmulateBranch(EmulatorState *state, uint8_t *op);
void EmulateLogical(EmulatorState *state, uint8_t *op);
void EmulateStack(EmulatorState *state, uint8_t *op);
void EmulateMisc(EmulatorState *state, uint8_t *op);

void EmulateInstruction(EmulatorState *state)
{
    uint8_t *op = &state->memory[state->pc];

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
        EmulateDataTransfer(state, op);
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
        EmulateArithmetic(state, op);
        break;
    
    // Logical
    case 0x07: case 0x0f: case 0x17: case 0x1f:
    case 0x2f: case 0x37: case 0x3f: case 0xe6:
    case 0xee: case 0xf6: case 0xfe:
        EmulateLogical(state, op);
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
        EmulateBranch(state, op);
        break;
    
    case 0xc1: case 0xc5: case 0xd1: case 0xd5: case 0xe1:
    case 0xe3: case 0xe5: case 0xf1: case 0xf5: case 0xf9: 
        EmulateStack(state, op);
        break;

    case 0x27: case 0x76: case 0xd3:
    case 0xdb: case 0xf3: case 0xfb:
        EmulateMisc(state, op);
        break;

    default:
        if (*op >= 0x40 && *op <= 0x7f && *op != 0x76) {
            EmulateDataTransfer(state, op);
        }
        else if (*op >= 0x80 && *op <= 0x9f) {
            EmulateArithmetic(state, op);
        }
        else if (*op >= 0xa0 && *op <= 0xbf) {
            EmulateLogical(state, op);
        }
        printf("WARNING: default case encountered during emulation\n");
        break;
    }

    // remaining in upper part: 0x27 DAA, 0x76 HLT

    state->pc++;
}
