#include <stdio.h>
#include <string.h>
#include <assert.h>
#include "z80opmap.h"
#include "sysbus.h"

//#define PAUSE

char *regnames[19] = {
    "NONE", "A", "B", "C", "D", "E", "F", "H", "L", "SP",
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
//	printf("-> %s (len=%u, type=%u)\n", oc_ptr->description, oc_ptr->length, oc_ptr->type);
    printf("   0x%04X: %02X ", CPU->pc, insn);
    /*
    switch (oc_ptr->length) {
    				default:
    					break;
    				}
    */
    return oc_ptr;
}

void z80_load8(Z80 *CPU, opcode *oc_ptr, uint8_t value8)
{
    assert(oc_ptr);
    //printf("z80_load8(..., register=%u, value=0x%02x)\n", oc_ptr->regidx1, value8);

    switch(oc_ptr->regidx1) {
    case REG_A:
        CPU->a = value8;
        break;
    case REG_C:
        CPU->c = value8;
        break;
    case REG_D:
        CPU->d = value8;
        break;
    default:
        printf("z80_load8: unknown regidx1=%u\n", oc_ptr->regidx1);
        assert(NULL);
        break;
    }

    return;
}

void z80_add16(uint8_t regidx, uint16_t value)
{
    uint16_t t1 = 0;
    switch (regidx) {
    case REG_HL:
        t1 = z80_get_reg16(REG_HL);
        t1 += value;
        /* FLAGS!!? */
        CPU.l = t1 & 0x00FF;
        CPU.h = (t1 & 0xFF00) >> 8;
        return;
        break;
    default:
        printf("z80_add16: unsupported 16-bit destination register\n");
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
        CPU->b = (value16 & 0xFF00) >> 8;
        CPU->c = value16 & 0x00FF;
        break;
    case REG_HL:
        CPU->h = (value16 & 0xFF00) >> 8;
        CPU->l = value16 & 0x00FF;
        break;
    case REG_SP:
        CPU->sp = value16;
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
    char buffer[10];
//	printf("\nz80_dumpregs():\n   ");
    printf(" ");
    printf("INS=%06u ", CPU->insns);
    printf("CSC=%06u ", CPU->cycles);
    printf("PC=%04X: ", CPU->pc);
    printf("SP=%04X: ", CPU->sp);
    printf("A=%02X ", CPU->a);
    printf("B=%02X ", CPU->b);
    printf("C=%02X ", CPU->c);
    printf("D=%02X ", CPU->d);
    printf("E=%02X ", CPU->e);
    printf("H=%02X ", CPU->h);
    printf("L=%02X ", CPU->l);

    printf("FLAGS=");

    for (uint8_t i = 128 ; i >= 1; i = i / 2) {
        if (CPU->flags & i) {
            printf("1");
        } else {
            printf("0");
        }
    }

#ifdef PAUSE
    fread(&buffer, 1, 1, stdin);
#else
    printf("\n");
#endif
    /*
    	printf("AF=0x%04X ", CPU->a | CPU->f << 8);
    	printf("BC=0x%04X ", CPU->b | CPU->c << 8);
    	printf("DE=0x%04X ", CPU->d | CPU->e << 8);
    	printf("HL=0x%04X\n", CPU->h | CPU->l << 8);
    */
    return(0);
}

int z80_out(Z80 *CPU, opcode *oc_ptr, uint8_t port)
{
    switch(oc_ptr->regidx1) {
    case REG_A:
        printf("\n\n** Z80_OUT(0x%04X, 0x%02X): ", (uint16_t) port, CPU->a);
        sysbus_out(CPU, port, CPU->a);
        break;
    default:
        printf("z80_out: bad regidx1=%u\n", oc_ptr->regidx1);
        z80_dumpregs(CPU);
        assert(NULL);
        break;
    }

    return 0;
}

int z80_in(Z80 *CPU, opcode *oc_ptr, uint8_t port)
{
    switch(oc_ptr->regidx1) {
    case REG_A:
        printf("\n\n** Z80_IN (0x%04X, 0x%02X): ", (uint16_t) port, CPU->a);
        sysbus_in(CPU, port);
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

bool z80_getflag(uint8_t flag)
{
    if (CPU.flags & flag) {
        return true;
    }
    return false;
}

void z80_setflag(uint8_t flag, bool state)
{
//	printf("z80_setflag(%u, %s)\n", flag, (state ? "true" : "false"));
    if (state == true) {
        CPU.flags |= flag;
    } else {
        CPU.flags = ~flag;
    }
//	assert(NULL);
    return;
}

uint16_t z80_get_reg16(uint8_t reg)
{

    switch (reg) {
    case REG_BC:
        return CPU.c | (CPU.b << 8);
        break;
    case REG_HL:
        return CPU.l | (CPU.h << 8);
        break;
    case REG_SP:
        return CPU.sp;
        break;
    default:
        printf("z80_get_reg16: unsupported 16 bit register (%s)\n",  z80_regname(reg));
        assert(NULL);
        break;
    }
}

uint16_t z80_set_reg16(uint8_t reg, uint16_t val)
{

    switch (reg) {
    case REG_BC:
        CPU.b = (uint8_t) (val & 0xFF00) >> 8;
        CPU.c = (uint8_t) (val & 0x00FF);
        break;
    default:
        printf("z80_set_reg16: unsupported 16 bit register (%s)\n",  z80_regname(reg));
        assert(NULL);
        break;
    }

}


int z80_execute(uint16_t address)
{
    uint16_t p16_1 = 0;
    uint8_t p8_1 = 0;
    opcode *oc_ptr = NULL;
    CPU.pc = address;
    uint8_t advance = 0;

    /* set all bits in all registers to 1 */
    /* let's set them manually, just in case anyway */
    CPU.a = 0xFF;
    CPU.b = 0xFF;
    CPU.c = 0xFF;
    CPU.d = 0xFF;
    CPU.e = 0xFF;
    CPU.h = 0xFF;
    CPU.l = 0xFF;
    CPU._a = 0xFF;
    CPU._b = 0xFF;
    CPU._c = 0xFF;
    CPU._d = 0xFF;
    CPU._e = 0xFF;
    CPU._h = 0xFF;
    CPU._l = 0xFF;
    CPU.flags = 0xFF; 	/* set all flags on initially */
    CPU._flags = 0xFF; 	/* set all flags on initially */
    /* program counter starts at zero */
    CPU.pc = 0x0000;
    CPU.insns = 0;
    CPU.cycles = 0;

    while (1) {
        oc_ptr = z80_decode(&CPU);
        advance = 0;
        switch (oc_ptr->type) {
        case OPCODE_CP:
            p8_1 = mem_read8(CPU.pc+1);
            printf("     ");
            printf("| CP %02XH          |", p8_1);
            p8_1 = CPU.a - p8_1;
            /* MODIFY FLAGS!! */
            if (p8_1 == 0) {
                z80_setflag(FLAG_ZF, true);
            } else {
                z80_setflag(FLAG_ZF, false);
            }
            advance = oc_ptr->length;
            break;
        case OPCODE_ADD16:
            printf("     ");
            printf("| ADD %s,%s       |", z80_regname(oc_ptr->regidx1), z80_regname(oc_ptr->regidx2));
            switch (oc_ptr->regidx1) {
            case REG_HL:
                z80_add16(oc_ptr->regidx1, z80_get_reg16(oc_ptr->regidx2));
                advance = oc_ptr->length;
                /* TODO: flags */
                break;
            default:
                printf("+++ unsupported ADD16 register (%s)\n",  z80_regname(oc_ptr->regidx1));
                assert(NULL);
                break;
            }
            break;

        case OPCODE_INC8:
            assert(oc_ptr->length == 1);
            printf("     ");
            printf("| INC %s           |", z80_regname(oc_ptr->regidx1));
            switch (oc_ptr->regidx1) {
            case REG_C:
                CPU.c++;
                if (CPU.c == 0) {
                    /* set zero flag */
                    z80_setflag(FLAG_ZF, true);
                    z80_setflag(FLAG_CF, true);
                } else {
                    z80_setflag(FLAG_ZF, false);
                    z80_setflag(FLAG_CF, false);
                }
                /* TODO: flags */
                break;
            default:
                printf("+++ unsupported INC 8-bit register (%s)\n",  z80_regname(oc_ptr->regidx1));
                assert(NULL);
                break;
            }
            advance = oc_ptr->length;
            break;

        case OPCODE_INC16:
            assert(oc_ptr->length == 1);
            printf("     ");
            printf("| INC %s          |", z80_regname(oc_ptr->regidx1));
            switch (oc_ptr->regidx1) {
            case REG_BC:
                z80_set_reg16(REG_BC, z80_get_reg16(REG_BC)+1);
                break;
            default:
                printf("+++ unsupported INC 16-bit register (%s)\n",  z80_regname(oc_ptr->regidx1));
                assert(NULL);
                break;
            }
            advance = oc_ptr->length;
            break;

        case OPCODE_DEC8:
            assert(oc_ptr->length == 1);
            printf("     ");
            printf("| DEC %s           |", z80_regname(oc_ptr->regidx1));
            switch (oc_ptr->regidx1) {
            case REG_D:
                CPU.d--;
                if (CPU.d == 0) {
                    /* set zero flag */
                    z80_setflag(FLAG_ZF, true);
                } else {
                    z80_setflag(FLAG_ZF, false);
                }
                /* TODO: flags */
                break;
            default:
                printf("+++ unsupported DEC register (%s)\n",  z80_regname(oc_ptr->regidx1));
                assert(NULL);
                break;
            }
            advance = oc_ptr->length;
            break;
        case OPCODE_OR:
            assert(oc_ptr->length == 1);
            printf("     ");
            printf("| OR %s            |", z80_regname(oc_ptr->regidx1));
            switch (oc_ptr->regidx1) {
            case REG_A:
                CPU.a = CPU.a | CPU.a;
                /* TODO: flags */
                break;
            default:
                printf("+++ unsupported OR register (%s)\n",  z80_regname(oc_ptr->regidx1));
                assert(NULL);
                break;
            }
            advance = oc_ptr->length;
            break;
        case OPCODE_XOR:
            assert(oc_ptr->length == 1);
            printf("     ");
            printf("| XOR %s           |", z80_regname(oc_ptr->regidx1));
            switch (oc_ptr->regidx1) {
            case REG_A:
                CPU.a = CPU.a ^ CPU.a;
                if (CPU.a == 0) {
                    z80_setflag(FLAG_ZF, true);
                }
                /* TODO: flags */
                break;
            default:
                printf("+++ unsupported XOR register (%s)\n",  z80_regname(oc_ptr->regidx1));
                assert(NULL);
                break;
            }
            advance = oc_ptr->length;
            break;
        case OPCODE_REGCOPY8:
            assert(oc_ptr->length == 1);
            printf("     ");
            printf("| LD %s,%s          |", z80_regname(oc_ptr->regidx1), z80_regname(oc_ptr->regidx2));
            z80_regcopy(&CPU, oc_ptr);
            advance = oc_ptr->length;
            break;
        case OPCODE_IN:
            assert(oc_ptr->length == 2);
            p8_1 = mem_read8(CPU.pc+1);
            printf("%02X   ", p8_1);
            printf("| IN  00%02X,%s      |", p8_1, z80_regname(oc_ptr->regidx1));
            z80_in(&CPU, oc_ptr, p8_1);
            advance = oc_ptr->length;
            break;
        case OPCODE_OUT:
            assert(oc_ptr->length == 2);
            p8_1 = mem_read8(CPU.pc+1);
            printf("%02X   ", p8_1);
            printf("| OUT 00%02X,%s      |", p8_1, z80_regname(oc_ptr->regidx1));
            z80_out(&CPU, oc_ptr, p8_1);
            advance = oc_ptr->length;
            break;
        case OPCODE_JMP:
            assert(oc_ptr->length == 3);
            p16_1 = mem_read16(CPU.pc+1);
            printf("%04X ", p16_1);
            printf("| JP %04XH        |", p16_1);
            CPU.pc = p16_1;
            break;
        case OPCODE_JPC:
            assert(oc_ptr->length == 3);
            p16_1 = mem_read16(CPU.pc+1);
            printf("%04X ", p16_1);
            printf("| JP_C %04XH      |", p16_1);

            //printf("z80_getflag(FLAG_CF) = %s\n", (z80_getflag(FLAG_CF) ? "true" : "false"));
            if (z80_getflag(FLAG_CF)) {
                //printf("Jumping to %04XH\n", p16_1);
                CPU.pc = p16_1;
                advance = 0;
            } else {
                //printf("Not jumping to %04XH\n", p16_1);
                advance = oc_ptr->length;
            }
            break;
        case OPCODE_JPZ:
            assert(oc_ptr->length == 3);
            p16_1 = mem_read16(CPU.pc+1);
            printf("%04X ", p16_1);
            printf("| JP_Z %04XH      |", p16_1);
            //printf("z80_getflag(FLAG_ZF) = %s\n", (z80_getflag(FLAG_ZF) ? "true" : "false"));
            if (z80_getflag(FLAG_ZF)) {
                CPU.pc = p16_1;
                advance = 0;
            } else {
                advance = oc_ptr->length;
            }
            break;
        case OPCODE_LOAD8:
            assert(oc_ptr->length == 2);
            p8_1 = mem_read8(CPU.pc+1);
            printf("%02X   ", p8_1);
            printf("| LD %s,%02XH        |", z80_regname(oc_ptr->regidx1), p8_1);
            z80_load8(&CPU, oc_ptr, p8_1);
            advance = oc_ptr->length;
            break;
        case OPCODE_LOAD16:
            assert(oc_ptr->length == 3);
            p16_1 = mem_read16(CPU.pc+1);
            printf("%04X ", p16_1);
            printf("| LD %s,%04XH     |", z80_regname(oc_ptr->regidx1), p16_1);
            z80_load16(&CPU, oc_ptr, p16_1);
            advance = oc_ptr->length;
            break;
        case OPCODE_NONE:
            printf("\n++ OPCODE_NONE encountered, aborting\n");
            z80_dumpregs(&CPU);
            sysbus_dump();
            fflush(NULL);
            assert(NULL);
            break;
        default:
            printf("\n++ unhandled opcode (type=%u) %s\n", oc_ptr->type, oc_ptr->description);
            z80_dumpregs(&CPU);
            fflush(NULL);
            assert(NULL);
            break;
        }
        CPU.pc += advance;
        CPU.insns++;
        CPU.cycles += oc_ptr->cycles;
        z80_dumpregs(&CPU);
    }

    return 0;
}

char *z80_regname(uint8_t regidx1)
{
    return (regnames[regidx1] ? regnames[regidx1] : "XX");
}
