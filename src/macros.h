#ifndef MACROS_H
#define MACROS_H

#include <stdint.h>

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
#define PC (state->pc.word)
#define PC_LO (state->pc.bytes.lo)
#define PC_HI (state->pc.bytes.hi)
#define FLAGS (state->flags)
#define MEM (state->memory)

#define DATA_BYTE (op[1])
#define DATA_WORD ((op[2] << 8) | op[1])

#define INDIRECT(X) (state->memory[(X)])
#define BC_INDIRECT INDIRECT(BC)
#define DE_INDIRECT INDIRECT(DE)
#define HL_INDIRECT INDIRECT(HL)

#define SET_FLAGS_ZSP(X) \
    FLAGS.z  = (X) == 0; \
    FLAGS.s  = ((X) >> 7); \
    FLAGS.p  = Parity(X)

uint8_t Parity(uint8_t x);

#endif
