#include "emulator.h"

typedef struct DebugFrame {
    char **const arr;
    const int size;
    int cur;
} DebugFrame;

void WriteLnToFrame(DebugFrame *frame, EmulatorState *state);

void PrintFrame(DebugFrame *frame);

