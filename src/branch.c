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
    PUSH_PC; \
    JMP

#define RET \
    PC_HI = MEM[SP + 1]; \
    PC_LO = MEM[SP]; \
    SP += 2

#define RST(X) \
    PUSH_PC; \
    PC = (X)

/// @brief Emulate one of the 8080's branch instructions
/// @param state Pointer to state initialized using InitEmulator(...)
/// @param op Direct pointer to instruction inside ROM memory
bool EmulateBranch(EmulatorState *state, uint8_t *op)
{

    /*
    case 0xc0: case 0xc2: case 0xc3: case 0xc4:
    case 0xc7: case 0xc8: case 0xc9: case 0xca:
    case 0xcc: case 0xcd: case 0xcf: case 0xd0:
    case 0xd2: case 0xd4: case 0xd7: case 0xd8:
    case 0xda: case 0xdc: case 0xdf: case 0xe0:
    case 0xe2: case 0xe4: case 0xe7: case 0xe8:
    case 0xe9: case 0xea: case 0xec: case 0xef:
    case 0xf0: case 0xf2: case 0xf4: case 0xf7:
    case 0xf8: case 0xfa: case 0xfc: case 0xff:
    */

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
    case 0xe0: // todo RPO
    }

    return true;
}
