#ifndef MACROS_H
#define MACROS_H

#include <stdint.h>
#include "memaccess.h"

#define A  (state->a)

#define B  (state->bc.bytes.hi)
#define C  (state->bc.bytes.lo)
#define BC (state->bc.word)

#define D  (state->de.bytes.hi)
#define E  (state->de.bytes.lo)
#define DE (state->de.word)

#define H  (state->hl.bytes.hi)
#define L  (state->hl.bytes.lo)
#define HL (state->hl.word)

#define SP (state->sp.word)
#define SP_LO (state->sp.bytes.lo)
#define SP_HI (state->sp.bytes.hi)

#define PC (state->pc.word)
#define PC_LO (state->pc.bytes.lo)
#define PC_HI (state->pc.bytes.hi)
#define INSTR_PTR (state->instrPtr)

#define FLAG_BYTE (state->flags)
#define HALTED (state->halted)
#define INT_ENABLE (state->intEnable)
#define MEM (state->memory)
#define MEMSIZE (state->memsize)

#define FLAG_N(N) ((FLAG_BYTE >> (N)) & 1)
#define SET_FLAG_N(N, X) { \
    if (X) \
        FLAG_BYTE |=  (1 << (N)); \
    else \
        FLAG_BYTE &= ~(1 << (N)); \
}

#define FLAG_S FLAG_N(7)
#define SET_FLAG_S(X) SET_FLAG_N(7, X)

#define FLAG_Z FLAG_N(6)
#define SET_FLAG_Z(X) SET_FLAG_N(6, X)

#define FLAG_AC FLAG_N(4)
#define SET_FLAG_AC(X) SET_FLAG_N(4, X)

#define FLAG_P FLAG_N(2)
#define SET_FLAG_P(X) SET_FLAG_N(2, X)

#define FLAG_C FLAG_N(0)
#define SET_FLAG_C(X) SET_FLAG_N(0, X)

#define OP_1 (*GetMem(state, INSTR_PTR.word + 1))
#define OP_2 (*GetMem(state, INSTR_PTR.word + 2))

#define DATA_BYTE (OP_1)
#define DATA_WORD ((OP_2 << 8) | OP_1)

#define INDIRECT(X) (*GetMem(state, (X)))
#define BC_INDIRECT INDIRECT(BC)
#define DE_INDIRECT INDIRECT(DE)
#define HL_INDIRECT INDIRECT(HL)

#define SET_FLAGS_ZSP(X) { \
    SET_FLAG_Z((X) == 0); \
    SET_FLAG_S((X) & 0x80); \
    SET_FLAG_P(Parity(X)); \
}

uint8_t Parity(uint8_t x);

#endif
