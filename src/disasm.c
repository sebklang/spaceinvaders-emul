#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "disasm.h"

int disasmSingleInstruction(FILE *out, char *buffer, int pc)
{
    unsigned char *op = buffer + pc;
    int opsize = 1;
    fprintf(out, "%04x\t%02x\t", pc, *op);

    switch (*op) {
    case 0x00:
        fprintf(out, "NOP");
        break;

    case 0x01:
        fprintf(out, "LXI\tB,#$%02x%02x", op[2], op[1]);
        opsize = 3;
        break;

    case 0x02:
        fprintf(out, "STAX\tB");
        break;

    case 0x03:
        fprintf(out, "INX\tB");
        break;

    case 0x04:
        fprintf(out, "INR\tB");
        break;

    case 0x05:
        fprintf(out, "DCR\tB");
        break;

    case 0x06:
        fprintf(out, "MVI\tB,#$%02x", op[1]);
        opsize = 2;
        break;

    case 0x07:
        fprintf(out, "RLC");
        break;

    case 0x08:
        fprintf(out, "[0x08 not implemented]");
        break;

    case 0x09:
        fprintf(out, "DAD\tB");
        break;

    case 0x0a:
        fprintf(out, "LDAX\tB");
        break;

    case 0x0b:
        fprintf(out, "DCX\tB");
        break;

    case 0x0c:
        fprintf(out, "INR\tC");
        break;

    case 0x0d:
        fprintf(out, "DCR\tC");
        break;

    case 0x0e:
        fprintf(out, "MVI\tC,#$%02x", op[1]);
        opsize = 2;
        break;

    case 0x0f:
        fprintf(out, "RRC");
        break;

    case 0x10:
        fprintf(out, "[0x10 not implemented]");
        break;

    case 0x11:
        fprintf(out, "LXI\tD,#$%02x%02x", op[2], op[1]);
        opsize = 3;
        break;

    case 0x12:
        fprintf(out, "STAX\tD");
        break;

    case 0x13:
        fprintf(out, "INX\tD");
        break;

    case 0x14:
        fprintf(out, "INR\tD");
        break;

    case 0x15:
        fprintf(out, "DCR\tD");
        break;

    case 0x16:
        fprintf(out, "MVI\tD,#$%02x", op[1]);
        opsize = 2;
        break;

    case 0x17:
        fprintf(out, "RAL");
        break;

    case 0x18:
        fprintf(out, "[0x18 not implemented]");
        break;

    case 0x19:
        fprintf(out, "DAD\tD");
        break;

    case 0x1a:
        fprintf(out, "LDAX\tD");
        break;

    case 0x1b:
        fprintf(out, "DCX\tD");
        break;

    case 0x1c:
        fprintf(out, "INR\tE");
        break;

    case 0x1d:
        fprintf(out, "DCR\tE");
        break;

    case 0x1e:
        fprintf(out, "MVI\tE,#$%02x", op[1]);
        opsize = 2;
        break;

    case 0x1f:
        fprintf(out, "RAR");
        break;

    case 0x20:
        fprintf(out, "[0x20 not implemented]");
        break;

    case 0x21:
        fprintf(out, "LXI\tH,#$%02x%02x", op[2], op[1]);
        opsize = 3;
        break;

    case 0x22:
        fprintf(out, "SHLD\t$%02x%02x", op[2], op[1]);
        opsize = 3;
        break;

    case 0x23:
        fprintf(out, "INX\tH");
        break;

    case 0x24:
        fprintf(out, "INR\tH");
        break;

    case 0x25:
        fprintf(out, "DCR\tH");
        break;

    case 0x26:
        fprintf(out, "MVI\tH,#$%02x", op[1]);
        opsize = 2;
        break;

    case 0x27:
        fprintf(out, "DAA");
        break;

    case 0x28:
        fprintf(out, "[0x28 not implemented]");
        break;

    case 0x29:
        fprintf(out, "DAD\tH");
        break;

    case 0x2a:
        fprintf(out, "LHLD\t$%02x%02x", op[2], op[1]);
        opsize = 3;
        break;

    case 0x2b:
        fprintf(out, "DCX\tH");
        break;

    case 0x2c:
        fprintf(out, "INR\tL");
        break;

    case 0x2d:
        fprintf(out, "DCR\tL");
        break;

    case 0x2e:
        fprintf(out, "MVI\tL,#$%02x", op[1]);
        opsize = 2;
        break;

    case 0x2f:
        fprintf(out, "CMA");
        break;

    case 0x30:
        fprintf(out, "[0x30 not implemented]");
        break;

    case 0x31:
        fprintf(out, "LXI\tSP,#$%02x%02x", op[2], op[1]);
        opsize = 3;
        break;

    case 0x32:
        fprintf(out, "STA\t$%02x%02x", op[2], op[1]);
        opsize = 3;
        break;

    case 0x33:
        fprintf(out, "INX\tSP");
        break;

    case 0x34:
        fprintf(out, "INR\tM");
        break;

    case 0x35:
        fprintf(out, "DCR\tM");
        break;

    case 0x36:
        fprintf(out, "MVI\tM,#$%02x", op[1]);
        opsize = 2;
        break;

    case 0x37:
        fprintf(out, "STC");
        break;

    case 0x38:
        fprintf(out, "[0x38 not implemented]");
        break;

    case 0x39:
        fprintf(out, "DAD\tSP");
        break;

    case 0x3a:
        fprintf(out, "LDA\t$%02x%02x", op[2], op[1]);
        opsize = 3;
        break;

    case 0x3b:
        fprintf(out, "DCX\tSP");
        break;

    case 0x3c:
        fprintf(out, "INR\tA");
        break;

    case 0x3d:
        fprintf(out, "DCR\tA");
        break;

    case 0x3e:
        fprintf(out, "MVI\tA,#$%02x", op[1]);
        opsize = 2;
        break;

    case 0x3f:
        fprintf(out, "CMC");
        break;

    case 0x40:
        fprintf(out, "MOV\tB,B");
        break;

    case 0x41:
        fprintf(out, "MOV\tB,C");
        break;

    case 0x42:
        fprintf(out, "MOV\tB,D");
        break;

    case 0x43:
        fprintf(out, "MOV\tB,E");
        break;

    case 0x44:
        fprintf(out, "MOV\tB,H");
        break;

    case 0x45:
        fprintf(out, "MOV\tB,L");
        break;

    case 0x46:
        fprintf(out, "MOV\tB,M");
        break;

    case 0x47:
        fprintf(out, "MOV\tB,A");
        break;

    case 0x48:
        fprintf(out, "MOV\tC,B");
        break;

    case 0x49:
        fprintf(out, "MOV\tC,C");
        break;

    case 0x4a:
        fprintf(out, "MOV\tC,D");
        break;

    case 0x4b:
        fprintf(out, "MOV\tC,E");
        break;
    
    case 0x4c:
        fprintf(out, "MOV\tC,H");
        break;

    case 0x4d:
        fprintf(out, "MOV\tC,L");
        break;

    case 0x4e:
        fprintf(out, "MOV\tC,M");
        break;

    case 0x4f:
        fprintf(out, "MOV\tC,A");
        break;

    case 0x50:
        fprintf(out, "MOV\tD,B");
        break;
        
    case 0x51:
        fprintf(out, "MOV\tD,C");
        break;

    case 0x52:
        fprintf(out, "MOV\tD,D");
        break;

    case 0x53:
        fprintf(out, "MOV\tD,E");
        break;

    case 0x54:
        fprintf(out, "MOV\tD,H");
        break;

    case 0x55:
        fprintf(out, "MOV\tD,L");
        break;

    case 0x56:
        fprintf(out, "MOV\tD,M");
        break;

    case 0x57:
        fprintf(out, "MOV\tD,A");    
        break;

    case 0x58:
        fprintf(out, "MOV\tE,B");
        break;

    case 0x59:
        fprintf(out, "MOV\tE,C");    
        break;

    case 0x5a:
        fprintf(out, "MOV\tE,D");    
        break;

    case 0x5b:
        fprintf(out, "MOV\tE,E");    
        break;

    case 0x5c:
        fprintf(out, "MOV\tE,H");    
        break;

    case 0x5d:
        fprintf(out, "MOV\tE,L");    
        break;

    case 0x5e:
        fprintf(out, "MOV\tE,M");    
        break;

    case 0x5f:
        fprintf(out, "MOV\tE,A");    
        break;

    case 0x60:
        fprintf(out, "MOV\tH,B");    
        break;

    case 0x61:
        fprintf(out, "MOV\tH,C");    
        break;

    case 0x62:
        fprintf(out, "MOV\tH,D");    
        break;

    case 0x63:
        fprintf(out, "MOV\tH,E");    
        break;

    case 0x64:
        fprintf(out, "MOV\tH,H");    
        break;

    case 0x65:
        fprintf(out, "MOV\tH,L");    
        break;

    case 0x66:
        fprintf(out, "MOV\tH,M");    
        break;

    case 0x67:
        fprintf(out, "MOV\tH,A");    
        break;

    case 0x68:
        fprintf(out, "MOV\tL,B");    
        break;

    case 0x69:
        fprintf(out, "MOV\tL,C");
        break;

    case 0x6a:
        fprintf(out, "MOV\tL,D");    
        break;

    case 0x6b:
        fprintf(out, "MOV\tL,E");    
        break;

    case 0x6c:
        fprintf(out, "MOV\tL,H");    
        break;

    case 0x6d:
        fprintf(out, "MOV\tL,L");    
        break;

    case 0x6e:
        fprintf(out, "MOV\tL,M");    
        break;

    case 0x6f:
        fprintf(out, "MOV\tL,A");    
        break;

    case 0x70:
        fprintf(out, "MOV\tM,B");
        break;

    case 0x71:
        fprintf(out, "MOV\tM,C");    
        break;

    case 0x72:
        fprintf(out, "MOV\tM,D");    
        break;

    case 0x73:
        fprintf(out, "MOV\tM,E");    
        break;

    case 0x74:
        fprintf(out, "MOV\tM,H");    
        break;

    case 0x75:
        fprintf(out, "MOV\tM,L");    
        break;

    case 0x76:
        fprintf(out, "HLT");
        break;

    case 0x77:
        fprintf(out, "MOV\tM,A");    
        break;

    case 0x78:
        fprintf(out, "MOV\tA,B");    
        break;

    case 0x79:
        fprintf(out, "MOV\tA,C");    
        break;

    case 0x7a:
        fprintf(out, "MOV\tA,D");    
        break;

    case 0x7b:
        fprintf(out, "MOV\tA,E");    
        break;

    case 0x7c:
        fprintf(out, "MOV\tA,H");    
        break;

    case 0x7d:
        fprintf(out, "MOV\tA,L");    
        break;

    case 0x7e:
        fprintf(out, "MOV\tA,M");    
        break;

    case 0x7f:
        fprintf(out, "MOV\tA,A");    
        break;

    case 0x80:
        fprintf(out, "ADD\tB");    
        break;

    case 0x81:
        fprintf(out, "ADD\tC");
        break;

    case 0x82:
        fprintf(out, "ADD\tD");    
        break;

    case 0x83:
        fprintf(out, "ADD\tE");    
        break;

    case 0x84:
        fprintf(out, "ADD\tH");    
        break;

    case 0x85:
        fprintf(out, "ADD\tL");    
        break;

    case 0x86:
        fprintf(out, "ADD\tM");    
        break;

    case 0x87:
        fprintf(out, "ADD\tA");    
        break;

    case 0x88:
        fprintf(out, "ADC\tB");    
        break;

    case 0x89:
        fprintf(out, "ADC\tC");    
        break;

    case 0x8a:
        fprintf(out, "ADC\tD");    
        break;

    case 0x8b:
        fprintf(out, "ADC\tE");    
        break;

    case 0x8c:
        fprintf(out, "ADC\tH");    
        break;

    case 0x8d:
        fprintf(out, "ADC\tL");    
        break;

    case 0x8e:
        fprintf(out, "ADC\tM");    
        break;

    case 0x8f:
        fprintf(out, "ADC\tA");    
        break;

    case 0x90:
        fprintf(out, "SUB\tB");    
        break;

    case 0x91:
        fprintf(out, "SUB\tC");    
        break;

    case 0x92:
        fprintf(out, "SUB\tD");    
        break;

    case 0x93:
        fprintf(out, "SUB\tE");    
        break;

    case 0x94:
        fprintf(out, "SUB\tH");    
        break;

    case 0x95:
        fprintf(out, "SUB\tL");    
        break;

    case 0x96:
        fprintf(out, "SUB\tM");    
        break;

    case 0x97:
        fprintf(out, "SUB\tA");    
        break;

    case 0x98:
        fprintf(out, "SBB\tB");    
        break;

    case 0x99:
        fprintf(out, "SBB\tC");    
        break;

    case 0x9a:
        fprintf(out, "SBB\tD");    
        break;

    case 0x9b:
        fprintf(out, "SBB\tE");    
        break;

    case 0x9c:
        fprintf(out, "SBB\tH");    
        break;

    case 0x9d:
        fprintf(out, "SBB\tL");    
        break;

    case 0x9e:
        fprintf(out, "SBB\tM");    
        break;

    case 0x9f:
        fprintf(out, "SBB\tA");    
        break;

    case 0xa0:
        fprintf(out, "ANA\tB");    
        break;

    case 0xa1:
        fprintf(out, "ANA\tC");    
        break;

    case 0xa2:
        fprintf(out, "ANA\tD");    
        break;

    case 0xa3:
        fprintf(out, "ANA\tE");    
        break;

    case 0xa4:
        fprintf(out, "ANA\tH");    
        break;

    case 0xa5:
        fprintf(out, "ANA\tL");    
        break;

    case 0xa6:
        fprintf(out, "ANA\tM");    
        break;

    case 0xa7:
        fprintf(out, "ANA\tA");    
        break;

    case 0xa8:
        fprintf(out, "XRA\tB");    
        break;

    case 0xa9:
        fprintf(out, "XRA\tC");    
        break;

    case 0xaa:
        fprintf(out, "XRA\tD");    
        break;

    case 0xab:
        fprintf(out, "XRA\tE");    
        break;

    case 0xac:
        fprintf(out, "XRA\tH");    
        break;

    case 0xad:
        fprintf(out, "XRA\tL");    
        break;

    case 0xae:
        fprintf(out, "XRA\tM");    
        break;

    case 0xaf:
        fprintf(out, "XRA\tA");    
        break;

    case 0xb0:
        fprintf(out, "ORA\tB");    
        break;

    case 0xb1:
        fprintf(out, "ORA\tC");    
        break;

    case 0xb2:
        fprintf(out, "ORA\tD");    
        break;

    case 0xb3:
        fprintf(out, "ORA\tE");    
        break;

    case 0xb4:
        fprintf(out, "ORA\tH");    
        break;

    case 0xb5:
        fprintf(out, "ORA\tL");    
        break;

    case 0xb6:
        fprintf(out, "ORA\tM");    
        break;

    case 0xb7:
        fprintf(out, "ORA\tA");    
        break;

    case 0xb8:
        fprintf(out, "CMP\tB");    
        break;

    case 0xb9:
        fprintf(out, "CMP\tC");    
        break;

    case 0xba:
        fprintf(out, "CMP\tD");    
        break;

    case 0xbb:
        fprintf(out, "CMP\tE");    
        break;

    case 0xbc:
        fprintf(out, "CMP\tH");    
        break;

    case 0xbd:
        fprintf(out, "CMP\tL");    
        break;

    case 0xbe:
        fprintf(out, "CMP\tM");    
        break;

    case 0xbf:
        fprintf(out, "CMP\tA");    
        break;

    case 0xc0:
        fprintf(out, "RNZ");    
        break;

    case 0xc1:
        fprintf(out, "POP\tB");    
        break;

    case 0xc2:
        fprintf(out, "JNZ\t$%02x%02x", op[2], op[1]);
        opsize = 3;
        break;

    case 0xc3:
        fprintf(out, "JMP\t$%02x%02x", op[2], op[1]);
        opsize = 3;
        break;

    case 0xc4:
        fprintf(out, "CNZ\t$%02x%02x", op[2], op[1]);
        opsize = 3;
        break;

    case 0xc5:
        fprintf(out, "PUSH\tB");    
        break;

    case 0xc6:
        fprintf(out, "ADI\t#$%02x", op[1]);
        opsize = 2;
        break;

    case 0xc7:
        fprintf(out, "RST\t0");    
        break;

    case 0xc8:
        fprintf(out, "RZ");    
        break;

    case 0xc9:
        fprintf(out, "RET");    
        break;

    case 0xca:
        fprintf(out, "JZ\t$%02x%02x", op[2], op[1]);
        opsize = 3;
        break;

    case 0xcb:
        fprintf(out, "[0xcb not implemented]");    
        break;

    case 0xcc:
        fprintf(out, "CZ\t$%02x%02x", op[2], op[1]);
        opsize = 3;
        break;

    case 0xcd:
        fprintf(out, "CALL\t$%02x%02x", op[2], op[1]);
        opsize = 3;
        break;

    case 0xce:
        fprintf(out, "ACI\t#$%02x", op[1]);
        opsize = 2;
        break;

    case 0xcf:
        fprintf(out, "RST\t1");    
        break;

    case 0xd0:
        fprintf(out, "RNC");    
        break;

    case 0xd1:
        fprintf(out, "POP\tD");    
        break;

    case 0xd2:
        fprintf(out, "JNC\t$%02x%02x", op[2], op[1]);
        opsize = 3;
        break;

    case 0xd3:
        fprintf(out, "OUT\t#$%02x", op[1]);
        opsize = 2;
        break;

    case 0xd4:
        fprintf(out, "CNC\t$%02x%02x", op[2], op[1]);
        opsize = 3;
        break;

    case 0xd5:
        fprintf(out, "PUSH\tD");    
        break;

    case 0xd6:
        fprintf(out, "SUI\t#$%02x", op[1]);
        opsize = 2;
        break;

    case 0xd7:
        fprintf(out, "RST\t2");    
        break;

    case 0xd8:
        fprintf(out, "RC");    
        break;

    case 0xd9:
        fprintf(out, "[0xd9 not implemented]");
        break;

    case 0xda:
        fprintf(out, "JC\t$%02x%02x", op[2], op[1]);
        opsize = 3;
        break;

    case 0xdb:
        fprintf(out, "IN\t#$%02x", op[1]);
        opsize = 2;
        break;
    
    case 0xdc:
        fprintf(out, "CC\t$%02x%02x", op[2], op[1]);
        opsize = 3;
        break;
    
    case 0xdd:
        fprintf(out, "[0xdd not implemented]");
        break;
    
    case 0xde:
        fprintf(out, "SBI\t#$%02x", op[1]);
        opsize = 2;
        break;
    
    case 0xdf:
        fprintf(out, "RST\t3");
        break;
    
    case 0xe0:
        fprintf(out, "RPO");
        break;
    
    case 0xe1:
        fprintf(out, "POP\tH");
        break;
    
    case 0xe2:
        fprintf(out, "JPO\t$%02x%02x", op[2], op[1]);
        opsize = 3;
        break;
    
    case 0xe3:
        fprintf(out, "XTHL");
        break;
    
    case 0xe4:
        fprintf(out, "CPO\t$%02x%02x", op[2], op[1]);
        opsize = 3;
        break;
    
    case 0xe5:
        fprintf(out, "PUSH\tH");
        break;
    
    case 0xe6:
        fprintf(out, "ANI\t#$%02x", op[1]);
        opsize = 2;
        break;
    
    case 0xe7:
        fprintf(out, "RST\t4");
        break;
    
    case 0xe8:
        fprintf(out, "RPE");
        break;
    
    case 0xe9:
        fprintf(out, "PCHL");
        break;
    
    case 0xea:
        fprintf(out, "JPE\t$%02x%02x", op[2], op[1]);
        opsize = 3;
        break;
    
    case 0xeb:
        fprintf(out, "XCHG");
        break;
    
    case 0xec:
        fprintf(out, "CPE\t$%02x%02x", op[2], op[1]);
        opsize = 3;
        break;
    
    case 0xed:
        fprintf(out, "[0xed not implemented]");
        break;
    
    case 0xee:
        fprintf(out, "XRI\t#$%02x", op[1]);
        opsize = 2;
        break;
    
    case 0xef:
        fprintf(out, "RST\t5");
        break;
    
    case 0xf0:
        fprintf(out, "RP");
        break;
    
    case 0xf1:
        fprintf(out, "POP\tPSW");
        break;
    
    case 0xf2:
        fprintf(out, "JP\t$%02x%02x", op[2], op[1]);
        opsize = 3;
        break;
    
    case 0xf3:
        fprintf(out, "DI");
        break;
    
    case 0xf4:
        fprintf(out, "CP\t$%02x%02x", op[2], op[1]);
        opsize = 3;
        break;
    
    case 0xf5:
        fprintf(out, "PUSH\tPSW");
        break;
    
    case 0xf6:
        fprintf(out, "ORI\t#$%02x", op[1]);
        opsize = 2;
        break;
    
    case 0xf7:
        fprintf(out, "RST\t6");
        break;
    
    case 0xf8:
        fprintf(out, "RM");
        break;
    
    case 0xf9:
        fprintf(out, "SPHL");
        break;
    
    case 0xfa:
        fprintf(out, "JM\t$%02x%02x", op[2], op[1]);
        opsize = 3;
        break;
    
    case 0xfb:
        fprintf(out, "EI");
        break;
    
    case 0xfc:
        fprintf(out, "CM\t$%02x%02x", op[2], op[1]);
        opsize = 3;
        break;
    
    case 0xfd:
        fprintf(out, "[0xfd not implemented]");
        break;
    
    case 0xfe:
        fprintf(out, "CPI\t#$%02x", op[1]);
        opsize = 2;
        break;
    
    case 0xff:
        fprintf(out, "RST 7");
        break;

    default:
        fprintf(out, "default");
        break;
    }

    fprintf(out, "\n");
    return opsize;
}
