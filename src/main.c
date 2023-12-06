#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "emulator.h"
#include "macros.h"
#include "disasm.h"
#include "debug.h"

#define DEBUG_FRAME_LENGTH 10

uint8_t *StringToReg(EmulatorState *state, char *input, char **regstr)
{
    switch (input[3])
    {
    case 'B':
    case 'b':
        *regstr = "BC";
        return GetMem(state, BC);
        break;
    case 'D':
    case 'd':
        *regstr = "DE";
        return GetMem(state, DE);
        break;
    case 'H':
    case 'h':
        *regstr = "HL";
        return GetMem(state, HL);
        break;
    case 'S':
    case 's':
        *regstr = "SP";
        return GetMem(state, SP);
        break;
    case 'P':
    case 'p':
        *regstr = "PC";
        return GetMem(state, PC);
        break;
    default:
        break;
    }
    return NULL;
}

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
        char input[256];
        fgets(input, 256, stdin);
        int numIter = 0;
        long int dest;

        if (input[0] == '\n') {
            numIter = 1;
        }

        else if (strcmp(input, "ps\n") == 0) {
            printf("--- Stack ---\nAddress | Value\n");
            for (int i = 0x23ff; i >= SP; i--) { // 0x2400 is specific to space invaders
                printf("%04x    | %02x\n", i, *GetMem(state, i));
            }
            printf("--- End of stack ---\n");
        }

        else if (strcmp(input, "pf\n") == 0) {
            printf("Printing last up to %d executed instructions.\n", DEBUG_FRAME_LENGTH);
            PrintFrame(dbg);
        }

        else if (strcmp(input, "q\n") == 0) {
            printf("Exiting.\n");
            return 0;
        }

        else if (memcmp(input, "gm ", 3) == 0) {
            dest = strtol(&input[3], NULL, 16);
            if (dest >= 0 && dest <= 0xffff) {
                uint8_t *dataptr = GetMem(state, dest);
                if (dataptr) {
                    printf("Memory @ %04x: %02x\n", dest, *dataptr);
                }
                else {
                    printf("Impossible error.\n");
                }
            }
            else {
                printf("Invalid address.\n");
            }
        }

        else if (memcmp(input, "gr ", 3) == 0) {
            char *regstr;
            uint8_t *dataptr = StringToReg(state, input, &regstr);
            if (dataptr && regstr) {
                uint16_t loc = dataptr - GetMem(state, 0);
                printf("Memory @ %s (%04x): %02x\n", regstr, loc, *dataptr);
            }
        }

        else {
            numIter = atoi(input);
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
