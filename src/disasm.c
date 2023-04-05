#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "disasm.h"

// This function could be a lot shorter and neater, but i cba
int DisasmSingleInstruction(char *out, uint8_t *buffer, int pc)
{
    uint8_t *op = buffer + pc;
    int opsize = 1;
    sprintf(out, "%04x\t%02x\t", pc, *op);

    switch (*op) {
    case 0x00:
        sprintf(out, "NOP");
        break;

    case 0x01:
        sprintf(out, "LXI\tB,#$%02x%02x", op[2], op[1]);
        opsize = 3;
        break;

    case 0x02:
        sprintf(out, "STAX\tB");
        break;

    case 0x03:
        sprintf(out, "INX\tB");
        break;

    case 0x04:
        sprintf(out, "INR\tB");
        break;

    case 0x05:
        sprintf(out, "DCR\tB");
        break;

    case 0x06:
        sprintf(out, "MVI\tB,#$%02x", op[1]);
        opsize = 2;
        break;

    case 0x07:
        sprintf(out, "RLC");
        break;

    case 0x08:
        sprintf(out, "[0x08 not implemented]");
        break;

    case 0x09:
        sprintf(out, "DAD\tB");
        break;

    case 0x0a:
        sprintf(out, "LDAX\tB");
        break;

    case 0x0b:
        sprintf(out, "DCX\tB");
        break;

    case 0x0c:
        sprintf(out, "INR\tC");
        break;

    case 0x0d:
        sprintf(out, "DCR\tC");
        break;

    case 0x0e:
        sprintf(out, "MVI\tC,#$%02x", op[1]);
        opsize = 2;
        break;

    case 0x0f:
        sprintf(out, "RRC");
        break;

    case 0x10:
        sprintf(out, "[0x10 not implemented]");
        break;

    case 0x11:
        sprintf(out, "LXI\tD,#$%02x%02x", op[2], op[1]);
        opsize = 3;
        break;

    case 0x12:
        sprintf(out, "STAX\tD");
        break;

    case 0x13:
        sprintf(out, "INX\tD");
        break;

    case 0x14:
        sprintf(out, "INR\tD");
        break;

    case 0x15:
        sprintf(out, "DCR\tD");
        break;

    case 0x16:
        sprintf(out, "MVI\tD,#$%02x", op[1]);
        opsize = 2;
        break;

    case 0x17:
        sprintf(out, "RAL");
        break;

    case 0x18:
        sprintf(out, "[0x18 not implemented]");
        break;

    case 0x19:
        sprintf(out, "DAD\tD");
        break;

    case 0x1a:
        sprintf(out, "LDAX\tD");
        break;

    case 0x1b:
        sprintf(out, "DCX\tD");
        break;

    case 0x1c:
        sprintf(out, "INR\tE");
        break;

    case 0x1d:
        sprintf(out, "DCR\tE");
        break;

    case 0x1e:
        sprintf(out, "MVI\tE,#$%02x", op[1]);
        opsize = 2;
        break;

    case 0x1f:
        sprintf(out, "RAR");
        break;

    case 0x20:
        sprintf(out, "[0x20 not implemented]");
        break;

    case 0x21:
        sprintf(out, "LXI\tH,#$%02x%02x", op[2], op[1]);
        opsize = 3;
        break;

    case 0x22:
        sprintf(out, "SHLD\t$%02x%02x", op[2], op[1]);
        opsize = 3;
        break;

    case 0x23:
        sprintf(out, "INX\tH");
        break;

    case 0x24:
        sprintf(out, "INR\tH");
        break;

    case 0x25:
        sprintf(out, "DCR\tH");
        break;

    case 0x26:
        sprintf(out, "MVI\tH,#$%02x", op[1]);
        opsize = 2;
        break;

    case 0x27:
        sprintf(out, "DAA");
        break;

    case 0x28:
        sprintf(out, "[0x28 not implemented]");
        break;

    case 0x29:
        sprintf(out, "DAD\tH");
        break;

    case 0x2a:
        sprintf(out, "LHLD\t$%02x%02x", op[2], op[1]);
        opsize = 3;
        break;

    case 0x2b:
        sprintf(out, "DCX\tH");
        break;

    case 0x2c:
        sprintf(out, "INR\tL");
        break;

    case 0x2d:
        sprintf(out, "DCR\tL");
        break;

    case 0x2e:
        sprintf(out, "MVI\tL,#$%02x", op[1]);
        opsize = 2;
        break;

    case 0x2f:
        sprintf(out, "CMA");
        break;

    case 0x30:
        sprintf(out, "[0x30 not implemented]");
        break;

    case 0x31:
        sprintf(out, "LXI\tSP,#$%02x%02x", op[2], op[1]);
        opsize = 3;
        break;

    case 0x32:
        sprintf(out, "STA\t$%02x%02x", op[2], op[1]);
        opsize = 3;
        break;

    case 0x33:
        sprintf(out, "INX\tSP");
        break;

    case 0x34:
        sprintf(out, "INR\tM");
        break;

    case 0x35:
        sprintf(out, "DCR\tM");
        break;

    case 0x36:
        sprintf(out, "MVI\tM,#$%02x", op[1]);
        opsize = 2;
        break;

    case 0x37:
        sprintf(out, "STC");
        break;

    case 0x38:
        sprintf(out, "[0x38 not implemented]");
        break;

    case 0x39:
        sprintf(out, "DAD\tSP");
        break;

    case 0x3a:
        sprintf(out, "LDA\t$%02x%02x", op[2], op[1]);
        opsize = 3;
        break;

    case 0x3b:
        sprintf(out, "DCX\tSP");
        break;

    case 0x3c:
        sprintf(out, "INR\tA");
        break;

    case 0x3d:
        sprintf(out, "DCR\tA");
        break;

    case 0x3e:
        sprintf(out, "MVI\tA,#$%02x", op[1]);
        opsize = 2;
        break;

    case 0x3f:
        sprintf(out, "CMC");
        break;

    case 0x40:
        sprintf(out, "MOV\tB,B");
        break;

    case 0x41:
        sprintf(out, "MOV\tB,C");
        break;

    case 0x42:
        sprintf(out, "MOV\tB,D");
        break;

    case 0x43:
        sprintf(out, "MOV\tB,E");
        break;

    case 0x44:
        sprintf(out, "MOV\tB,H");
        break;

    case 0x45:
        sprintf(out, "MOV\tB,L");
        break;

    case 0x46:
        sprintf(out, "MOV\tB,M");
        break;

    case 0x47:
        sprintf(out, "MOV\tB,A");
        break;

    case 0x48:
        sprintf(out, "MOV\tC,B");
        break;

    case 0x49:
        sprintf(out, "MOV\tC,C");
        break;

    case 0x4a:
        sprintf(out, "MOV\tC,D");
        break;

    case 0x4b:
        sprintf(out, "MOV\tC,E");
        break;
    
    case 0x4c:
        sprintf(out, "MOV\tC,H");
        break;

    case 0x4d:
        sprintf(out, "MOV\tC,L");
        break;

    case 0x4e:
        sprintf(out, "MOV\tC,M");
        break;

    case 0x4f:
        sprintf(out, "MOV\tC,A");
        break;

    case 0x50:
        sprintf(out, "MOV\tD,B");
        break;
        
    case 0x51:
        sprintf(out, "MOV\tD,C");
        break;

    case 0x52:
        sprintf(out, "MOV\tD,D");
        break;

    case 0x53:
        sprintf(out, "MOV\tD,E");
        break;

    case 0x54:
        sprintf(out, "MOV\tD,H");
        break;

    case 0x55:
        sprintf(out, "MOV\tD,L");
        break;

    case 0x56:
        sprintf(out, "MOV\tD,M");
        break;

    case 0x57:
        sprintf(out, "MOV\tD,A");    
        break;

    case 0x58:
        sprintf(out, "MOV\tE,B");
        break;

    case 0x59:
        sprintf(out, "MOV\tE,C");    
        break;

    case 0x5a:
        sprintf(out, "MOV\tE,D");    
        break;

    case 0x5b:
        sprintf(out, "MOV\tE,E");    
        break;

    case 0x5c:
        sprintf(out, "MOV\tE,H");    
        break;

    case 0x5d:
        sprintf(out, "MOV\tE,L");    
        break;

    case 0x5e:
        sprintf(out, "MOV\tE,M");    
        break;

    case 0x5f:
        sprintf(out, "MOV\tE,A");    
        break;

    case 0x60:
        sprintf(out, "MOV\tH,B");    
        break;

    case 0x61:
        sprintf(out, "MOV\tH,C");    
        break;

    case 0x62:
        sprintf(out, "MOV\tH,D");    
        break;

    case 0x63:
        sprintf(out, "MOV\tH,E");    
        break;

    case 0x64:
        sprintf(out, "MOV\tH,H");    
        break;

    case 0x65:
        sprintf(out, "MOV\tH,L");    
        break;

    case 0x66:
        sprintf(out, "MOV\tH,M");    
        break;

    case 0x67:
        sprintf(out, "MOV\tH,A");    
        break;

    case 0x68:
        sprintf(out, "MOV\tL,B");    
        break;

    case 0x69:
        sprintf(out, "MOV\tL,C");
        break;

    case 0x6a:
        sprintf(out, "MOV\tL,D");    
        break;

    case 0x6b:
        sprintf(out, "MOV\tL,E");    
        break;

    case 0x6c:
        sprintf(out, "MOV\tL,H");    
        break;

    case 0x6d:
        sprintf(out, "MOV\tL,L");    
        break;

    case 0x6e:
        sprintf(out, "MOV\tL,M");    
        break;

    case 0x6f:
        sprintf(out, "MOV\tL,A");    
        break;

    case 0x70:
        sprintf(out, "MOV\tM,B");
        break;

    case 0x71:
        sprintf(out, "MOV\tM,C");    
        break;

    case 0x72:
        sprintf(out, "MOV\tM,D");    
        break;

    case 0x73:
        sprintf(out, "MOV\tM,E");    
        break;

    case 0x74:
        sprintf(out, "MOV\tM,H");    
        break;

    case 0x75:
        sprintf(out, "MOV\tM,L");    
        break;

    case 0x76:
        sprintf(out, "HLT");
        break;

    case 0x77:
        sprintf(out, "MOV\tM,A");    
        break;

    case 0x78:
        sprintf(out, "MOV\tA,B");    
        break;

    case 0x79:
        sprintf(out, "MOV\tA,C");    
        break;

    case 0x7a:
        sprintf(out, "MOV\tA,D");    
        break;

    case 0x7b:
        sprintf(out, "MOV\tA,E");    
        break;

    case 0x7c:
        sprintf(out, "MOV\tA,H");    
        break;

    case 0x7d:
        sprintf(out, "MOV\tA,L");    
        break;

    case 0x7e:
        sprintf(out, "MOV\tA,M");    
        break;

    case 0x7f:
        sprintf(out, "MOV\tA,A");    
        break;

    case 0x80:
        sprintf(out, "ADD\tB");    
        break;

    case 0x81:
        sprintf(out, "ADD\tC");
        break;

    case 0x82:
        sprintf(out, "ADD\tD");    
        break;

    case 0x83:
        sprintf(out, "ADD\tE");    
        break;

    case 0x84:
        sprintf(out, "ADD\tH");    
        break;

    case 0x85:
        sprintf(out, "ADD\tL");    
        break;

    case 0x86:
        sprintf(out, "ADD\tM");    
        break;

    case 0x87:
        sprintf(out, "ADD\tA");    
        break;

    case 0x88:
        sprintf(out, "ADC\tB");    
        break;

    case 0x89:
        sprintf(out, "ADC\tC");    
        break;

    case 0x8a:
        sprintf(out, "ADC\tD");    
        break;

    case 0x8b:
        sprintf(out, "ADC\tE");    
        break;

    case 0x8c:
        sprintf(out, "ADC\tH");    
        break;

    case 0x8d:
        sprintf(out, "ADC\tL");    
        break;

    case 0x8e:
        sprintf(out, "ADC\tM");    
        break;

    case 0x8f:
        sprintf(out, "ADC\tA");    
        break;

    case 0x90:
        sprintf(out, "SUB\tB");    
        break;

    case 0x91:
        sprintf(out, "SUB\tC");    
        break;

    case 0x92:
        sprintf(out, "SUB\tD");    
        break;

    case 0x93:
        sprintf(out, "SUB\tE");    
        break;

    case 0x94:
        sprintf(out, "SUB\tH");    
        break;

    case 0x95:
        sprintf(out, "SUB\tL");    
        break;

    case 0x96:
        sprintf(out, "SUB\tM");    
        break;

    case 0x97:
        sprintf(out, "SUB\tA");    
        break;

    case 0x98:
        sprintf(out, "SBB\tB");    
        break;

    case 0x99:
        sprintf(out, "SBB\tC");    
        break;

    case 0x9a:
        sprintf(out, "SBB\tD");    
        break;

    case 0x9b:
        sprintf(out, "SBB\tE");    
        break;

    case 0x9c:
        sprintf(out, "SBB\tH");    
        break;

    case 0x9d:
        sprintf(out, "SBB\tL");    
        break;

    case 0x9e:
        sprintf(out, "SBB\tM");    
        break;

    case 0x9f:
        sprintf(out, "SBB\tA");    
        break;

    case 0xa0:
        sprintf(out, "ANA\tB");    
        break;

    case 0xa1:
        sprintf(out, "ANA\tC");    
        break;

    case 0xa2:
        sprintf(out, "ANA\tD");    
        break;

    case 0xa3:
        sprintf(out, "ANA\tE");    
        break;

    case 0xa4:
        sprintf(out, "ANA\tH");    
        break;

    case 0xa5:
        sprintf(out, "ANA\tL");    
        break;

    case 0xa6:
        sprintf(out, "ANA\tM");    
        break;

    case 0xa7:
        sprintf(out, "ANA\tA");    
        break;

    case 0xa8:
        sprintf(out, "XRA\tB");    
        break;

    case 0xa9:
        sprintf(out, "XRA\tC");    
        break;

    case 0xaa:
        sprintf(out, "XRA\tD");    
        break;

    case 0xab:
        sprintf(out, "XRA\tE");    
        break;

    case 0xac:
        sprintf(out, "XRA\tH");    
        break;

    case 0xad:
        sprintf(out, "XRA\tL");    
        break;

    case 0xae:
        sprintf(out, "XRA\tM");    
        break;

    case 0xaf:
        sprintf(out, "XRA\tA");    
        break;

    case 0xb0:
        sprintf(out, "ORA\tB");    
        break;

    case 0xb1:
        sprintf(out, "ORA\tC");    
        break;

    case 0xb2:
        sprintf(out, "ORA\tD");    
        break;

    case 0xb3:
        sprintf(out, "ORA\tE");    
        break;

    case 0xb4:
        sprintf(out, "ORA\tH");    
        break;

    case 0xb5:
        sprintf(out, "ORA\tL");    
        break;

    case 0xb6:
        sprintf(out, "ORA\tM");    
        break;

    case 0xb7:
        sprintf(out, "ORA\tA");    
        break;

    case 0xb8:
        sprintf(out, "CMP\tB");    
        break;

    case 0xb9:
        sprintf(out, "CMP\tC");    
        break;

    case 0xba:
        sprintf(out, "CMP\tD");    
        break;

    case 0xbb:
        sprintf(out, "CMP\tE");    
        break;

    case 0xbc:
        sprintf(out, "CMP\tH");    
        break;

    case 0xbd:
        sprintf(out, "CMP\tL");    
        break;

    case 0xbe:
        sprintf(out, "CMP\tM");    
        break;

    case 0xbf:
        sprintf(out, "CMP\tA");    
        break;

    case 0xc0:
        sprintf(out, "RNZ");    
        break;

    case 0xc1:
        sprintf(out, "POP\tB");    
        break;

    case 0xc2:
        sprintf(out, "JNZ\t$%02x%02x", op[2], op[1]);
        opsize = 3;
        break;

    case 0xc3:
        sprintf(out, "JMP\t$%02x%02x", op[2], op[1]);
        opsize = 3;
        break;

    case 0xc4:
        sprintf(out, "CNZ\t$%02x%02x", op[2], op[1]);
        opsize = 3;
        break;

    case 0xc5:
        sprintf(out, "PUSH\tB");    
        break;

    case 0xc6:
        sprintf(out, "ADI\t#$%02x", op[1]);
        opsize = 2;
        break;

    case 0xc7:
        sprintf(out, "RST\t0");    
        break;

    case 0xc8:
        sprintf(out, "RZ");    
        break;

    case 0xc9:
        sprintf(out, "RET");    
        break;

    case 0xca:
        sprintf(out, "JZ\t$%02x%02x", op[2], op[1]);
        opsize = 3;
        break;

    case 0xcb:
        sprintf(out, "[0xcb not implemented]");    
        break;

    case 0xcc:
        sprintf(out, "CZ\t$%02x%02x", op[2], op[1]);
        opsize = 3;
        break;

    case 0xcd:
        sprintf(out, "CALL\t$%02x%02x", op[2], op[1]);
        opsize = 3;
        break;

    case 0xce:
        sprintf(out, "ACI\t#$%02x", op[1]);
        opsize = 2;
        break;

    case 0xcf:
        sprintf(out, "RST\t1");    
        break;

    case 0xd0:
        sprintf(out, "RNC");    
        break;

    case 0xd1:
        sprintf(out, "POP\tD");    
        break;

    case 0xd2:
        sprintf(out, "JNC\t$%02x%02x", op[2], op[1]);
        opsize = 3;
        break;

    case 0xd3:
        sprintf(out, "OUT\t#$%02x", op[1]);
        opsize = 2;
        break;

    case 0xd4:
        sprintf(out, "CNC\t$%02x%02x", op[2], op[1]);
        opsize = 3;
        break;

    case 0xd5:
        sprintf(out, "PUSH\tD");    
        break;

    case 0xd6:
        sprintf(out, "SUI\t#$%02x", op[1]);
        opsize = 2;
        break;

    case 0xd7:
        sprintf(out, "RST\t2");    
        break;

    case 0xd8:
        sprintf(out, "RC");    
        break;

    case 0xd9:
        sprintf(out, "[0xd9 not implemented]");
        break;

    case 0xda:
        sprintf(out, "JC\t$%02x%02x", op[2], op[1]);
        opsize = 3;
        break;

    case 0xdb:
        sprintf(out, "IN\t#$%02x", op[1]);
        opsize = 2;
        break;
    
    case 0xdc:
        sprintf(out, "CC\t$%02x%02x", op[2], op[1]);
        opsize = 3;
        break;
    
    case 0xdd:
        sprintf(out, "[0xdd not implemented]");
        break;
    
    case 0xde:
        sprintf(out, "SBI\t#$%02x", op[1]);
        opsize = 2;
        break;
    
    case 0xdf:
        sprintf(out, "RST\t3");
        break;
    
    case 0xe0:
        sprintf(out, "RPO");
        break;
    
    case 0xe1:
        sprintf(out, "POP\tH");
        break;
    
    case 0xe2:
        sprintf(out, "JPO\t$%02x%02x", op[2], op[1]);
        opsize = 3;
        break;
    
    case 0xe3:
        sprintf(out, "XTHL");
        break;
    
    case 0xe4:
        sprintf(out, "CPO\t$%02x%02x", op[2], op[1]);
        opsize = 3;
        break;
    
    case 0xe5:
        sprintf(out, "PUSH\tH");
        break;
    
    case 0xe6:
        sprintf(out, "ANI\t#$%02x", op[1]);
        opsize = 2;
        break;
    
    case 0xe7:
        sprintf(out, "RST\t4");
        break;
    
    case 0xe8:
        sprintf(out, "RPE");
        break;
    
    case 0xe9:
        sprintf(out, "PCHL");
        break;
    
    case 0xea:
        sprintf(out, "JPE\t$%02x%02x", op[2], op[1]);
        opsize = 3;
        break;
    
    case 0xeb:
        sprintf(out, "XCHG");
        break;
    
    case 0xec:
        sprintf(out, "CPE\t$%02x%02x", op[2], op[1]);
        opsize = 3;
        break;
    
    case 0xed:
        sprintf(out, "[0xed not implemented]");
        break;
    
    case 0xee:
        sprintf(out, "XRI\t#$%02x", op[1]);
        opsize = 2;
        break;
    
    case 0xef:
        sprintf(out, "RST\t5");
        break;
    
    case 0xf0:
        sprintf(out, "RP");
        break;
    
    case 0xf1:
        sprintf(out, "POP\tPSW");
        break;
    
    case 0xf2:
        sprintf(out, "JP\t$%02x%02x", op[2], op[1]);
        opsize = 3;
        break;
    
    case 0xf3:
        sprintf(out, "DI");
        break;
    
    case 0xf4:
        sprintf(out, "CP\t$%02x%02x", op[2], op[1]);
        opsize = 3;
        break;
    
    case 0xf5:
        sprintf(out, "PUSH\tPSW");
        break;
    
    case 0xf6:
        sprintf(out, "ORI\t#$%02x", op[1]);
        opsize = 2;
        break;
    
    case 0xf7:
        sprintf(out, "RST\t6");
        break;
    
    case 0xf8:
        sprintf(out, "RM");
        break;
    
    case 0xf9:
        sprintf(out, "SPHL");
        break;
    
    case 0xfa:
        sprintf(out, "JM\t$%02x%02x", op[2], op[1]);
        opsize = 3;
        break;
    
    case 0xfb:
        sprintf(out, "EI");
        break;
    
    case 0xfc:
        sprintf(out, "CM\t$%02x%02x", op[2], op[1]);
        opsize = 3;
        break;
    
    case 0xfd:
        sprintf(out, "[0xfd not implemented]");
        break;
    
    case 0xfe:
        sprintf(out, "CPI\t#$%02x", op[1]);
        opsize = 2;
        break;
    
    case 0xff:
        sprintf(out, "RST 7");
        break;

    default:
        sprintf(out, "default");
        break;
    }

    sprintf(out, "\n");
    return opsize;
}
