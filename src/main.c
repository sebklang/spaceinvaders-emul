#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "emulator.h"
#include "macros.h"
#include "disasm.h"
#include "debug.h"

#define DEBUG_FRAME_LENGTH 10

int main(int argc, char *argv[])
{
    FILE *file;
    int filesize;
    uint8_t *memory;
    bool printState;
    char dbgstrs[DEBUG_FRAME_LENGTH][256] = {0};
    EmulatorState state_;
    char disasmOut[256];

    EmulatorState *state = &state_;
    int  const memsize   = 1 << 16;
    char const *const fn = "bin/invaders.rom";
    DebugFrame dbg_ = {(char **) dbgstrs, DEBUG_FRAME_LENGTH, 0};
    DebugFrame *dbg = &dbg_;

    // Initialize memory from ROM file
    if ((file = fopen(fn, "rb")) == NULL) {
        printf("Failed to open file %s for reading. Exiting...", fn);
        return 1;
    }
    fseek(file, 0L, SEEK_END);
    filesize = ftell(file);
    memory = malloc(memsize);
    fread(memory, filesize, 1, file);
    fclose(file);
    fseek(file, 0L, SEEK_SET);
    // -----

    InitEmulator(state, memory, memsize, NULL, NULL);
    printState = true;

    while (PC < MEMSIZE) {
        // Output
        if (printState) {
            for (int i = 0; i < 10; i++) printf("\n");
            printf("Current state:\nA = %02x\nBC = %02x %02x\n", A, B, C);
            printf("DE = %02x %02x\nHL = %02x %02x\n", D, E, H, L);
            printf("SP = %02x %02x\n", SP_HI, SP_LO);
            printf("PC = %02x %02x\n", PC_HI, PC_LO);
            printf("Flag byte = %02x\n", FLAG_BYTE);
            printf("    Sign = %d\n    Zero = %d\n    ----\n", FLAG_S, FLAG_Z);
            printf("    Aux Carry = %d\n    ----\n    Parity = %d\n", FLAG_AC, FLAG_P);
            printf("    ----\n    Carry = %d\n", FLAG_C);
            printf("Halted = %d\nIrq Enable = %d\n\n", HALTED, INT_ENABLE);

            printf("Type the number of instructions to execute,\nor press enter to execute the next instruction.\n");
            printf("Next instruction to be executed is:\n");
            DisasmSingleInstruction(disasmOut, memory, PC);
            printf("%s", disasmOut); 
        }
        printState = true;

        // Input
        char inString[256];
        fgets(inString, 256, stdin);
        int numIter = 0;

        if (inString[0] == '\n') {
            numIter = 1;
        }
        else if (strcmp(inString, "ps\n") == 0) {
            printf("--- Stack ---\n");
            printf("Address | Value\n");
            for (int i = 0x23ff; i >= SP; i--) { // 0x2400 is specific to space invaders
                printf("%04x    | %02x\n", i, *GetMem(state, i));
            }
            printf("--- End of stack ---\n");
        }
        else {
            numIter = atoi(inString);
        }

        if (numIter == 0) printState = false;

        // Execution
        for (int i = 0; i < numIter; i++) {
            WriteLnToFrame(dbg, state);

            if (!EmulateInstruction(state)) {
                printf("Fatal error! Printing last %d executed instructions...\n", dbg->size);
                PrintFrame(dbg);
            }
        }
    }

    printf("Reached end of memory.\n");
    return 0;
}
