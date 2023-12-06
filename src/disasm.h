#ifndef DISASM_H
#define DISASM_H

#include <stdio.h>
#include <stdint.h>

#define FILE_ENDING ".asm"

#ifdef __cplusplus
extern "C" {
#endif

int DisasmSingleInstruction(const char *, uint8_t *, int);

#ifdef __cplusplus
}
#endif

#endif
