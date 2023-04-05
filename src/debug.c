#include <stdio.h>
#include "debug.h"
#include "disasm.h"
#include "macros.h"
/// @brief Defined in GNU stdio.h
FILE *fmemopen (void *buf, size_t size, const char *opentype);

void WriteLnToFrame(DebugFrame *frame, EmulatorState *state)
{
    DisasmSingleInstruction(frame->arr[frame->cur], state->memory, PC);
    frame->cur++;
    frame->cur %= frame->size;
}

void PrintFrame(DebugFrame *frame)
{
    int i = frame->cur;
    do {
        printf("%s", frame->arr[i]);
        i++;
        i %= frame->size;
    } while (i != frame->cur);
}
