#include "z80.h"
opcode z80opmap[0xFF] = {
// 0, 
// 1, 
// 22, 
// 33, 
// 62, 
// 118, 
// 120, 
// 121, 
// 124, 
// 125, 
// 195, 
// 201, 
// 211, 
	{ "INSN_00_NOP", FLAGS_NONE, OPCODE_NOP, 1, 11, ( REG_NONE ), ( REG_NONE ) },
	{ "INSN_01_LOAD_BC", FLAGS_NONE, OPCODE_LOAD16, 3, 11, ( REG_BC ), ( REG_NONE ) },
	{ "NULL", FLAGS_NONE, OPCODE_NONE, 0, 11, ( REG_NONE ), ( REG_NONE ) },
	{ "NULL", FLAGS_NONE, OPCODE_NONE, 0, 11, ( REG_NONE ), ( REG_NONE ) },
	{ "NULL", FLAGS_NONE, OPCODE_NONE, 0, 11, ( REG_NONE ), ( REG_NONE ) },
	{ "NULL", FLAGS_NONE, OPCODE_NONE, 0, 11, ( REG_NONE ), ( REG_NONE ) },
	{ "NULL", FLAGS_NONE, OPCODE_NONE, 0, 11, ( REG_NONE ), ( REG_NONE ) },
	{ "NULL", FLAGS_NONE, OPCODE_NONE, 0, 11, ( REG_NONE ), ( REG_NONE ) },
	{ "NULL", FLAGS_NONE, OPCODE_NONE, 0, 11, ( REG_NONE ), ( REG_NONE ) },
	{ "NULL", FLAGS_NONE, OPCODE_NONE, 0, 11, ( REG_NONE ), ( REG_NONE ) },
	{ "NULL", FLAGS_NONE, OPCODE_NONE, 0, 11, ( REG_NONE ), ( REG_NONE ) },
	{ "NULL", FLAGS_NONE, OPCODE_NONE, 0, 11, ( REG_NONE ), ( REG_NONE ) },
	{ "NULL", FLAGS_NONE, OPCODE_NONE, 0, 11, ( REG_NONE ), ( REG_NONE ) },
	{ "NULL", FLAGS_NONE, OPCODE_NONE, 0, 11, ( REG_NONE ), ( REG_NONE ) },
	{ "NULL", FLAGS_NONE, OPCODE_NONE, 0, 11, ( REG_NONE ), ( REG_NONE ) },
	{ "NULL", FLAGS_NONE, OPCODE_NONE, 0, 11, ( REG_NONE ), ( REG_NONE ) },
	{ "NULL", FLAGS_NONE, OPCODE_NONE, 0, 11, ( REG_NONE ), ( REG_NONE ) },
	{ "NULL", FLAGS_NONE, OPCODE_NONE, 0, 11, ( REG_NONE ), ( REG_NONE ) },
	{ "NULL", FLAGS_NONE, OPCODE_NONE, 0, 11, ( REG_NONE ), ( REG_NONE ) },
	{ "NULL", FLAGS_NONE, OPCODE_NONE, 0, 11, ( REG_NONE ), ( REG_NONE ) },
	{ "NULL", FLAGS_NONE, OPCODE_NONE, 0, 11, ( REG_NONE ), ( REG_NONE ) },
	{ "NULL", FLAGS_NONE, OPCODE_NONE, 0, 11, ( REG_NONE ), ( REG_NONE ) },
	{ "INSN_16_LOAD_D", FLAGS_NONE, OPCODE_LOAD8, 2, 11, ( REG_D ), ( REG_NONE ) },
	{ "NULL", FLAGS_NONE, OPCODE_NONE, 0, 11, ( REG_NONE ), ( REG_NONE ) },
	{ "NULL", FLAGS_NONE, OPCODE_NONE, 0, 11, ( REG_NONE ), ( REG_NONE ) },
	{ "NULL", FLAGS_NONE, OPCODE_NONE, 0, 11, ( REG_NONE ), ( REG_NONE ) },
	{ "NULL", FLAGS_NONE, OPCODE_NONE, 0, 11, ( REG_NONE ), ( REG_NONE ) },
	{ "NULL", FLAGS_NONE, OPCODE_NONE, 0, 11, ( REG_NONE ), ( REG_NONE ) },
	{ "NULL", FLAGS_NONE, OPCODE_NONE, 0, 11, ( REG_NONE ), ( REG_NONE ) },
	{ "NULL", FLAGS_NONE, OPCODE_NONE, 0, 11, ( REG_NONE ), ( REG_NONE ) },
	{ "NULL", FLAGS_NONE, OPCODE_NONE, 0, 11, ( REG_NONE ), ( REG_NONE ) },
	{ "NULL", FLAGS_NONE, OPCODE_NONE, 0, 11, ( REG_NONE ), ( REG_NONE ) },
	{ "NULL", FLAGS_NONE, OPCODE_NONE, 0, 11, ( REG_NONE ), ( REG_NONE ) },
	{ "INSN_21_LOAD_HL", FLAGS_NONE, OPCODE_LOAD16, 3, 11, ( REG_HL ), ( REG_NONE ) },
	{ "NULL", FLAGS_NONE, OPCODE_NONE, 0, 11, ( REG_NONE ), ( REG_NONE ) },
	{ "NULL", FLAGS_NONE, OPCODE_NONE, 0, 11, ( REG_NONE ), ( REG_NONE ) },
	{ "NULL", FLAGS_NONE, OPCODE_NONE, 0, 11, ( REG_NONE ), ( REG_NONE ) },
	{ "NULL", FLAGS_NONE, OPCODE_NONE, 0, 11, ( REG_NONE ), ( REG_NONE ) },
	{ "NULL", FLAGS_NONE, OPCODE_NONE, 0, 11, ( REG_NONE ), ( REG_NONE ) },
	{ "NULL", FLAGS_NONE, OPCODE_NONE, 0, 11, ( REG_NONE ), ( REG_NONE ) },
	{ "NULL", FLAGS_NONE, OPCODE_NONE, 0, 11, ( REG_NONE ), ( REG_NONE ) },
	{ "NULL", FLAGS_NONE, OPCODE_NONE, 0, 11, ( REG_NONE ), ( REG_NONE ) },
	{ "NULL", FLAGS_NONE, OPCODE_NONE, 0, 11, ( REG_NONE ), ( REG_NONE ) },
	{ "NULL", FLAGS_NONE, OPCODE_NONE, 0, 11, ( REG_NONE ), ( REG_NONE ) },
	{ "NULL", FLAGS_NONE, OPCODE_NONE, 0, 11, ( REG_NONE ), ( REG_NONE ) },
	{ "NULL", FLAGS_NONE, OPCODE_NONE, 0, 11, ( REG_NONE ), ( REG_NONE ) },
	{ "NULL", FLAGS_NONE, OPCODE_NONE, 0, 11, ( REG_NONE ), ( REG_NONE ) },
	{ "NULL", FLAGS_NONE, OPCODE_NONE, 0, 11, ( REG_NONE ), ( REG_NONE ) },
	{ "NULL", FLAGS_NONE, OPCODE_NONE, 0, 11, ( REG_NONE ), ( REG_NONE ) },
	{ "NULL", FLAGS_NONE, OPCODE_NONE, 0, 11, ( REG_NONE ), ( REG_NONE ) },
	{ "NULL", FLAGS_NONE, OPCODE_NONE, 0, 11, ( REG_NONE ), ( REG_NONE ) },
	{ "NULL", FLAGS_NONE, OPCODE_NONE, 0, 11, ( REG_NONE ), ( REG_NONE ) },
	{ "NULL", FLAGS_NONE, OPCODE_NONE, 0, 11, ( REG_NONE ), ( REG_NONE ) },
	{ "NULL", FLAGS_NONE, OPCODE_NONE, 0, 11, ( REG_NONE ), ( REG_NONE ) },
	{ "NULL", FLAGS_NONE, OPCODE_NONE, 0, 11, ( REG_NONE ), ( REG_NONE ) },
	{ "NULL", FLAGS_NONE, OPCODE_NONE, 0, 11, ( REG_NONE ), ( REG_NONE ) },
	{ "NULL", FLAGS_NONE, OPCODE_NONE, 0, 11, ( REG_NONE ), ( REG_NONE ) },
	{ "NULL", FLAGS_NONE, OPCODE_NONE, 0, 11, ( REG_NONE ), ( REG_NONE ) },
	{ "NULL", FLAGS_NONE, OPCODE_NONE, 0, 11, ( REG_NONE ), ( REG_NONE ) },
	{ "NULL", FLAGS_NONE, OPCODE_NONE, 0, 11, ( REG_NONE ), ( REG_NONE ) },
	{ "NULL", FLAGS_NONE, OPCODE_NONE, 0, 11, ( REG_NONE ), ( REG_NONE ) },
	{ "NULL", FLAGS_NONE, OPCODE_NONE, 0, 11, ( REG_NONE ), ( REG_NONE ) },
	{ "INSN_3E_LOAD_A", FLAGS_NONE, OPCODE_LOAD8, 2, 11, ( REG_A ), ( REG_NONE ) },
	{ "NULL", FLAGS_NONE, OPCODE_NONE, 0, 11, ( REG_NONE ), ( REG_NONE ) },
	{ "NULL", FLAGS_NONE, OPCODE_NONE, 0, 11, ( REG_NONE ), ( REG_NONE ) },
	{ "NULL", FLAGS_NONE, OPCODE_NONE, 0, 11, ( REG_NONE ), ( REG_NONE ) },
	{ "NULL", FLAGS_NONE, OPCODE_NONE, 0, 11, ( REG_NONE ), ( REG_NONE ) },
	{ "NULL", FLAGS_NONE, OPCODE_NONE, 0, 11, ( REG_NONE ), ( REG_NONE ) },
	{ "NULL", FLAGS_NONE, OPCODE_NONE, 0, 11, ( REG_NONE ), ( REG_NONE ) },
	{ "NULL", FLAGS_NONE, OPCODE_NONE, 0, 11, ( REG_NONE ), ( REG_NONE ) },
	{ "NULL", FLAGS_NONE, OPCODE_NONE, 0, 11, ( REG_NONE ), ( REG_NONE ) },
	{ "NULL", FLAGS_NONE, OPCODE_NONE, 0, 11, ( REG_NONE ), ( REG_NONE ) },
	{ "NULL", FLAGS_NONE, OPCODE_NONE, 0, 11, ( REG_NONE ), ( REG_NONE ) },
	{ "NULL", FLAGS_NONE, OPCODE_NONE, 0, 11, ( REG_NONE ), ( REG_NONE ) },
	{ "NULL", FLAGS_NONE, OPCODE_NONE, 0, 11, ( REG_NONE ), ( REG_NONE ) },
	{ "NULL", FLAGS_NONE, OPCODE_NONE, 0, 11, ( REG_NONE ), ( REG_NONE ) },
	{ "NULL", FLAGS_NONE, OPCODE_NONE, 0, 11, ( REG_NONE ), ( REG_NONE ) },
	{ "NULL", FLAGS_NONE, OPCODE_NONE, 0, 11, ( REG_NONE ), ( REG_NONE ) },
	{ "NULL", FLAGS_NONE, OPCODE_NONE, 0, 11, ( REG_NONE ), ( REG_NONE ) },
	{ "NULL", FLAGS_NONE, OPCODE_NONE, 0, 11, ( REG_NONE ), ( REG_NONE ) },
	{ "NULL", FLAGS_NONE, OPCODE_NONE, 0, 11, ( REG_NONE ), ( REG_NONE ) },
	{ "NULL", FLAGS_NONE, OPCODE_NONE, 0, 11, ( REG_NONE ), ( REG_NONE ) },
	{ "NULL", FLAGS_NONE, OPCODE_NONE, 0, 11, ( REG_NONE ), ( REG_NONE ) },
	{ "NULL", FLAGS_NONE, OPCODE_NONE, 0, 11, ( REG_NONE ), ( REG_NONE ) },
	{ "NULL", FLAGS_NONE, OPCODE_NONE, 0, 11, ( REG_NONE ), ( REG_NONE ) },
	{ "NULL", FLAGS_NONE, OPCODE_NONE, 0, 11, ( REG_NONE ), ( REG_NONE ) },
	{ "NULL", FLAGS_NONE, OPCODE_NONE, 0, 11, ( REG_NONE ), ( REG_NONE ) },
	{ "NULL", FLAGS_NONE, OPCODE_NONE, 0, 11, ( REG_NONE ), ( REG_NONE ) },
	{ "NULL", FLAGS_NONE, OPCODE_NONE, 0, 11, ( REG_NONE ), ( REG_NONE ) },
	{ "NULL", FLAGS_NONE, OPCODE_NONE, 0, 11, ( REG_NONE ), ( REG_NONE ) },
	{ "NULL", FLAGS_NONE, OPCODE_NONE, 0, 11, ( REG_NONE ), ( REG_NONE ) },
	{ "NULL", FLAGS_NONE, OPCODE_NONE, 0, 11, ( REG_NONE ), ( REG_NONE ) },
	{ "NULL", FLAGS_NONE, OPCODE_NONE, 0, 11, ( REG_NONE ), ( REG_NONE ) },
	{ "NULL", FLAGS_NONE, OPCODE_NONE, 0, 11, ( REG_NONE ), ( REG_NONE ) },
	{ "NULL", FLAGS_NONE, OPCODE_NONE, 0, 11, ( REG_NONE ), ( REG_NONE ) },
	{ "NULL", FLAGS_NONE, OPCODE_NONE, 0, 11, ( REG_NONE ), ( REG_NONE ) },
	{ "NULL", FLAGS_NONE, OPCODE_NONE, 0, 11, ( REG_NONE ), ( REG_NONE ) },
	{ "NULL", FLAGS_NONE, OPCODE_NONE, 0, 11, ( REG_NONE ), ( REG_NONE ) },
	{ "NULL", FLAGS_NONE, OPCODE_NONE, 0, 11, ( REG_NONE ), ( REG_NONE ) },
	{ "NULL", FLAGS_NONE, OPCODE_NONE, 0, 11, ( REG_NONE ), ( REG_NONE ) },
	{ "NULL", FLAGS_NONE, OPCODE_NONE, 0, 11, ( REG_NONE ), ( REG_NONE ) },
	{ "NULL", FLAGS_NONE, OPCODE_NONE, 0, 11, ( REG_NONE ), ( REG_NONE ) },
	{ "NULL", FLAGS_NONE, OPCODE_NONE, 0, 11, ( REG_NONE ), ( REG_NONE ) },
	{ "NULL", FLAGS_NONE, OPCODE_NONE, 0, 11, ( REG_NONE ), ( REG_NONE ) },
	{ "NULL", FLAGS_NONE, OPCODE_NONE, 0, 11, ( REG_NONE ), ( REG_NONE ) },
	{ "NULL", FLAGS_NONE, OPCODE_NONE, 0, 11, ( REG_NONE ), ( REG_NONE ) },
	{ "NULL", FLAGS_NONE, OPCODE_NONE, 0, 11, ( REG_NONE ), ( REG_NONE ) },
	{ "NULL", FLAGS_NONE, OPCODE_NONE, 0, 11, ( REG_NONE ), ( REG_NONE ) },
	{ "NULL", FLAGS_NONE, OPCODE_NONE, 0, 11, ( REG_NONE ), ( REG_NONE ) },
	{ "NULL", FLAGS_NONE, OPCODE_NONE, 0, 11, ( REG_NONE ), ( REG_NONE ) },
	{ "NULL", FLAGS_NONE, OPCODE_NONE, 0, 11, ( REG_NONE ), ( REG_NONE ) },
	{ "NULL", FLAGS_NONE, OPCODE_NONE, 0, 11, ( REG_NONE ), ( REG_NONE ) },
	{ "NULL", FLAGS_NONE, OPCODE_NONE, 0, 11, ( REG_NONE ), ( REG_NONE ) },
	{ "NULL", FLAGS_NONE, OPCODE_NONE, 0, 11, ( REG_NONE ), ( REG_NONE ) },
	{ "NULL", FLAGS_NONE, OPCODE_NONE, 0, 11, ( REG_NONE ), ( REG_NONE ) },
	{ "NULL", FLAGS_NONE, OPCODE_NONE, 0, 11, ( REG_NONE ), ( REG_NONE ) },
	{ "NULL", FLAGS_NONE, OPCODE_NONE, 0, 11, ( REG_NONE ), ( REG_NONE ) },
	{ "NULL", FLAGS_NONE, OPCODE_NONE, 0, 11, ( REG_NONE ), ( REG_NONE ) },
	{ "INSN_76_HLT", FLAGS_NONE, OPCODE_HLT, 1, 11, ( REG_NONE ), ( REG_NONE ) },
	{ "NULL", FLAGS_NONE, OPCODE_NONE, 0, 11, ( REG_NONE ), ( REG_NONE ) },
	{ "INSN_78_LOAD_A_B", FLAGS_NONE, OPCODE_REGCOPY8, 1, 11, ( REG_A ), ( REG_B ) },
	{ "INSN_79_LOAD_A_C", FLAGS_NONE, OPCODE_REGCOPY8, 1, 11, ( REG_A ), ( REG_C ) },
	{ "NULL", FLAGS_NONE, OPCODE_NONE, 0, 11, ( REG_NONE ), ( REG_NONE ) },
	{ "NULL", FLAGS_NONE, OPCODE_NONE, 0, 11, ( REG_NONE ), ( REG_NONE ) },
	{ "INSN_7C_LOAD_A_H", FLAGS_NONE, OPCODE_REGCOPY8, 1, 11, ( REG_A ), ( REG_H ) },
	{ "INSN_7D_LOAD_A_L", FLAGS_NONE, OPCODE_REGCOPY8, 1, 11, ( REG_A ), ( REG_L ) },
	{ "NULL", FLAGS_NONE, OPCODE_NONE, 0, 11, ( REG_NONE ), ( REG_NONE ) },
	{ "NULL", FLAGS_NONE, OPCODE_NONE, 0, 11, ( REG_NONE ), ( REG_NONE ) },
	{ "NULL", FLAGS_NONE, OPCODE_NONE, 0, 11, ( REG_NONE ), ( REG_NONE ) },
	{ "NULL", FLAGS_NONE, OPCODE_NONE, 0, 11, ( REG_NONE ), ( REG_NONE ) },
	{ "NULL", FLAGS_NONE, OPCODE_NONE, 0, 11, ( REG_NONE ), ( REG_NONE ) },
	{ "NULL", FLAGS_NONE, OPCODE_NONE, 0, 11, ( REG_NONE ), ( REG_NONE ) },
	{ "NULL", FLAGS_NONE, OPCODE_NONE, 0, 11, ( REG_NONE ), ( REG_NONE ) },
	{ "NULL", FLAGS_NONE, OPCODE_NONE, 0, 11, ( REG_NONE ), ( REG_NONE ) },
	{ "NULL", FLAGS_NONE, OPCODE_NONE, 0, 11, ( REG_NONE ), ( REG_NONE ) },
	{ "NULL", FLAGS_NONE, OPCODE_NONE, 0, 11, ( REG_NONE ), ( REG_NONE ) },
	{ "NULL", FLAGS_NONE, OPCODE_NONE, 0, 11, ( REG_NONE ), ( REG_NONE ) },
	{ "NULL", FLAGS_NONE, OPCODE_NONE, 0, 11, ( REG_NONE ), ( REG_NONE ) },
	{ "NULL", FLAGS_NONE, OPCODE_NONE, 0, 11, ( REG_NONE ), ( REG_NONE ) },
	{ "NULL", FLAGS_NONE, OPCODE_NONE, 0, 11, ( REG_NONE ), ( REG_NONE ) },
	{ "NULL", FLAGS_NONE, OPCODE_NONE, 0, 11, ( REG_NONE ), ( REG_NONE ) },
	{ "NULL", FLAGS_NONE, OPCODE_NONE, 0, 11, ( REG_NONE ), ( REG_NONE ) },
	{ "NULL", FLAGS_NONE, OPCODE_NONE, 0, 11, ( REG_NONE ), ( REG_NONE ) },
	{ "NULL", FLAGS_NONE, OPCODE_NONE, 0, 11, ( REG_NONE ), ( REG_NONE ) },
	{ "NULL", FLAGS_NONE, OPCODE_NONE, 0, 11, ( REG_NONE ), ( REG_NONE ) },
	{ "NULL", FLAGS_NONE, OPCODE_NONE, 0, 11, ( REG_NONE ), ( REG_NONE ) },
	{ "NULL", FLAGS_NONE, OPCODE_NONE, 0, 11, ( REG_NONE ), ( REG_NONE ) },
	{ "NULL", FLAGS_NONE, OPCODE_NONE, 0, 11, ( REG_NONE ), ( REG_NONE ) },
	{ "NULL", FLAGS_NONE, OPCODE_NONE, 0, 11, ( REG_NONE ), ( REG_NONE ) },
	{ "NULL", FLAGS_NONE, OPCODE_NONE, 0, 11, ( REG_NONE ), ( REG_NONE ) },
	{ "NULL", FLAGS_NONE, OPCODE_NONE, 0, 11, ( REG_NONE ), ( REG_NONE ) },
	{ "NULL", FLAGS_NONE, OPCODE_NONE, 0, 11, ( REG_NONE ), ( REG_NONE ) },
	{ "NULL", FLAGS_NONE, OPCODE_NONE, 0, 11, ( REG_NONE ), ( REG_NONE ) },
	{ "NULL", FLAGS_NONE, OPCODE_NONE, 0, 11, ( REG_NONE ), ( REG_NONE ) },
	{ "NULL", FLAGS_NONE, OPCODE_NONE, 0, 11, ( REG_NONE ), ( REG_NONE ) },
	{ "NULL", FLAGS_NONE, OPCODE_NONE, 0, 11, ( REG_NONE ), ( REG_NONE ) },
	{ "NULL", FLAGS_NONE, OPCODE_NONE, 0, 11, ( REG_NONE ), ( REG_NONE ) },
	{ "NULL", FLAGS_NONE, OPCODE_NONE, 0, 11, ( REG_NONE ), ( REG_NONE ) },
	{ "NULL", FLAGS_NONE, OPCODE_NONE, 0, 11, ( REG_NONE ), ( REG_NONE ) },
	{ "NULL", FLAGS_NONE, OPCODE_NONE, 0, 11, ( REG_NONE ), ( REG_NONE ) },
	{ "NULL", FLAGS_NONE, OPCODE_NONE, 0, 11, ( REG_NONE ), ( REG_NONE ) },
	{ "NULL", FLAGS_NONE, OPCODE_NONE, 0, 11, ( REG_NONE ), ( REG_NONE ) },
	{ "NULL", FLAGS_NONE, OPCODE_NONE, 0, 11, ( REG_NONE ), ( REG_NONE ) },
	{ "NULL", FLAGS_NONE, OPCODE_NONE, 0, 11, ( REG_NONE ), ( REG_NONE ) },
	{ "NULL", FLAGS_NONE, OPCODE_NONE, 0, 11, ( REG_NONE ), ( REG_NONE ) },
	{ "NULL", FLAGS_NONE, OPCODE_NONE, 0, 11, ( REG_NONE ), ( REG_NONE ) },
	{ "NULL", FLAGS_NONE, OPCODE_NONE, 0, 11, ( REG_NONE ), ( REG_NONE ) },
	{ "NULL", FLAGS_NONE, OPCODE_NONE, 0, 11, ( REG_NONE ), ( REG_NONE ) },
	{ "NULL", FLAGS_NONE, OPCODE_NONE, 0, 11, ( REG_NONE ), ( REG_NONE ) },
	{ "NULL", FLAGS_NONE, OPCODE_NONE, 0, 11, ( REG_NONE ), ( REG_NONE ) },
	{ "NULL", FLAGS_NONE, OPCODE_NONE, 0, 11, ( REG_NONE ), ( REG_NONE ) },
	{ "NULL", FLAGS_NONE, OPCODE_NONE, 0, 11, ( REG_NONE ), ( REG_NONE ) },
	{ "NULL", FLAGS_NONE, OPCODE_NONE, 0, 11, ( REG_NONE ), ( REG_NONE ) },
	{ "NULL", FLAGS_NONE, OPCODE_NONE, 0, 11, ( REG_NONE ), ( REG_NONE ) },
	{ "NULL", FLAGS_NONE, OPCODE_NONE, 0, 11, ( REG_NONE ), ( REG_NONE ) },
	{ "NULL", FLAGS_NONE, OPCODE_NONE, 0, 11, ( REG_NONE ), ( REG_NONE ) },
	{ "NULL", FLAGS_NONE, OPCODE_NONE, 0, 11, ( REG_NONE ), ( REG_NONE ) },
	{ "NULL", FLAGS_NONE, OPCODE_NONE, 0, 11, ( REG_NONE ), ( REG_NONE ) },
	{ "NULL", FLAGS_NONE, OPCODE_NONE, 0, 11, ( REG_NONE ), ( REG_NONE ) },
	{ "NULL", FLAGS_NONE, OPCODE_NONE, 0, 11, ( REG_NONE ), ( REG_NONE ) },
	{ "NULL", FLAGS_NONE, OPCODE_NONE, 0, 11, ( REG_NONE ), ( REG_NONE ) },
	{ "NULL", FLAGS_NONE, OPCODE_NONE, 0, 11, ( REG_NONE ), ( REG_NONE ) },
	{ "NULL", FLAGS_NONE, OPCODE_NONE, 0, 11, ( REG_NONE ), ( REG_NONE ) },
	{ "NULL", FLAGS_NONE, OPCODE_NONE, 0, 11, ( REG_NONE ), ( REG_NONE ) },
	{ "NULL", FLAGS_NONE, OPCODE_NONE, 0, 11, ( REG_NONE ), ( REG_NONE ) },
	{ "NULL", FLAGS_NONE, OPCODE_NONE, 0, 11, ( REG_NONE ), ( REG_NONE ) },
	{ "NULL", FLAGS_NONE, OPCODE_NONE, 0, 11, ( REG_NONE ), ( REG_NONE ) },
	{ "NULL", FLAGS_NONE, OPCODE_NONE, 0, 11, ( REG_NONE ), ( REG_NONE ) },
	{ "NULL", FLAGS_NONE, OPCODE_NONE, 0, 11, ( REG_NONE ), ( REG_NONE ) },
	{ "NULL", FLAGS_NONE, OPCODE_NONE, 0, 11, ( REG_NONE ), ( REG_NONE ) },
	{ "NULL", FLAGS_NONE, OPCODE_NONE, 0, 11, ( REG_NONE ), ( REG_NONE ) },
	{ "NULL", FLAGS_NONE, OPCODE_NONE, 0, 11, ( REG_NONE ), ( REG_NONE ) },
	{ "NULL", FLAGS_NONE, OPCODE_NONE, 0, 11, ( REG_NONE ), ( REG_NONE ) },
	{ "NULL", FLAGS_NONE, OPCODE_NONE, 0, 11, ( REG_NONE ), ( REG_NONE ) },
	{ "NULL", FLAGS_NONE, OPCODE_NONE, 0, 11, ( REG_NONE ), ( REG_NONE ) },
	{ "INSN_C3_JMP", FLAGS_NONE, OPCODE_JMP, 3, 11, ( REG_NONE ), ( REG_NONE ) },
	{ "NULL", FLAGS_NONE, OPCODE_NONE, 0, 11, ( REG_NONE ), ( REG_NONE ) },
	{ "NULL", FLAGS_NONE, OPCODE_NONE, 0, 11, ( REG_NONE ), ( REG_NONE ) },
	{ "NULL", FLAGS_NONE, OPCODE_NONE, 0, 11, ( REG_NONE ), ( REG_NONE ) },
	{ "NULL", FLAGS_NONE, OPCODE_NONE, 0, 11, ( REG_NONE ), ( REG_NONE ) },
	{ "NULL", FLAGS_NONE, OPCODE_NONE, 0, 11, ( REG_NONE ), ( REG_NONE ) },
	{ "INSN_C9_RET", FLAGS_NONE, OPCODE_RET, 1, 11, ( REG_NONE ), ( REG_NONE ) },
	{ "NULL", FLAGS_NONE, OPCODE_NONE, 0, 11, ( REG_NONE ), ( REG_NONE ) },
	{ "NULL", FLAGS_NONE, OPCODE_NONE, 0, 11, ( REG_NONE ), ( REG_NONE ) },
	{ "NULL", FLAGS_NONE, OPCODE_NONE, 0, 11, ( REG_NONE ), ( REG_NONE ) },
	{ "NULL", FLAGS_NONE, OPCODE_NONE, 0, 11, ( REG_NONE ), ( REG_NONE ) },
	{ "NULL", FLAGS_NONE, OPCODE_NONE, 0, 11, ( REG_NONE ), ( REG_NONE ) },
	{ "NULL", FLAGS_NONE, OPCODE_NONE, 0, 11, ( REG_NONE ), ( REG_NONE ) },
	{ "NULL", FLAGS_NONE, OPCODE_NONE, 0, 11, ( REG_NONE ), ( REG_NONE ) },
	{ "NULL", FLAGS_NONE, OPCODE_NONE, 0, 11, ( REG_NONE ), ( REG_NONE ) },
	{ "NULL", FLAGS_NONE, OPCODE_NONE, 0, 11, ( REG_NONE ), ( REG_NONE ) },
	{ "INSN_D3_OUT_A", FLAGS_NONE, OPCODE_OUT, 2, 11, ( REG_A ), ( REG_NONE ) },
	{ "NULL", FLAGS_NONE, OPCODE_NONE, 0, 11, ( REG_NONE ), ( REG_NONE ) },
	{ "NULL", FLAGS_NONE, OPCODE_NONE, 0, 11, ( REG_NONE ), ( REG_NONE ) },
	{ "NULL", FLAGS_NONE, OPCODE_NONE, 0, 11, ( REG_NONE ), ( REG_NONE ) },
	{ "NULL", FLAGS_NONE, OPCODE_NONE, 0, 11, ( REG_NONE ), ( REG_NONE ) },
	{ "NULL", FLAGS_NONE, OPCODE_NONE, 0, 11, ( REG_NONE ), ( REG_NONE ) },
	{ "NULL", FLAGS_NONE, OPCODE_NONE, 0, 11, ( REG_NONE ), ( REG_NONE ) },
	{ "NULL", FLAGS_NONE, OPCODE_NONE, 0, 11, ( REG_NONE ), ( REG_NONE ) },
	{ "NULL", FLAGS_NONE, OPCODE_NONE, 0, 11, ( REG_NONE ), ( REG_NONE ) },
	{ "NULL", FLAGS_NONE, OPCODE_NONE, 0, 11, ( REG_NONE ), ( REG_NONE ) },
	{ "NULL", FLAGS_NONE, OPCODE_NONE, 0, 11, ( REG_NONE ), ( REG_NONE ) },
	{ "NULL", FLAGS_NONE, OPCODE_NONE, 0, 11, ( REG_NONE ), ( REG_NONE ) },
	{ "NULL", FLAGS_NONE, OPCODE_NONE, 0, 11, ( REG_NONE ), ( REG_NONE ) },
	{ "NULL", FLAGS_NONE, OPCODE_NONE, 0, 11, ( REG_NONE ), ( REG_NONE ) },
	{ "NULL", FLAGS_NONE, OPCODE_NONE, 0, 11, ( REG_NONE ), ( REG_NONE ) },
	{ "NULL", FLAGS_NONE, OPCODE_NONE, 0, 11, ( REG_NONE ), ( REG_NONE ) },
	{ "NULL", FLAGS_NONE, OPCODE_NONE, 0, 11, ( REG_NONE ), ( REG_NONE ) },
	{ "NULL", FLAGS_NONE, OPCODE_NONE, 0, 11, ( REG_NONE ), ( REG_NONE ) },
	{ "NULL", FLAGS_NONE, OPCODE_NONE, 0, 11, ( REG_NONE ), ( REG_NONE ) },
	{ "NULL", FLAGS_NONE, OPCODE_NONE, 0, 11, ( REG_NONE ), ( REG_NONE ) },
	{ "NULL", FLAGS_NONE, OPCODE_NONE, 0, 11, ( REG_NONE ), ( REG_NONE ) },
	{ "NULL", FLAGS_NONE, OPCODE_NONE, 0, 11, ( REG_NONE ), ( REG_NONE ) },
	{ "NULL", FLAGS_NONE, OPCODE_NONE, 0, 11, ( REG_NONE ), ( REG_NONE ) },
	{ "NULL", FLAGS_NONE, OPCODE_NONE, 0, 11, ( REG_NONE ), ( REG_NONE ) },
	{ "NULL", FLAGS_NONE, OPCODE_NONE, 0, 11, ( REG_NONE ), ( REG_NONE ) },
	{ "NULL", FLAGS_NONE, OPCODE_NONE, 0, 11, ( REG_NONE ), ( REG_NONE ) },
	{ "NULL", FLAGS_NONE, OPCODE_NONE, 0, 11, ( REG_NONE ), ( REG_NONE ) },
	{ "NULL", FLAGS_NONE, OPCODE_NONE, 0, 11, ( REG_NONE ), ( REG_NONE ) },
	{ "NULL", FLAGS_NONE, OPCODE_NONE, 0, 11, ( REG_NONE ), ( REG_NONE ) },
	{ "NULL", FLAGS_NONE, OPCODE_NONE, 0, 11, ( REG_NONE ), ( REG_NONE ) },
	{ "NULL", FLAGS_NONE, OPCODE_NONE, 0, 11, ( REG_NONE ), ( REG_NONE ) },
	{ "NULL", FLAGS_NONE, OPCODE_NONE, 0, 11, ( REG_NONE ), ( REG_NONE ) },
	{ "NULL", FLAGS_NONE, OPCODE_NONE, 0, 11, ( REG_NONE ), ( REG_NONE ) },
	{ "NULL", FLAGS_NONE, OPCODE_NONE, 0, 11, ( REG_NONE ), ( REG_NONE ) },
	{ "NULL", FLAGS_NONE, OPCODE_NONE, 0, 11, ( REG_NONE ), ( REG_NONE ) },
	{ "NULL", FLAGS_NONE, OPCODE_NONE, 0, 11, ( REG_NONE ), ( REG_NONE ) },
	{ "NULL", FLAGS_NONE, OPCODE_NONE, 0, 11, ( REG_NONE ), ( REG_NONE ) },
	{ "NULL", FLAGS_NONE, OPCODE_NONE, 0, 11, ( REG_NONE ), ( REG_NONE ) },
	{ "NULL", FLAGS_NONE, OPCODE_NONE, 0, 11, ( REG_NONE ), ( REG_NONE ) },
	{ "NULL", FLAGS_NONE, OPCODE_NONE, 0, 11, ( REG_NONE ), ( REG_NONE ) },
	{ "NULL", FLAGS_NONE, OPCODE_NONE, 0, 11, ( REG_NONE ), ( REG_NONE ) },
	{ "NULL", FLAGS_NONE, OPCODE_NONE, 0, 11, ( REG_NONE ), ( REG_NONE ) },
	{ "NULL", FLAGS_NONE, OPCODE_NONE, 0, 11, ( REG_NONE ), ( REG_NONE ) },
};
