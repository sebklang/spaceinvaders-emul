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
    char  dbgstrs[DEBUG_FRAME_LENGTH][64] = {0};
    char *dbgptrs[DEBUG_FRAME_LENGTH];
    EmulatorState state_;
    char disasmOut[64];

    EmulatorState *state = &state_;
    int  const memsize   = 1 << 16;
    char const *const filename = "bin/invaders.rom";
    DebugFrame dbg_ = {(char **) dbgptrs, DEBUG_FRAME_LENGTH, 0};
    DebugFrame *dbg = &dbg_;
    bool printState = true;

    // Initialize dbgptrs. (Do not use dbg_ or dbg before this)
    for (int i = 0; i < DEBUG_FRAME_LENGTH; i++) {
        dbgptrs[i] = dbgstrs[i];
    }

    // Initialize memory from ROM file
    if ((file = fopen(filename, "rb")) == NULL) {
        printf("Failed to open file %s for reading. Exiting...", filename);
        return 1;
    }
    fseek(file, 0L, SEEK_END);
    filesize = ftell(file);
    fseek(file, 0L, SEEK_SET);
    memory = malloc(memsize);
    fread(memory, filesize, 1, file);
    fclose(file);
    // -----

    InitEmulator(state, memory, memsize, NULL, NULL);

    while (PC < MEMSIZE) {
        // Output
        if (printState) { // Starts true
            for (int i = 0; i < 10; i++) printf("\n");
            printf("Current state:\n"
            "A = %02x\nBC = %02x %02x\n"
            "DE = %02x %02x\nHL = %02x %02x\n"
            "SP = %02x %02x\nPC = %02x %02x\n"
            "Flag byte = %02x\n"
            "    Sign = %d\n    Zero = %d\n    ----\n"
            "    Aux Carry = %d\n    ----\n    Parity = %d\n"
            "    ----\n    Carry = %d\n"
            "Halted = %d\nIrq Enable = %d\n\n"
            "Type the number of instructions to execute,\n"
            "or press enter to execute the next instruction.\n"
            "Next instruction to be executed is:\n",
            A, B, C, D, E, H, L, SP_HI, SP_LO, PC_HI, PC_LO,
            FLAG_BYTE, FLAG_S, FLAG_Z, FLAG_AC, FLAG_P, FLAG_C,
            HALTED, INT_ENABLE);

            DisasmSingleInstruction(disasmOut, memory, PC);
            printf("%s", disasmOut); 
        }
        printState = true;

        // Input
        char inString[256];
        fgets(inString, 256, stdin);
        int numIter = 0;
        long int dest;

        if (inString[0] == '\n') {
            numIter = 1;
        }
        else if (strcmp(inString, "ps\n") == 0) {
            printf("--- Stack ---\nAddress | Value\n");
            for (int i = 0x23ff; i >= SP; i--) { // 0x2400 is specific to space invaders
                printf("%04x    | %02x\n", i, *GetMem(state, i));
            }
            printf("--- End of stack ---\n");
        }
        else if (strcmp(inString, "pf\n") == 0) {
            printf("Printing last up to %d executed instructions.\n", DEBUG_FRAME_LENGTH);
            PrintFrame(dbg);
        }
        else if (strcmp(inString, "q\n") == 0) {
            printf("Exiting.\n");
            return 0;
        }
        else if (memcmp(inString, "gm ", 3) == 0 && (dest = strtol(inString[3], NULL, 16)) != 0) {
            uint8_t *dataptr = GetMem(state, dest);
            if (dataptr) {
                printf("Memory @ %04x: %02x\n", dest, *dataptr);
            }
            else {
                printf("Invalid address.\n");
            }
        }
        else if (memcmp(inString, "gr ", 3) == 0) {
            uint8_t *dataptr = NULL;
            char *regstr = NULL;
            switch (inString[3])
            {
            case 'B':
            case 'b':
                dataptr = GetMem(state, BC);
                regstr = "BC";
                break;
            case 'D':
            case 'd':
                dataptr = GetMem(state, DE);
                regstr = "DE";
                break;
            case 'H':
            case 'h':
                dataptr = GetMem(state, HL);
                regstr = "HL";
                break;
            case 'S':
            case 's':
                dataptr = GetMem(state, SP);
                regstr = "SP";
                break;
            case 'P':
            case 'p':
                dataptr = GetMem(state, PC);
                regstr = "PC";
                break;
            default:
                dataptr = NULL;
                break;
            }
            if (dataptr && regstr) {
                printf("Memory @ %s (%04x): %02x", regstr, dataptr, *dataptr);
            }
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

