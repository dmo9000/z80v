#include <stdio.h>
#include <assert.h>
#include "z80opmap.h"

char *regnames[19] = {
                        "NONE", "A", "B", "C", "D", "E", "F", "H", "L", "(unassigned)",   
                        "PC", "AF", "BC", "DE", "HL", "IX", "IY",
												NULL
                    };

Z80 CPU;

opcode *z80_decode(Z80 *CPU)
{
	opcode *oc_ptr = NULL;
  uint8_t insn = 0;
  insn = mem_read8(CPU->pc);
	oc_ptr = &z80opmap[insn];
	assert(oc_ptr);
	printf("-> %s (len=%u, type=%u)\n", oc_ptr->description, oc_ptr->length, oc_ptr->type);
  printf("   0x%04x: %02X ", CPU->pc, insn);
	return oc_ptr;
}

void z80_load8(Z80 *CPU, opcode *oc_ptr, uint8_t value8)
{
  assert(oc_ptr);
  //printf("z80_load8(..., register=%u, value=0x%02x)\n", oc_ptr->regidx1, value8);

  switch(oc_ptr->regidx1) {
				case REG_A:
					CPU->a = value8;
          //printf("CPU->a=0x%02x\n", CPU->a);
					break;
        case REG_D:
          CPU->d = value8;
          //printf("CPU->d=0x%02x\n", CPU->d);
          break;
        default:
          printf("z80_load8: unknown regidx1=%u\n", oc_ptr->regidx1);
          assert(NULL);
          break;
        }

  return;
}


void z80_load16(Z80 *CPU, opcode *oc_ptr, uint16_t value16)
{
	assert(oc_ptr);
	//printf("z80_load16(..., register=%u, value=0x%04x)\n", oc_ptr->regidx1, value16);	
	
	switch(oc_ptr->regidx1) {
				case REG_BC:
					CPU->b = value16 & 0x00FF;
					CPU->c = (value16 & 0xFF00) >> 8;
					//printf("CPU->b=0x%02x\n", CPU->b);
					//printf("CPU->c=0x%02x\n", CPU->c);
					break;
				case REG_HL:
					CPU->h = value16 & 0x00FF;
					CPU->l = (value16 & 0xFF00) >> 8;
					//printf("CPU->h=0x%02x\n", CPU->h);
					//printf("CPU->l=0x%02x\n", CPU->l);
					break;
				default:
					printf("z80_load16: unknown regidx1=%u\n", oc_ptr->regidx1);
					assert(NULL);
					break;
				}

	return;
}

int z80_dumpregs(Z80 *CPU)
{
	printf("\nz80_dumpregs():\n   ");
	printf("AF=0x%04X ", CPU->a | CPU->f << 8);
	printf("BC=0x%04X ", CPU->b | CPU->c << 8);
	printf("DE=0x%04X ", CPU->d | CPU->e << 8);
	printf("HL=0x%04X ", CPU->h | CPU->l << 8);
	printf("PC=0x%04X\n", CPU->pc);
	return(0);
}

int z80_out(Z80 *CPU, opcode *oc_ptr, uint8_t port)
{

	switch(oc_ptr->regidx1) {
				case REG_A:
					printf("\n** Z80_OUT(0x%04X, 0x%02X)\n\n", (uint16_t) port, CPU->a); 
					break;
				default:
					printf("z80_out: bad regidx1=%u\n", oc_ptr->regidx1);
					z80_dumpregs(CPU);
					assert(NULL);
					break;
				}
	
	return 0;

}

int z80_regcopy(Z80 *CPU, opcode *oc_ptr)
{
	assert(CPU);
	assert(oc_ptr);
//	printf("z80_regcopy()\n");
	switch (oc_ptr->regidx1) {
				case REG_A:
					switch(oc_ptr->regidx2) {
						case REG_B:
							CPU->a = CPU->b;
							break;
						case REG_C:
							CPU->a = CPU->c;
							break;
						case REG_H:
							CPU->a = CPU->h;
							break;
						case REG_L:
							CPU->a = CPU->l;
							break;
						default:
							printf("** unsupported source register (%s)\n", z80_regname(oc_ptr->regidx2));
							assert(NULL);
							break;
						}
					break;
				default:
					printf("** unsupported destination register (%s)\n", z80_regname(oc_ptr->regidx1));
					assert(NULL);
					break;
				}
	return 0;
}

int z80_execute(uint16_t address)
{
	uint16_t p16_1 = 0;
	uint8_t p8_1 = 0;
	opcode *oc_ptr = NULL;
  CPU.pc = address;
	uint8_t advance = 0;
	uint16_t cycles = 0;

  while (1) {
						oc_ptr = z80_decode(&CPU);
						advance = 0;
            switch (oc_ptr->type) {
								case OPCODE_REGCOPY8:
									assert(oc_ptr->length == 1);
									printf("| LD %s <- %s \n", z80_regname(oc_ptr->regidx1), z80_regname(oc_ptr->regidx2));
									z80_regcopy(&CPU, oc_ptr);
									advance = oc_ptr->length;
									break;
								case OPCODE_OUT:
									assert(oc_ptr->length == 2);
									p8_1 = mem_read8(CPU.pc+1);	
									printf("%02X   ", p8_1);
									printf("| OUT 0x00%02X <- <%s> \n", p8_1, z80_regname(oc_ptr->regidx1));
									z80_out(&CPU, oc_ptr, p8_1);
									advance = oc_ptr->length;
									break;
								case OPCODE_JMP:
									assert(oc_ptr->length == 3);
									p16_1 = mem_read16(CPU.pc+1);	
									printf("%04X ", p16_1);
									printf("| JMP 0x%04X\n", p16_1);
									CPU.pc = p16_1;
									break;
								case OPCODE_LOAD8:
									assert(oc_ptr->length == 2);
									p8_1 = mem_read8(CPU.pc+1);	
									printf("%02X   ", p8_1);
									printf("| LOAD8 <%s>  <- 0x%02X\n", z80_regname(oc_ptr->regidx1), p8_1);
									z80_load8(&CPU, oc_ptr, p8_1);
									advance = oc_ptr->length;
									break;
								case OPCODE_LOAD16:
									assert(oc_ptr->length == 3);
									p16_1 = mem_read16(CPU.pc+1);	
									printf("%04X ", p16_1);
									printf("| LOAD16 <%s> <- 0x%04x\n", z80_regname(oc_ptr->regidx1), p16_1);
									z80_load16(&CPU, oc_ptr, p16_1);
									advance = oc_ptr->length;
									break;
                case OPCODE_NONE:
                  printf("\n++ OPCODE_NONE encountered, aborting\n");
									z80_dumpregs(&CPU);
                  assert(NULL);
									break;
								default:
									printf("\n++ unhandled opcode (type=%u)\n", oc_ptr->type);
									z80_dumpregs(&CPU);
									assert(NULL);
									break;
                }
            CPU.pc += advance;
						cycles += oc_ptr->cycles;
            }

  return 0;
}

char *z80_regname(uint8_t regidx1)
{
	return regnames[regidx1];
}
