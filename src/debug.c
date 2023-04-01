#include <stdio.h>
#include "debug.h"
#include "disasm.h"
#include "macros.h"
/// @brief Defined in GNU stdio.h
FILE *fmemopen (void *buf, size_t size, const char *opentype);

void WriteLnToFrame(DebugFrame *frame, EmulatorState *state)
{
    FILE *dbgstream = fmemopen(frame->arr[frame->cur], 256, "w");
    DisasmSingleInstruction(dbgstream, state->memory, PC);
    frame->cur++;
    frame->cur %= frame->size;
    fclose(dbgstream);
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
