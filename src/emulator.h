#ifndef EMULATOR_H
#define EMULATOR_H

#include <stdint.h>
#include <stdbool.h>
#include "io.h"

typedef uint32_t memsize_t;

typedef struct Bytes {
    uint8_t lo, hi; // This order is important
} Bytes;

typedef union Word {
    Bytes bytes;
    uint16_t word;
} Word;

typedef struct EmulatorState {
    uint8_t a;
    Word bc, de, hl, sp, pc, instrPtr;
    uint8_t *memory;
    memsize_t memsize;
    uint8_t flags;
    bool halted;
    bool intEnable;
    InputHandler inputHandler;
    OutputHandler outputHandler;
} EmulatorState;

void InitEmulator(EmulatorState *state, uint8_t *memory, memsize_t memsize, InputHandler ih, OutputHandler oh);
bool EmulateInstruction(EmulatorState *state);

#endif
