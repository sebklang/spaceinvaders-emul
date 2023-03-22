#ifndef EMULATOR_H
#define EMULATOR_H

#include <stdint.h>

typedef struct Bytes {
    uint8_t lo, hi; // This order is important
} Bytes;

typedef union Word {
    Bytes bytes;
    uint16_t word;
} Word;

typedef struct EmulatorFlags {
    uint8_t s  : 1;
    uint8_t z  : 1;
    uint8_t _1 : 1; // Pad 1
    uint8_t ac : 1;
    uint8_t _2 : 1; // Pad 2
    uint8_t p  : 1;
    uint8_t _3 : 1; // Pad 3
    uint8_t c  : 1;
} EmulatorFlags;

typedef union FlagUnion {
    EmulatorFlags fields;
    uint8_t byte;
} FlagUnion;

typedef struct EmulatorState {
    uint8_t a;
    Word bc, de, hl, sp, pc;
    uint8_t *memory;
    union FlagUnion flags;
} EmulatorState;

void InitEmulator(uint8_t *memory, EmulatorState *state);
void EmulateInstruction(EmulatorState *state);

#endif
