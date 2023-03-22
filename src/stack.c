#include <stdbool.h>
#include "emulator.h"
#include "macros.h"

#define POP16(X, Y) \
    (X) = MEM[SP + 1]; \
    (Y) = MEM[SP]; \
    SP += 2

#define PUSH16(X, Y) \
    MEM[SP - 1] = (X); \
    MEM[SP - 2] = (Y); \
    SP -= 2

bool EmulateStack(EmulatorState *state, uint8_t *op)
{
    uint8_t temp;
    /*
    case 0xc1: case 0xc5: case 0xd1:
    case 0xd5: case 0xe1: case 0xe3:
    case 0xe5: case 0xf1: case 0xf5: case 0xf9: 
    */

    switch (*op) {
    case 0xc1:  POP16(B, C); break;
    case 0xc5: PUSH16(B, C); break;
    case 0xd1:  POP16(D, E); break;
    case 0xd5: PUSH16(D, E); break;
    case 0xe1:  POP16(H, L); break;
    case 0xe3: // XTHL
        temp = H;
        H = MEM[SP + 1];
        MEM[SP + 1] = temp;
        temp = L;
        L = MEM[SP];
        MEM[SP] = temp;
        break;
    case 0xe5: PUSH16(H, L); break;
    case 0xf1: // todo POP PSW
    }
}
