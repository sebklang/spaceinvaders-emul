#ifndef EMULATOR_H
#define EMULATOR_H

#include <stdint.h>

typedef struct EmulatorFlags {
    uint8_t s : 1;
    uint8_t z : 1;
    uint8_t p : 1;
    uint8_t c : 1;
    uint8_t ac : 1;
} EmulatorFlags;

typedef struct EmulatorState {
    uint8_t a, b, c, d, e, h, l;
    uint16_t sp, pc;
    uint8_t *memory;
    struct EmulatorFlags flags;
} EmulatorState;

void InitEmulator(uint8_t *memory, EmulatorState *state);
void EmulateInstruction(EmulatorState *state);

#endif
