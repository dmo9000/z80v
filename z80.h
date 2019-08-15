#ifndef __Z80_H__
#define __Z80_H__

#include <stdint.h>

#define INSN_00_NOP   0x00
#define INSN_76_HLT   0x76
#define INSN_C9_RET   0xC9

#define OPCODE_NONE				0x00
#define OPCODE_NOP				0x01
#define OPCODE_JMP				0x02
#define OPCODE_CALL				0x03
#define OPCODE_RET				0x04
#define OPCODE_INC				0x05
#define OPCODE_HLT				0x06
#define	OPCODE_LOAD8			0x07
#define	OPCODE_LOAD16			0x08
#define OPCODE_XOR				0x09
#define	OPCODE_IN					0x20
#define	OPCODE_OUT				0x21
#define OPCODE_REGCOPY8		0x22
#define OPCODE_REGCOPY16	0x23

#define FLAGS_NONE			0x0
#define	FLAG_SF					128
#define	FLAG_ZF					64	
#define	FLAG_YF					32
#define	FLAG_HF					16
#define	FLAG_XF					8
#define	FLAG_PF					4	
#define	FLAG_NF					2	
#define	FLAG_CF					1


#define REG_NONE				0
#define REG_A						1	
#define REG_B						2	
#define REG_C						3	
#define REG_D						4
#define REG_E						5
#define REG_F						6
#define REG_H						7	
#define REG_L						8
#define REG_PC					10	
#define REG_AF					11	
#define REG_BC					12	
#define REG_DE					13
#define REG_HL					14
#define REG_IX					15
#define REG_IY					16


struct _opcode {
							char *description;
							uint8_t flags;	
							uint8_t type;	
							uint8_t length;
							uint8_t cycles;
							uint8_t regidx1;
							uint8_t regidx2;
							};

typedef struct _opcode opcode;

struct _z80 {
						uint64_t insns;
						uint64_t cycles;
						uint8_t flags;
            uint16_t pc;
						uint8_t  a;
						uint8_t  b;
						uint8_t  c;
						uint8_t	 d;
						uint8_t  e;
						uint8_t	 h;
						uint8_t	 l;
						uint8_t  _a;
						uint8_t  _b;
						uint8_t  _c;
						uint8_t	 _d;
						uint8_t  _e;
						uint8_t	 _h;
						uint8_t	 _l;
						uint16_t	ix;
						uint16_t	iy;
            }; 

typedef struct _z80 Z80;


uint8_t mem_read8(uint16_t addr);
void mem_write8(uint16_t addr, uint8_t val);
uint16_t mem_read16(uint16_t addr);
void mem_write16(uint16_t addr, uint16_t val);
opcode *z80_decode();
int z80_execute(uint16_t address);
char *z80_regname(uint8_t regidx);

#endif /* __Z80_H__ */
