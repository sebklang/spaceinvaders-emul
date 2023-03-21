#include <stdio.h>
#include <stdbool.h>
#include "emulator.h"
#include "macros.h"

#define IMM_SET_ZSP_PC \
    SET_FLAGS_ZSP(A); \
    PC++

#define IMM_END \
    FLAGS.c = 0; \
    IMM_SET_ZSP_PC

/// @brief Emulate one of the 8080's logic instructions
/// @param state Pointer to state initialized using InitEmulator(...)
/// @param op Direct pointer to instruction inside ROM memory
bool EmulateLogic(EmulatorState *state, uint8_t *op)
{

    /*
    case 0x07: case 0x0f: case 0x17: case 0x1f:
    case 0x2f: case 0x37: case 0x3f: case 0xe6:
    case 0xee: case 0xf6: case 0xfe:
    */

    uint8_t carry;
    uint32_t cpi;

    switch (*op) {
    case 0x07: // RLC
        carry = A >> 7;
        A = (A << 1) | carry;
        FLAGS.c = carry;
        break;
    case 0x0f: // RRC
        carry = A & 1;
        A = (A >> 1) | (carry << 7);
        FLAGS.c = carry;
        break;
    case 0x17: // RAL
        carry = A >> 7;
        A = (A << 1) | FLAGS.c;
        FLAGS.c = carry;
        break;
    case 0x1f: // RAR
        carry = A & 1;
        A = (A >> 1) | (FLAGS.c << 7);
        FLAGS.c = carry;
        break;
    case 0x2f: // CMA
        A = ~A;
        break;
    case 0x37: // STC
        FLAGS.c = 1;
        break;
    case 0x3f: // CMC
        FLAGS.c = ~FLAGS.c;
        break;
    case 0xe6: // ANI D8
        A = A & DATA_BYTE;
        IMM_END;
        break;
    case 0xee: // XRI D8
        A = A ^ DATA_BYTE;
        IMM_END;
        break;
    case 0xf6: // ORI D8
        A = A | DATA_BYTE;
        IMM_END;
        break;
    case 0xfe: // CPI D8
        cpi = A - DATA_BYTE;
        FLAGS.c = cpi > 0xff;
        IMM_SET_ZSP_PC;
        break;
    default:
        if (*op >= 0xa0 && *op <= 0xbf) {
            uint8_t term;
            switch(*op % 8) {
            case 0: term = B; break;
            case 1: term = C; break;
            case 2: term = D; break;
            case 3: term = E; break;
            case 4: term = H; break;
            case 5: term = L; break;
            case 6: term = HL_INDIRECT; break;
            case 7: term = A; break;
            default:
                printf("Impossible logic term\n");
                return false;
            }
            switch((*op - 0xa0) / 8) {
            case 0: // ANA
                break;
            case 1: // XRA
                break;
            case 2: // ORA
                break;
            case 3: // CMP
                break;
            default:
                printf("TODO");
                return false;
            }
        }
        else {
            return false;
        }
    }

    return true;
}
