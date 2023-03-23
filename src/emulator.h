#ifndef EMULATOR_H
#define EMULATOR_H

#include <stdint.h>

typedef uint32_t memsize_t;

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
    memsize_t memsize;
    union FlagUnion flags;
    bool halted;
    bool intEnable;
} EmulatorState;

void InitEmulator(uint8_t *memory, memsize_t memsize, EmulatorState *state);
bool EmulateInstruction(EmulatorState *state);

#endif
