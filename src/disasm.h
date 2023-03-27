#ifndef DISASM_H
#define DISASM_H

#include <stdio.h>
#include <stdint.h>

#define FILE_ENDING ".asm"
int DisasmSingleInstruction(FILE*, uint8_t*, int);

#endif
