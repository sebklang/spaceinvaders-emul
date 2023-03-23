#include <stdio.h>
#include <stdbool.h>
#include "emulator.h"
#include "macros.h"

#define PUSH_PC \
    MEM[SP - 1] = PC_HI; \
    MEM[SP - 2] = PC_LO; \
    SP -= 2

#define JMP \
    PC_HI = op[2]; \
    PC_LO = op[1]

#define CALL \
    PC += 3; \
    PUSH_PC; \
    JMP

#define RET \
    PC_HI = MEM[SP + 1]; \
    PC_LO = MEM[SP]; \
    SP += 2

#define RST(X) \
    PC++; \
    PUSH_PC; \
    PC = (X)

/// @brief Emulate one of the 8080's branch instructions
/// @param state Pointer to state initialized using InitEmulator(...)
/// @param op Direct pointer to instruction inside ROM memory
bool EmulateBranch(EmulatorState *state, uint8_t *op)
{
    // NOTE: PC will not be incremented automatically
    switch (*op)
    {
    case 0xc0: if (!FLAGS.z) RET;       break;
    case 0xc2: if (!FLAGS.z) JMP;       break;
    case 0xc3:               JMP;       break;
    case 0xc4: if (!FLAGS.z) CALL;      break;
    case 0xc7:               RST(0x00); break;
    case 0xc8: if (FLAGS.z)  RET;       break;
    case 0xc9:               RET;       break;
    case 0xca: if (FLAGS.z)  JMP;       break;
    case 0xcc: if (FLAGS.z)  CALL;      break;
    case 0xcd:               CALL;      break;
    case 0xcf:               RST(0x08); break;
    case 0xd0: if (!FLAGS.c) RET;       break;
    case 0xd2: if (!FLAGS.c) JMP;       break;
    case 0xd4: if (!FLAGS.c) CALL;      break;
    case 0xd7:               RST(0x10); break;
    case 0xd8: if (FLAGS.c)  RET;       break;
    case 0xda: if (FLAGS.c)  JMP;       break;
    case 0xdc: if (FLAGS.c)  CALL;      break;
    case 0xdf:               RST(0x18); break;
    case 0xe0: if (!FLAGS.s) RET;       break;
    case 0xe2: if (!FLAGS.s) JMP;       break;
    case 0xe4: if (!FLAGS.s) CALL;      break;
    case 0xe7:               RST(0x20); break;
    case 0xe8: if (FLAGS.p)  RET;       break;
    case 0xe9:
        PC_HI = H;
        PC_LO = L;
        break;
    case 0xea: if (FLAGS.p)  JMP;       break;
    case 0xec: if (FLAGS.p)  CALL;      break;
    case 0xef:               RST(0x28); break;
    case 0xf0: if (!FLAGS.s) RET;       break;
    case 0xf2: if (!FLAGS.s) JMP;       break;
    case 0xf4: if (!FLAGS.s) CALL;      break;
    case 0xf7:               RST(0x30); break;
    case 0xf8: if (FLAGS.s)  RET;       break;
    case 0xfa: if (FLAGS.s)  JMP;       break;
    case 0xfc: if (FLAGS.s)  CALL;      break;
    case 0xff:               RST(0x38); break;
    default:
        printf("In branch.c: default\n");
        return false;
        break;
    }

    return true;
}
