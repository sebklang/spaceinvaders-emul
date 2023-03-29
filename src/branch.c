#include <stdint.h>
#include <stdio.h>
#include <stdbool.h>
#include "emulator.h"
#include "macros.h"

void PushPc(EmulatorState *state)
{
    SetMem(state, SP - 1, PC_HI);
    SetMem(state, SP - 2, PC_LO);
    SP -= 2;
}

void Jmp(EmulatorState *state, uint8_t *op)
{
    PC_HI = OP_2;
    PC_LO = OP_1;
}

void Call(EmulatorState *state, uint8_t *op)
{
    PC += 3;
    PushPc(state);
    Jmp(state, op);
}

void Ret(EmulatorState *state)
{
    PC_HI = *GetMem(state, SP + 1);
    PC_LO = *GetMem(state, SP);
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

#define COND_BRANCH(C, M) { if (C) {M;} else PC++; }

/// @brief Emulate one of the 8080's branch instructions
/// @param state Pointer to state initialized using InitEmulator(...)
/// @param op Direct pointer to instruction inside ROM memory
bool EmulateBranch(EmulatorState *state, uint8_t *op)
{
    // NOTE: PC will not be incremented automatically
    switch (*op)
    {
    case 0xc0: COND_BRANCH(!FLAG_Z, RET)       break;
    case 0xc2: COND_BRANCH(!FLAG_Z, JMP)       break;
    case 0xc3:              JMP;               break;
    case 0xc4: COND_BRANCH(!FLAG_Z, CALL)      break;
    case 0xc7:              RST(0x00);         break;
    case 0xc8: COND_BRANCH(FLAG_Z,  RET)       break;
    case 0xc9:              RET;               break;
    case 0xca: COND_BRANCH(FLAG_Z,  JMP)       break;
    case 0xcc: COND_BRANCH(FLAG_Z,  CALL)      break;
    case 0xcd:              CALL;              break;
    case 0xcf:              RST(0x08);         break;
    case 0xd0: COND_BRANCH(!FLAG_C, RET)       break;
    case 0xd2: COND_BRANCH(!FLAG_C, JMP)       break;
    case 0xd4: COND_BRANCH(!FLAG_C, CALL)      break;
    case 0xd7:              RST(0x10); break;
    case 0xd8: COND_BRANCH(FLAG_C,  RET)       break;
    case 0xda: COND_BRANCH(FLAG_C,  JMP)       break;
    case 0xdc: COND_BRANCH(FLAG_C,  CALL)      break;
    case 0xdf:              RST(0x18);         break;
    case 0xe0: COND_BRANCH(!FLAG_S, RET)       break;
    case 0xe2: COND_BRANCH(!FLAG_S, JMP)       break;
    case 0xe4: COND_BRANCH(!FLAG_S, CALL)      break;
    case 0xe7:              RST(0x20);         break;
    case 0xe8: COND_BRANCH(FLAG_P,  RET)       break;
    case 0xe9:
        PC_HI = H;
        PC_LO = L;
        break;
    case 0xea: COND_BRANCH(FLAG_P,  JMP)       break;
    case 0xec: COND_BRANCH(FLAG_P,  CALL)      break;
    case 0xef:              RST(0x28);         break;
    case 0xf0: COND_BRANCH(!FLAG_S, RET)       break;
    case 0xf2: COND_BRANCH(!FLAG_S, JMP)       break;
    case 0xf4: COND_BRANCH(!FLAG_S, CALL)      break;
    case 0xf7:              RST(0x30);         break;
    case 0xf8: COND_BRANCH(FLAG_S,  RET)       break;
    case 0xfa: COND_BRANCH(FLAG_S,  JMP)       break;
    case 0xfc: COND_BRANCH(FLAG_S,  CALL)      break;
    case 0xff:              RST(0x38); break;
    default:
        printf("In branch.c: default\n");
        return false;
        break;
    }

    return true;
}
