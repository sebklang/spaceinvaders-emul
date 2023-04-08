#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "disasm.h"

// This function could be a lot shorter and neater, but i cba
int DisasmSingleInstruction(char *out, uint8_t *buffer, int pc)
{
    char instr[32];
    uint8_t *op = buffer + pc;
    int opsize = 1;
    #define ADR_OP_STR "%04x\t%02x\t"
    sprintf(out, ADR_OP_STR, pc, *op);
    out += sizeof ADR_OP_STR - 1;
    #undef ADR_OP_STR

    switch (*op) {
    case 0x00:
        sprintf(instr, "NOP");
        break;

    case 0x01:
        sprintf(instr, "LXI\tB,#$%02x%02x", op[2], op[1]);
        opsize = 3;
        break;

    case 0x02:
        sprintf(instr, "STAX\tB");
        break;

    case 0x03:
        sprintf(instr, "INX\tB");
        break;

    case 0x04:
        sprintf(instr, "INR\tB");
        break;

    case 0x05:
        sprintf(instr, "DCR\tB");
        break;

    case 0x06:
        sprintf(instr, "MVI\tB,#$%02x", op[1]);
        opsize = 2;
        break;

    case 0x07:
        sprintf(instr, "RLC");
        break;

    case 0x08:
        sprintf(instr, "[0x08 not implemented]");
        break;

    case 0x09:
        sprintf(instr, "DAD\tB");
        break;

    case 0x0a:
        sprintf(instr, "LDAX\tB");
        break;

    case 0x0b:
        sprintf(instr, "DCX\tB");
        break;

    case 0x0c:
        sprintf(instr, "INR\tC");
        break;

    case 0x0d:
        sprintf(instr, "DCR\tC");
        break;

    case 0x0e:
        sprintf(instr, "MVI\tC,#$%02x", op[1]);
        opsize = 2;
        break;

    case 0x0f:
        sprintf(instr, "RRC");
        break;

    case 0x10:
        sprintf(instr, "[0x10 not implemented]");
        break;

    case 0x11:
        sprintf(instr, "LXI\tD,#$%02x%02x", op[2], op[1]);
        opsize = 3;
        break;

    case 0x12:
        sprintf(instr, "STAX\tD");
        break;

    case 0x13:
        sprintf(instr, "INX\tD");
        break;

    case 0x14:
        sprintf(instr, "INR\tD");
        break;

    case 0x15:
        sprintf(instr, "DCR\tD");
        break;

    case 0x16:
        sprintf(instr, "MVI\tD,#$%02x", op[1]);
        opsize = 2;
        break;

    case 0x17:
        sprintf(instr, "RAL");
        break;

    case 0x18:
        sprintf(instr, "[0x18 not implemented]");
        break;

    case 0x19:
        sprintf(instr, "DAD\tD");
        break;

    case 0x1a:
        sprintf(instr, "LDAX\tD");
        break;

    case 0x1b:
        sprintf(instr, "DCX\tD");
        break;

    case 0x1c:
        sprintf(instr, "INR\tE");
        break;

    case 0x1d:
        sprintf(instr, "DCR\tE");
        break;

    case 0x1e:
        sprintf(instr, "MVI\tE,#$%02x", op[1]);
        opsize = 2;
        break;

    case 0x1f:
        sprintf(instr, "RAR");
        break;

    case 0x20:
        sprintf(instr, "[0x20 not implemented]");
        break;

    case 0x21:
        sprintf(instr, "LXI\tH,#$%02x%02x", op[2], op[1]);
        opsize = 3;
        break;

    case 0x22:
        sprintf(instr, "SHLD\t$%02x%02x", op[2], op[1]);
        opsize = 3;
        break;

    case 0x23:
        sprintf(instr, "INX\tH");
        break;

    case 0x24:
        sprintf(instr, "INR\tH");
        break;

    case 0x25:
        sprintf(instr, "DCR\tH");
        break;

    case 0x26:
        sprintf(instr, "MVI\tH,#$%02x", op[1]);
        opsize = 2;
        break;

    case 0x27:
        sprintf(instr, "DAA");
        break;

    case 0x28:
        sprintf(instr, "[0x28 not implemented]");
        break;

    case 0x29:
        sprintf(instr, "DAD\tH");
        break;

    case 0x2a:
        sprintf(instr, "LHLD\t$%02x%02x", op[2], op[1]);
        opsize = 3;
        break;

    case 0x2b:
        sprintf(instr, "DCX\tH");
        break;

    case 0x2c:
        sprintf(instr, "INR\tL");
        break;

    case 0x2d:
        sprintf(instr, "DCR\tL");
        break;

    case 0x2e:
        sprintf(instr, "MVI\tL,#$%02x", op[1]);
        opsize = 2;
        break;

    case 0x2f:
        sprintf(instr, "CMA");
        break;

    case 0x30:
        sprintf(instr, "[0x30 not implemented]");
        break;

    case 0x31:
        sprintf(instr, "LXI\tSP,#$%02x%02x", op[2], op[1]);
        opsize = 3;
        break;

    case 0x32:
        sprintf(instr, "STA\t$%02x%02x", op[2], op[1]);
        opsize = 3;
        break;

    case 0x33:
        sprintf(instr, "INX\tSP");
        break;

    case 0x34:
        sprintf(instr, "INR\tM");
        break;

    case 0x35:
        sprintf(instr, "DCR\tM");
        break;

    case 0x36:
        sprintf(instr, "MVI\tM,#$%02x", op[1]);
        opsize = 2;
        break;

    case 0x37:
        sprintf(instr, "STC");
        break;

    case 0x38:
        sprintf(instr, "[0x38 not implemented]");
        break;

    case 0x39:
        sprintf(instr, "DAD\tSP");
        break;

    case 0x3a:
        sprintf(instr, "LDA\t$%02x%02x", op[2], op[1]);
        opsize = 3;
        break;

    case 0x3b:
        sprintf(instr, "DCX\tSP");
        break;

    case 0x3c:
        sprintf(instr, "INR\tA");
        break;

    case 0x3d:
        sprintf(instr, "DCR\tA");
        break;

    case 0x3e:
        sprintf(instr, "MVI\tA,#$%02x", op[1]);
        opsize = 2;
        break;

    case 0x3f:
        sprintf(instr, "CMC");
        break;

    case 0x40:
        sprintf(instr, "MOV\tB,B");
        break;

    case 0x41:
        sprintf(instr, "MOV\tB,C");
        break;

    case 0x42:
        sprintf(instr, "MOV\tB,D");
        break;

    case 0x43:
        sprintf(instr, "MOV\tB,E");
        break;

    case 0x44:
        sprintf(instr, "MOV\tB,H");
        break;

    case 0x45:
        sprintf(instr, "MOV\tB,L");
        break;

    case 0x46:
        sprintf(instr, "MOV\tB,M");
        break;

    case 0x47:
        sprintf(instr, "MOV\tB,A");
        break;

    case 0x48:
        sprintf(instr, "MOV\tC,B");
        break;

    case 0x49:
        sprintf(instr, "MOV\tC,C");
        break;

    case 0x4a:
        sprintf(instr, "MOV\tC,D");
        break;

    case 0x4b:
        sprintf(instr, "MOV\tC,E");
        break;
    
    case 0x4c:
        sprintf(instr, "MOV\tC,H");
        break;

    case 0x4d:
        sprintf(instr, "MOV\tC,L");
        break;

    case 0x4e:
        sprintf(instr, "MOV\tC,M");
        break;

    case 0x4f:
        sprintf(instr, "MOV\tC,A");
        break;

    case 0x50:
        sprintf(instr, "MOV\tD,B");
        break;
        
    case 0x51:
        sprintf(instr, "MOV\tD,C");
        break;

    case 0x52:
        sprintf(instr, "MOV\tD,D");
        break;

    case 0x53:
        sprintf(instr, "MOV\tD,E");
        break;

    case 0x54:
        sprintf(instr, "MOV\tD,H");
        break;

    case 0x55:
        sprintf(instr, "MOV\tD,L");
        break;

    case 0x56:
        sprintf(instr, "MOV\tD,M");
        break;

    case 0x57:
        sprintf(instr, "MOV\tD,A");    
        break;

    case 0x58:
        sprintf(instr, "MOV\tE,B");
        break;

    case 0x59:
        sprintf(instr, "MOV\tE,C");    
        break;

    case 0x5a:
        sprintf(instr, "MOV\tE,D");    
        break;

    case 0x5b:
        sprintf(instr, "MOV\tE,E");    
        break;

    case 0x5c:
        sprintf(instr, "MOV\tE,H");    
        break;

    case 0x5d:
        sprintf(instr, "MOV\tE,L");    
        break;

    case 0x5e:
        sprintf(instr, "MOV\tE,M");    
        break;

    case 0x5f:
        sprintf(instr, "MOV\tE,A");    
        break;

    case 0x60:
        sprintf(instr, "MOV\tH,B");    
        break;

    case 0x61:
        sprintf(instr, "MOV\tH,C");    
        break;

    case 0x62:
        sprintf(instr, "MOV\tH,D");    
        break;

    case 0x63:
        sprintf(instr, "MOV\tH,E");    
        break;

    case 0x64:
        sprintf(instr, "MOV\tH,H");    
        break;

    case 0x65:
        sprintf(instr, "MOV\tH,L");    
        break;

    case 0x66:
        sprintf(instr, "MOV\tH,M");    
        break;

    case 0x67:
        sprintf(instr, "MOV\tH,A");    
        break;

    case 0x68:
        sprintf(instr, "MOV\tL,B");    
        break;

    case 0x69:
        sprintf(instr, "MOV\tL,C");
        break;

    case 0x6a:
        sprintf(instr, "MOV\tL,D");    
        break;

    case 0x6b:
        sprintf(instr, "MOV\tL,E");    
        break;

    case 0x6c:
        sprintf(instr, "MOV\tL,H");    
        break;

    case 0x6d:
        sprintf(instr, "MOV\tL,L");    
        break;

    case 0x6e:
        sprintf(instr, "MOV\tL,M");    
        break;

    case 0x6f:
        sprintf(instr, "MOV\tL,A");    
        break;

    case 0x70:
        sprintf(instr, "MOV\tM,B");
        break;

    case 0x71:
        sprintf(instr, "MOV\tM,C");    
        break;

    case 0x72:
        sprintf(instr, "MOV\tM,D");    
        break;

    case 0x73:
        sprintf(instr, "MOV\tM,E");    
        break;

    case 0x74:
        sprintf(instr, "MOV\tM,H");    
        break;

    case 0x75:
        sprintf(instr, "MOV\tM,L");    
        break;

    case 0x76:
        sprintf(instr, "HLT");
        break;

    case 0x77:
        sprintf(instr, "MOV\tM,A");    
        break;

    case 0x78:
        sprintf(instr, "MOV\tA,B");    
        break;

    case 0x79:
        sprintf(instr, "MOV\tA,C");    
        break;

    case 0x7a:
        sprintf(instr, "MOV\tA,D");    
        break;

    case 0x7b:
        sprintf(instr, "MOV\tA,E");    
        break;

    case 0x7c:
        sprintf(instr, "MOV\tA,H");    
        break;

    case 0x7d:
        sprintf(instr, "MOV\tA,L");    
        break;

    case 0x7e:
        sprintf(instr, "MOV\tA,M");    
        break;

    case 0x7f:
        sprintf(instr, "MOV\tA,A");    
        break;

    case 0x80:
        sprintf(instr, "ADD\tB");    
        break;

    case 0x81:
        sprintf(instr, "ADD\tC");
        break;

    case 0x82:
        sprintf(instr, "ADD\tD");    
        break;

    case 0x83:
        sprintf(instr, "ADD\tE");    
        break;

    case 0x84:
        sprintf(instr, "ADD\tH");    
        break;

    case 0x85:
        sprintf(instr, "ADD\tL");    
        break;

    case 0x86:
        sprintf(instr, "ADD\tM");    
        break;

    case 0x87:
        sprintf(instr, "ADD\tA");    
        break;

    case 0x88:
        sprintf(instr, "ADC\tB");    
        break;

    case 0x89:
        sprintf(instr, "ADC\tC");    
        break;

    case 0x8a:
        sprintf(instr, "ADC\tD");    
        break;

    case 0x8b:
        sprintf(instr, "ADC\tE");    
        break;

    case 0x8c:
        sprintf(instr, "ADC\tH");    
        break;

    case 0x8d:
        sprintf(instr, "ADC\tL");    
        break;

    case 0x8e:
        sprintf(instr, "ADC\tM");    
        break;

    case 0x8f:
        sprintf(instr, "ADC\tA");    
        break;

    case 0x90:
        sprintf(instr, "SUB\tB");    
        break;

    case 0x91:
        sprintf(instr, "SUB\tC");    
        break;

    case 0x92:
        sprintf(instr, "SUB\tD");    
        break;

    case 0x93:
        sprintf(instr, "SUB\tE");    
        break;

    case 0x94:
        sprintf(instr, "SUB\tH");    
        break;

    case 0x95:
        sprintf(instr, "SUB\tL");    
        break;

    case 0x96:
        sprintf(instr, "SUB\tM");    
        break;

    case 0x97:
        sprintf(instr, "SUB\tA");    
        break;

    case 0x98:
        sprintf(instr, "SBB\tB");    
        break;

    case 0x99:
        sprintf(instr, "SBB\tC");    
        break;

    case 0x9a:
        sprintf(instr, "SBB\tD");    
        break;

    case 0x9b:
        sprintf(instr, "SBB\tE");    
        break;

    case 0x9c:
        sprintf(instr, "SBB\tH");    
        break;

    case 0x9d:
        sprintf(instr, "SBB\tL");    
        break;

    case 0x9e:
        sprintf(instr, "SBB\tM");    
        break;

    case 0x9f:
        sprintf(instr, "SBB\tA");    
        break;

    case 0xa0:
        sprintf(instr, "ANA\tB");    
        break;

    case 0xa1:
        sprintf(instr, "ANA\tC");    
        break;

    case 0xa2:
        sprintf(instr, "ANA\tD");    
        break;

    case 0xa3:
        sprintf(instr, "ANA\tE");    
        break;

    case 0xa4:
        sprintf(instr, "ANA\tH");    
        break;

    case 0xa5:
        sprintf(instr, "ANA\tL");    
        break;

    case 0xa6:
        sprintf(instr, "ANA\tM");    
        break;

    case 0xa7:
        sprintf(instr, "ANA\tA");    
        break;

    case 0xa8:
        sprintf(instr, "XRA\tB");    
        break;

    case 0xa9:
        sprintf(instr, "XRA\tC");    
        break;

    case 0xaa:
        sprintf(instr, "XRA\tD");    
        break;

    case 0xab:
        sprintf(instr, "XRA\tE");    
        break;

    case 0xac:
        sprintf(instr, "XRA\tH");    
        break;

    case 0xad:
        sprintf(instr, "XRA\tL");    
        break;

    case 0xae:
        sprintf(instr, "XRA\tM");    
        break;

    case 0xaf:
        sprintf(instr, "XRA\tA");    
        break;

    case 0xb0:
        sprintf(instr, "ORA\tB");    
        break;

    case 0xb1:
        sprintf(instr, "ORA\tC");    
        break;

    case 0xb2:
        sprintf(instr, "ORA\tD");    
        break;

    case 0xb3:
        sprintf(instr, "ORA\tE");    
        break;

    case 0xb4:
        sprintf(instr, "ORA\tH");    
        break;

    case 0xb5:
        sprintf(instr, "ORA\tL");    
        break;

    case 0xb6:
        sprintf(instr, "ORA\tM");    
        break;

    case 0xb7:
        sprintf(instr, "ORA\tA");    
        break;

    case 0xb8:
        sprintf(instr, "CMP\tB");    
        break;

    case 0xb9:
        sprintf(instr, "CMP\tC");    
        break;

    case 0xba:
        sprintf(instr, "CMP\tD");    
        break;

    case 0xbb:
        sprintf(instr, "CMP\tE");    
        break;

    case 0xbc:
        sprintf(instr, "CMP\tH");    
        break;

    case 0xbd:
        sprintf(instr, "CMP\tL");    
        break;

    case 0xbe:
        sprintf(instr, "CMP\tM");    
        break;

    case 0xbf:
        sprintf(instr, "CMP\tA");    
        break;

    case 0xc0:
        sprintf(instr, "RNZ");    
        break;

    case 0xc1:
        sprintf(instr, "POP\tB");    
        break;

    case 0xc2:
        sprintf(instr, "JNZ\t$%02x%02x", op[2], op[1]);
        opsize = 3;
        break;

    case 0xc3:
        sprintf(instr, "JMP\t$%02x%02x", op[2], op[1]);
        opsize = 3;
        break;

    case 0xc4:
        sprintf(instr, "CNZ\t$%02x%02x", op[2], op[1]);
        opsize = 3;
        break;

    case 0xc5:
        sprintf(instr, "PUSH\tB");    
        break;

    case 0xc6:
        sprintf(instr, "ADI\t#$%02x", op[1]);
        opsize = 2;
        break;

    case 0xc7:
        sprintf(instr, "RST\t0");    
        break;

    case 0xc8:
        sprintf(instr, "RZ");    
        break;

    case 0xc9:
        sprintf(instr, "RET");    
        break;

    case 0xca:
        sprintf(instr, "JZ\t$%02x%02x", op[2], op[1]);
        opsize = 3;
        break;

    case 0xcb:
        sprintf(instr, "[0xcb not implemented]");    
        break;

    case 0xcc:
        sprintf(instr, "CZ\t$%02x%02x", op[2], op[1]);
        opsize = 3;
        break;

    case 0xcd:
        sprintf(instr, "CALL\t$%02x%02x", op[2], op[1]);
        opsize = 3;
        break;

    case 0xce:
        sprintf(instr, "ACI\t#$%02x", op[1]);
        opsize = 2;
        break;

    case 0xcf:
        sprintf(instr, "RST\t1");    
        break;

    case 0xd0:
        sprintf(instr, "RNC");    
        break;

    case 0xd1:
        sprintf(instr, "POP\tD");    
        break;

    case 0xd2:
        sprintf(instr, "JNC\t$%02x%02x", op[2], op[1]);
        opsize = 3;
        break;

    case 0xd3:
        sprintf(instr, "OUT\t#$%02x", op[1]);
        opsize = 2;
        break;

    case 0xd4:
        sprintf(instr, "CNC\t$%02x%02x", op[2], op[1]);
        opsize = 3;
        break;

    case 0xd5:
        sprintf(instr, "PUSH\tD");    
        break;

    case 0xd6:
        sprintf(instr, "SUI\t#$%02x", op[1]);
        opsize = 2;
        break;

    case 0xd7:
        sprintf(instr, "RST\t2");    
        break;

    case 0xd8:
        sprintf(instr, "RC");    
        break;

    case 0xd9:
        sprintf(instr, "[0xd9 not implemented]");
        break;

    case 0xda:
        sprintf(instr, "JC\t$%02x%02x", op[2], op[1]);
        opsize = 3;
        break;

    case 0xdb:
        sprintf(instr, "IN\t#$%02x", op[1]);
        opsize = 2;
        break;
    
    case 0xdc:
        sprintf(instr, "CC\t$%02x%02x", op[2], op[1]);
        opsize = 3;
        break;
    
    case 0xdd:
        sprintf(instr, "[0xdd not implemented]");
        break;
    
    case 0xde:
        sprintf(instr, "SBI\t#$%02x", op[1]);
        opsize = 2;
        break;
    
    case 0xdf:
        sprintf(instr, "RST\t3");
        break;
    
    case 0xe0:
        sprintf(instr, "RPO");
        break;
    
    case 0xe1:
        sprintf(instr, "POP\tH");
        break;
    
    case 0xe2:
        sprintf(instr, "JPO\t$%02x%02x", op[2], op[1]);
        opsize = 3;
        break;
    
    case 0xe3:
        sprintf(instr, "XTHL");
        break;
    
    case 0xe4:
        sprintf(instr, "CPO\t$%02x%02x", op[2], op[1]);
        opsize = 3;
        break;
    
    case 0xe5:
        sprintf(instr, "PUSH\tH");
        break;
    
    case 0xe6:
        sprintf(instr, "ANI\t#$%02x", op[1]);
        opsize = 2;
        break;
    
    case 0xe7:
        sprintf(instr, "RST\t4");
        break;
    
    case 0xe8:
        sprintf(instr, "RPE");
        break;
    
    case 0xe9:
        sprintf(instr, "PCHL");
        break;
    
    case 0xea:
        sprintf(instr, "JPE\t$%02x%02x", op[2], op[1]);
        opsize = 3;
        break;
    
    case 0xeb:
        sprintf(instr, "XCHG");
        break;
    
    case 0xec:
        sprintf(instr, "CPE\t$%02x%02x", op[2], op[1]);
        opsize = 3;
        break;
    
    case 0xed:
        sprintf(instr, "[0xed not implemented]");
        break;
    
    case 0xee:
        sprintf(instr, "XRI\t#$%02x", op[1]);
        opsize = 2;
        break;
    
    case 0xef:
        sprintf(instr, "RST\t5");
        break;
    
    case 0xf0:
        sprintf(instr, "RP");
        break;
    
    case 0xf1:
        sprintf(instr, "POP\tPSW");
        break;
    
    case 0xf2:
        sprintf(instr, "JP\t$%02x%02x", op[2], op[1]);
        opsize = 3;
        break;
    
    case 0xf3:
        sprintf(instr, "DI");
        break;
    
    case 0xf4:
        sprintf(instr, "CP\t$%02x%02x", op[2], op[1]);
        opsize = 3;
        break;
    
    case 0xf5:
        sprintf(instr, "PUSH\tPSW");
        break;
    
    case 0xf6:
        sprintf(instr, "ORI\t#$%02x", op[1]);
        opsize = 2;
        break;
    
    case 0xf7:
        sprintf(instr, "RST\t6");
        break;
    
    case 0xf8:
        sprintf(instr, "RM");
        break;
    
    case 0xf9:
        sprintf(instr, "SPHL");
        break;
    
    case 0xfa:
        sprintf(instr, "JM\t$%02x%02x", op[2], op[1]);
        opsize = 3;
        break;
    
    case 0xfb:
        sprintf(instr, "EI");
        break;
    
    case 0xfc:
        sprintf(instr, "CM\t$%02x%02x", op[2], op[1]);
        opsize = 3;
        break;
    
    case 0xfd:
        sprintf(instr, "[0xfd not implemented]");
        break;
    
    case 0xfe:
        sprintf(instr, "CPI\t#$%02x", op[1]);
        opsize = 2;
        break;
    
    case 0xff:
        sprintf(instr, "RST 7");
        break;

    default:
        sprintf(instr, "default");
        break;
    }
    strcpy(out, instr);
    strcat(out, "\n");
    return opsize;
}
