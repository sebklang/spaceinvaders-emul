#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "disasm.h"

int main(int argc, char **argv)
{
    if (argc < 2) {
        printf("Missing input file argument. Exiting...");
        return EXIT_FAILURE;
    }
    
    FILE *file;
    if ((file = fopen(argv[1], "rb")) == NULL) {
        printf("Failed to open file %s for reading. Exiting...", argv[1]);
        return EXIT_FAILURE;
    }
    fseek(file, 0L, SEEK_END);
    int filesize = ftell(file);
    fseek(file, 0L, SEEK_SET);

    unsigned char *rom = malloc(filesize);

    fread(rom, filesize, 1, file);
    fclose(file);

    char *outfname = malloc(strlen(argv[1]) + sizeof FILE_ENDING);
    strcpy(outfname, argv[1]);
    strcpy(outfname + strlen(argv[1]), FILE_ENDING);
    FILE *out;
    if ((out = fopen(outfname, "w")) == NULL) {
        printf("Failed to open file %s for writing. Exiting...", outfname);
        return EXIT_FAILURE;
    }

    int pc = 0;
    while (pc < filesize) {
        pc += disasmSingleInstruction(out, rom, pc);
    }

    fclose(out);
    return EXIT_SUCCESS;
}
