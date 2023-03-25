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
#define FLAG_BYTE (state->flags)
#define HALTED (state->halted)
#define INT_ENABLE (state->intEnable)
#define MEM (state->memory)
#define MEMSIZE (state->memsize)

/*typedef struct EmulatorFlags {
    uint8_t s  : 1;
    uint8_t z  : 1;
    uint8_t _1 : 1; // Pad 1
    uint8_t ac : 1;
    uint8_t _2 : 1; // Pad 2
    uint8_t p  : 1;
    uint8_t _3 : 1; // Pad 3
    uint8_t c  : 1;
} EmulatorFlags;*/

#define FLAG_S  ((FLAG_BYTE >> 7) & 1)
#define SET_FLAG_S  FLAG_BYTE |=  0x80
#define RST_FLAG_S  FLAG_BYTE &= ~0x80

#define FLAG_Z  ((FLAG_BYTE >> 6) & 1)
#define SET_FLAG_Z  FLAG_BYTE |=  0x40
#define RST_FLAG_Z  FLAG_BYTE &= ~0x40

#define FLAG_AC ((FLAG_BYTE >> 4) & 1)
#define SET_FLAG_AC FLAG_BYTE |=  0x10
#define RST_FLAG_AC FLAG_BYTE &= ~0x10

#define FLAG_P  ((FLAG_BYTE >> 2) & 1)
#define SET_FLAG_P  FLAG_BYTE |=  0x04
#define RST_FLAG_P  FLAG_BYTE &= ~0x04

#define FLAG_C  ((FLAG_BYTE >> 0) & 1)
#define SET_FLAG_C  FLAG_BYTE |=  0x01
#define RST_FLAG_C  FLAG_BYTE &= ~0x01

#define DATA_BYTE (op[1])
#define DATA_WORD ((op[2] << 8) | op[1])

#define INDIRECT(X) (state->memory[(X)])
#define BC_INDIRECT INDIRECT(BC)
#define DE_INDIRECT INDIRECT(DE)
#define HL_INDIRECT INDIRECT(HL)

#define SET_FLAGS_ZSP(X) \
    if ((X) == 0)   SET_FLAG_Z; else RST_FLAG_Z; \
    if ((X) & 0x80) SET_FLAG_S; else RST_FLAG_S; \
    if (Parity(X))  SET_FLAG_P; else RST_FLAG_P

uint8_t Parity(uint8_t x);

#endif
