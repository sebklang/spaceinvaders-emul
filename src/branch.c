#include <stdint.h>
#include <stdio.h>
#include <stdbool.h>
#include "emulator.h"
#include "macros.h"

void PushPc(EmulatorState *state)
{
    MEM[SP - 1] = PC_HI;
    MEM[SP - 2] = PC_LO;
    SP -= 2;
}

void Jmp(EmulatorState *state, uint8_t *op)
{
    PC_HI = op[2];
    PC_LO = op[1];
}

void Call(EmulatorState *state, uint8_t *op)
{
    PC += 3;
    PushPc(state);
    Jmp(state, op);
}

void Ret(EmulatorState *state)
{
    PC_HI = MEM[SP + 1];
    PC_LO = MEM[SP];
    SP += 2;
}

void Rst(EmulatorState *state, uint8_t adr)
{ 
    PC++;
    PushPc(state);
    PC = adr;
}

#define PUSH_PC PushPc(state)
#define JMP Jmp(state, op)
#define CALL Call(state, op)
#define RET Ret(state)
#define RST(X) Rst(state, (X))

/// @brief Emulate one of the 8080's branch instructions
/// @param state Pointer to state initialized using InitEmulator(...)
/// @param op Direct pointer to instruction inside ROM memory
bool EmulateBranch(EmulatorState *state, uint8_t *op)
{
    // NOTE: PC will not be incremented automatically
    switch (*op)
    {
    case 0xc0: if (!FLAG_Z) RET;       break;
    case 0xc2: if (!FLAG_Z) JMP;       break;
    case 0xc3:              JMP;       break;
    case 0xc4: if (!FLAG_Z) CALL;      break;
    case 0xc7:              RST(0x00); break;
    case 0xc8: if (FLAG_Z)  RET;       break;
    case 0xc9:              RET;       break;
    case 0xca: if (FLAG_Z)  JMP;       break;
    case 0xcc: if (FLAG_Z)  CALL;      break;
    case 0xcd:              CALL;      break;
    case 0xcf:              RST(0x08); break;
    case 0xd0: if (!FLAG_C) RET;       break;
    case 0xd2: if (!FLAG_C) JMP;       break;
    case 0xd4: if (!FLAG_C) CALL;      break;
    case 0xd7:              RST(0x10); break;
    case 0xd8: if (FLAG_C)  RET;       break;
    case 0xda: if (FLAG_C)  JMP;       break;
    case 0xdc: if (FLAG_C)  CALL;      break;
    case 0xdf:              RST(0x18); break;
    case 0xe0: if (!FLAG_S) RET;       break;
    case 0xe2: if (!FLAG_S) JMP;       break;
    case 0xe4: if (!FLAG_S) CALL;      break;
    case 0xe7:              RST(0x20); break;
    case 0xe8: if (FLAG_P)  RET;       break;
    case 0xe9:
        PC_HI = H;
        PC_LO = L;
        break;
    case 0xea: if (FLAG_P)  JMP;       break;
    case 0xec: if (FLAG_P)  CALL;      break;
    case 0xef:              RST(0x28); break;
    case 0xf0: if (!FLAG_S) RET;       break;
    case 0xf2: if (!FLAG_S) JMP;       break;
    case 0xf4: if (!FLAG_S) CALL;      break;
    case 0xf7:              RST(0x30); break;
    case 0xf8: if (FLAG_S)  RET;       break;
    case 0xfa: if (FLAG_S)  JMP;       break;
    case 0xfc: if (FLAG_S)  CALL;      break;
    case 0xff:              RST(0x38); break;
    default:
        printf("In branch.c: default\n");
        return false;
        break;
    }

    return true;
}
