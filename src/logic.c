#include <stdio.h>
#include <stdbool.h>
#include "emulator.h"
#include "macros.h"

#define IMM_SET_ZSP_PC \
    SET_FLAGS_ZSP(A); \
    PC++

#define IMM_END \
    SET_FLAG_C(0); \
    IMM_SET_ZSP_PC

#define REG_END \
    SET_FLAG_C(0); \
    SET_FLAGS_ZSP(A)

bool RegularLogic(EmulatorState *state, uint8_t *op);

/// @brief Emulate one of the 8080's logic instructions
/// @param state Pointer to state initialized using InitEmulator(...)
/// @param op Direct pointer to instruction inside ROM memory
bool EmulateLogic(EmulatorState *state, uint8_t *op)
{
    uint8_t carry;
    uint32_t compare;

    switch (*op) {
    case 0x07: // RLC
        carry = A >> 7;
        A = (A << 1) | carry;
        SET_FLAG_C(carry);
        break;
    case 0x0f: // RRC
        carry = A & 1;
        A = (A >> 1) | (carry << 7);
        SET_FLAG_C(carry);
        break;
    case 0x17: // RAL
        carry = A >> 7;
        A = (A << 1) | FLAG_C;
        SET_FLAG_C(carry);
        break;
    case 0x1f: // RAR
        carry = A & 1;
        A = (A >> 1) | (FLAG_C << 7);
        SET_FLAG_C(carry);
        break;
    case 0x2f: // CMA
        A = ~A;
        break;
    case 0x37: // STC
        SET_FLAG_C(1);
        break;
    case 0x3f: // CMC
        SET_FLAG_C(~FLAG_C);
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
        compare = A - DATA_BYTE;
        SET_FLAG_C(compare > 0xff);
        IMM_SET_ZSP_PC;
        break;
    default:
        if (*op >= 0xa0 && *op <= 0xbf) {
            return RegularLogic(state, op);
        }
        else {
            return false;
        }
    }

    return true;
}

bool RegularLogic(EmulatorState *state, uint8_t *op)
{
    uint8_t term;
    uint32_t compare;
    
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
        A = A & term;
        REG_END;
        break;
    case 1: // XRA
        A = A ^ term;
        REG_END;
        break;
    case 2: // ORA
        A = A | term;
        REG_END;
        break;
    case 3: // CMP
        compare = A - term;
        SET_FLAG_C(compare > 0xff);
        SET_FLAGS_ZSP(compare);
        break;
    default:
        printf("In logic.c/RegularLogic: default\n");
        return false;
    }

    return true;
}
