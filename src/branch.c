#include <stdbool.h>
#include "emulator.h"
#include "macros.h"

#define RET \
    

/// @brief Emulate one of the 8080's branch instructions
/// @param state Pointer to state initialized using InitEmulator(...)
/// @param op Direct pointer to instruction inside ROM memory
bool EmulateBranch(EmulatorState *state, uint8_t *op)
{

    /*
    case 0xc0: case 0xc2: case 0xc3: case 0xc4:
    case 0xc7: case 0xc8: case 0xc9: case 0xca:
    case 0xcc: case 0xcd: case 0xcf: case 0xd0:
    case 0xd2: case 0xd4: case 0xd7: case 0xd8:
    case 0xda: case 0xdc: case 0xdf: case 0xe0:
    case 0xe2: case 0xe4: case 0xe7: case 0xe8:
    case 0xe9: case 0xea: case 0xec: case 0xef:
    case 0xf0: case 0xf2: case 0xf4: case 0xf7:
    case 0xf8: case 0xfa: case 0xfc: case 0xff:
    */

    switch (*op)
    {
    case 0xc0: // RNZ
        
        break;
    
    default:
        break;
    }

    return true;
}
