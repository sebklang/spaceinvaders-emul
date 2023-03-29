#include <stdio.h>
#include <stdbool.h>
#include "emulator.h"
#include "macros.h"

#define STAX(X) \
    (X) = A

#define LDAX(X) \
    A = (X)

#define MVI(X) \
    (X) = OP_1; \
    PC++

#define LXI(X) \
    (X) = DATA_WORD; \
    PC += 2

bool RegularDataTransfer(EmulatorState *state, uint8_t *op);

/// @brief Emulate one of the 8080's data transfer instructions
/// @param state Pointer to state initialized using InitEmulator(...)
/// @param op Pointer to instruction inside ROM memory
bool EmulateDataTransfer(EmulatorState *state, uint8_t *op)
{
    uint16_t adr;
    uint8_t temp;

    switch (*op) {
    case 0x01: LXI(BC);           break;
    case 0x02: STAX(BC_INDIRECT); break;
    case 0x06: MVI(B);            break;
    case 0x0a: LDAX(BC_INDIRECT); break;
    case 0x0e: MVI(C);            break;
    case 0x11: LXI(DE);           break;
    case 0x12: STAX(DE_INDIRECT); break;
    case 0x16: MVI(D);            break;
    case 0x1a: LDAX(DE_INDIRECT); break;
    case 0x1e: MVI(E);            break;
    case 0x21: LXI(HL);           break;
    case 0x22: // SHLD adr
        adr = DATA_WORD;
        SetMem(state, adr + 1, H);
        SetMem(state, adr + 0, L);
        PC += 2;
        break;
    case 0x26: MVI(H); break;
    case 0x2a: // LHLD adr
        adr = DATA_WORD;
        H = *GetMem(state, adr + 1);
        L = *GetMem(state, adr + 0);
        PC += 2;
        break;
    case 0x2e: MVI(L);  break;
    case 0x31: LXI(SP); break;
    case 0x32: // STA adr
        SetMem(state, DATA_WORD, A);
        PC += 2;
        break;
    case 0x36: MVI(HL_INDIRECT); break;
    case 0x3a: // LDA adr
        A = *GetMem(state, DATA_WORD);
        PC += 2;
        break;
    case 0x3e: MVI(A); break;
    case 0xeb: // XCHG
        temp = H;
        H = D;
        D = temp;
        temp = L;
        L = E;
        E = temp;
        break;
    default:
        if (*op >= 0x40 && *op <= 0x7f && *op != 0x76) {
            return RegularDataTransfer(state, op);
        }
        else {
            printf("EmulateDataTransfer received invalid opcode 0x%02x\n", *op);
            return false;
        }
        break;
    }

    return true;
}

bool RegularDataTransfer(EmulatorState *state, uint8_t *op)
{
    // MOV
    uint8_t  srcIndex =  *op         % 8;
    uint8_t destIndex = (*op - 0x40) / 8;
    uint8_t src, *dest;

    switch (srcIndex) {
    case 0: src = B; break;
    case 1: src = C; break;
    case 2: src = D; break;
    case 3: src = E; break;
    case 4: src = H; break;
    case 5: src = L; break;
    case 6: src = HL_INDIRECT; break;
    case 7: src = A; break;
    default:
        printf("MOV impossible source register\n");
        return false;
    }

    switch (destIndex) {
    case 0: dest = &B; break;
    case 1: dest = &C; break;
    case 2: dest = &D; break;
    case 3: dest = &E; break;
    case 4: dest = &H; break;
    case 5: dest = &L; break;
    case 6: dest = &HL_INDIRECT; break;
    case 7: dest = &A; break;
    default:
        printf("MOV impossible destination register\n");
        return false;
    }

    *dest = src;
    return true;
}
