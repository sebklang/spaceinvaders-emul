#include <stdbool.h>
#include "emulator.h"
#include "macros.h"

#define SET_FLAGS(X) \
    FLAGS.z  = (X) == 0; \
    FLAGS.s  = ((X) >> 7); \
    FLAGS.p  = Parity(X); \
    FLAGS.ac = 0 // todo (probably won't)

#define INX(X) (X)++
#define INR(X) (X)++; SET_FLAGS(X)
#define DCX(X) (X)--;
#define DCR(X) (X)--; SET_FLAGS(X)
#define DAD(X) FLAGS.c = (uint32_t) HL + (X) > 0xffff; HL += (X)
#define ADI \
    FLAGS.c = (uint32_t) A + op[1] > 0xff; \
    A += op[1]; \
    PC++

uint8_t Parity(uint8_t x)
{
    uint8_t count = 0;
    for (int i = 0; i < 8; i++) {
        count += (x >> i) & 1;
    }
    return count % 2 == 0;
}

/// @brief Emulate one of the 8080's arithmetic instructions
/// @param state Pointer to state initialized using InitEmulator(...)
/// @param op Direct pointer to instruction inside ROM memory
bool EmulateArithmetic(EmulatorState *state, uint8_t *op)
{

    /*
    case 0x03: case 0x04: case 0x05: case 0x09:
    case 0x0b: case 0x0c: case 0x0d: case 0x13:
    case 0x14: case 0x15: case 0x19: case 0x1b:
    case 0x1c: case 0x1d: case 0x23: case 0x24:
    case 0x25: case 0x29: case 0x2b: case 0x2c:
    case 0x2d: case 0x33: case 0x34: case 0x35:
    case 0x39: case 0x3b: case 0x3c: case 0x3d:
    case 0xc6: case 0xce: case 0xd6: case 0xde:
    */

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
    case 0xce: 
    }
}
