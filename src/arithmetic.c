#include <stdio.h>
#include <stdbool.h>
#include "emulator.h"
#include "macros.h"

// TODO in this file: AC flag

#define INX(X) (X)++
#define INR(X) (X)++; SET_FLAGS_ZSP(X)
#define DCX(X) (X)--;
#define DCR(X) (X)--; SET_FLAGS_ZSP(X)
#define DAD(X) \
    SET_FLAG_C((uint32_t) HL + (X) > 0xffff); \
    HL += (X)
#define ADI \
    SET_FLAG_C((uint32_t) A + op[1] > 0xff); \
    A += op[1]; \
    SET_FLAGS_ZSP(A); \
    PC++
#define ACI \
    cin = FLAG_C; \
    SET_FLAG_C((uint32_t) A + op[1] + cin > 0xff); \
    A += op[1] + cin; \
    SET_FLAGS_ZSP(A); \
    PC++
#define SUI \
    SET_FLAG_C((uint32_t) A - op[1] > 0xff); \
    A -= op[1]; \
    SET_FLAGS_ZSP(A); \
    PC++
#define SBI \
    cin = FLAG_C; \
    SET_FLAG_C((uint32_t) A - op[1] - cin > 0xff); \
    A -= op[1] + cin; \
    SET_FLAGS_ZSP(A); \
    PC++

bool RegularArithmetic(EmulatorState *state, uint8_t *op);

/// @brief Emulate one of the 8080's arithmetic instructions
/// @param state Pointer to state initialized using InitEmulator(...)
/// @param op Direct pointer to instruction inside ROM memory
bool EmulateArithmetic(EmulatorState *state, uint8_t *op)
{
    uint8_t cin;

    switch(*op) {
    case 0x03: INX(BC);  break;
    case 0x04: INR(B);   break;
    case 0x05: DCR(B);   break;
    case 0x09: DAD(BC);  break;
    case 0x0b: DCX(BC);  break;
    case 0x0c: INR(C);   break;
    case 0x0d: DCR(C);   break;
    case 0x13: INX(DE);  break;
    case 0x14: INR(D);   break;
    case 0x15: DCR(D);   break;
    case 0x19: DAD(DE);  break;
    case 0x1b: DCX(DE);  break;
    case 0x1c: INR(E);   break;
    case 0x1d: DCR(E);   break;
    case 0x23: INX(HL);  break;
    case 0x24: INR(H);   break;
    case 0x25: DCR(H);   break;
    case 0x29: DAD(HL);  break;
    case 0x2b: DCX(HL);  break;
    case 0x2c: INR(L);   break;
    case 0x2d: DCR(L);   break;
    case 0x33: INX(SP);  break;
    case 0x34: INR(HL_INDIRECT); break;
    case 0x35: DCR(HL_INDIRECT); break;
    case 0x39: DAD(SP);  break;
    case 0x3b: DCX(SP);  break;
    case 0x3c: INR(A);   break;
    case 0x3d: DCR(A);   break;
    case 0xc6: ADI;      break;
    case 0xce: ACI;      break;
    case 0xd6: SUI;      break;
    case 0xde: SBI;      break;
    default:
        if (*op >= 0x80 && *op <= 0x9f) {
            return RegularArithmetic(state, op);
        }
        else {
            printf("Impossible arithmetic instruction *op = %02x", *op);
        }
    }

    return true;
}

bool RegularArithmetic(EmulatorState *state, uint8_t *op)
{
    uint8_t cin;
    uint8_t term;
    switch (*op % 8) {
    case 0: term = B; break;
    case 1: term = C; break;
    case 2: term = D; break;
    case 3: term = E; break;
    case 4: term = H; break;
    case 5: term = L; break;
    case 6: term = HL_INDIRECT; break;
    case 7: term = A; break;
    default:
        printf("Impossible arithmetic term\n");
        return false;
    }

    switch ((*op - 0x80) / 8) {
    case 0: // ADD
        SET_FLAG_C((uint32_t) A + term > 0xff);
        A += term;
        break;
    case 1: // ADC
        cin = FLAG_C;
        SET_FLAG_C((uint32_t) A + term + cin > 0xff);
        A += term + cin;
        break;
    case 2: // SUB
        SET_FLAG_C((uint32_t) A - term > 0xff);
        A -= term;
        break;
    case 3: // SBB
        cin = FLAG_C;
        SET_FLAG_C((uint32_t) A - term - cin > 0xff);
        A -= term + cin;
        break;
    default:
        printf("Impossible case ADD/ADC/SUB/SBB\n");
        return false;
    }

    SET_FLAGS_ZSP(A);
}
