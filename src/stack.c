#include <stdio.h>
#include <stdbool.h>
#include "emulator.h"
#include "macros.h"

#define POP(X, Y) \
    (X) = MEM[SP + 1]; \
    (Y) = MEM[SP]; \
    SP += 2

#define PUSH(X, Y) \
    MEM[SP - 1] = (X); \
    MEM[SP - 2] = (Y); \
    SP -= 2

bool EmulateStack(EmulatorState *state, uint8_t *op)
{
    uint8_t temp;

    switch (*op) {
    case 0xc1:  POP(B, C); break;
    case 0xc5: PUSH(B, C); break;
    case 0xd1:  POP(D, E); break;
    case 0xd5: PUSH(D, E); break;
    case 0xe1:  POP(H, L); break;
    //   0xe3 (XHTL) handled below
    case 0xe5: PUSH(H, L); break;
    case 0xf1:  POP(A, FLAG_BYTE); break;
    case 0xf5: PUSH(A, FLAG_BYTE); break;
    case 0xf9: SP = HL;      break;
    case 0xe3: // XHTL
        temp = H;
        H = MEM[SP + 1];
        MEM[SP + 1] = temp;
        temp = L;
        L = MEM[SP];
        MEM[SP] = temp;
        break;
    default:
        printf("In stack.c: default\n");
        return false;
    }

    return true;
}