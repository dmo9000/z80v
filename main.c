#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <stdbool.h>
#include <assert.h>
#include "z80.h"

#define ENTRY_ADDRESS   0x0000
#define BANK_SIZE       16384
#define MAX_BANKS       16
#define DIRECT_BANKS    4               /* only 64kb is directly addressable */
#define MAIN_MEMORY     (DIRECT_BANKS * BANK_SIZE)

/* FIXME: currently not endian-safe - this will only work correctly on a LSB CPU */

/* Z80 OPCODE REFERENCE CHARTS

   http://clrhome.org/table/
   http://z80-heaven.wikidot.com/opcode-reference-chart */

uint8_t memory_bank[MAX_BANKS][BANK_SIZE];
//uint8_t memory[MAIN_MEMORY];
int memory_bank_map [MAX_BANKS];

uint8_t mem_read8(uint16_t addr)
{
    uint16_t bank_off = addr % BANK_SIZE;
    uint8_t bank_sel = addr / BANK_SIZE;
    uint8_t phys_sel = 0;
    phys_sel = memory_bank_map[bank_sel];
    return memory_bank[phys_sel][bank_off];
}

void mem_write8(uint16_t addr, uint8_t val)
{
    uint16_t bank_off = addr % BANK_SIZE;
    uint8_t bank_sel = addr / BANK_SIZE;
    uint8_t phys_sel = 0;
    phys_sel = memory_bank_map[bank_sel];
    memory_bank[phys_sel][bank_off] = (uint8_t) val;
    return;
}

uint16_t mem_read16(uint16_t addr)
{
    uint16_t bank1_off = addr % BANK_SIZE;
    uint16_t bank2_off = (addr+1) % BANK_SIZE;
    uint8_t bank1_sel = addr / BANK_SIZE;
    uint8_t bank2_sel = (addr+1) / BANK_SIZE;
    uint8_t phys1_sel = 0;
    uint8_t phys2_sel = 0;

    phys1_sel = memory_bank_map[bank1_sel];
    phys2_sel = memory_bank_map[bank2_sel];

    /*
    		printf("\n");
    		printf("addr = %04XH\n", addr);
    		printf("bank1_sel/off = %02X/%02X, bank2_off = %02X/%02X\n", bank1_sel, bank1_off, bank2_sel, bank2_off);
    		printf("%02x==%02X\n", bank1_off, (uint8_t) memory_bank[phys1_sel][bank1_off]);
    		printf("%02x==%02X\n", bank2_off, (uint8_t) memory_bank[phys2_sel][bank2_off]);
    */

    return memory_bank[phys1_sel][bank1_off] | ( memory_bank[phys2_sel][bank2_off] << 8);
}

void mem_write16(uint16_t addr, uint16_t val)
{
    if ((addr % 0x4000) == 0x3FFF) {
        /* handle 16-bit read accross bank boundary */
        assert(NULL);
    }
    /* not yet implemented */
    assert(NULL);
    return;
}

bool mem_switch_bank(int b1, int b2)
{
    assert(b1 < DIRECT_BANKS);
    assert(b2 < MAX_BANKS);
    memory_bank_map[b1] = b2;
    return true;
}

bool test_bank_switching()
{

    int i = 0;

    for (i = 0; i < MAX_BANKS; i++) {
        memset(&memory_bank[i], (i % 16), BANK_SIZE);
    }

    for (i = 0; i < DIRECT_BANKS; i++) {
        /* setup initial bank mappings, 1:1 */
        memory_bank_map[i] = i;
    }

    mem_switch_bank(0, 0);
    mem_switch_bank(1, 1);
    mem_switch_bank(2, 2);
    mem_switch_bank(3, 3);

    assert(mem_read8(0x0000) == 0x00);
    assert(mem_read8(0x4000) == 0x01);
    assert(mem_read8(0x8000) == 0x02);
    assert(mem_read8(0xC000) == 0x03);

    mem_switch_bank(0, 4);
    mem_switch_bank(1, 5);
    mem_switch_bank(2, 6);
    mem_switch_bank(3, 7);

    assert(mem_read8(0x0000) == 0x04);
    assert(mem_read8(0x4000) == 0x05);
    assert(mem_read8(0x8000) == 0x06);
    assert(mem_read8(0xC000) == 0x07);

    mem_switch_bank(0, 8);
    mem_switch_bank(1, 9);
    mem_switch_bank(2, 10);
    mem_switch_bank(3, 11);

    assert(mem_read8(0x0000) == 0x08);
    assert(mem_read8(0x4000) == 0x09);
    assert(mem_read8(0x8000) == 0x0A);
    assert(mem_read8(0xC000) == 0x0B);

    mem_switch_bank(0, 12);
    mem_switch_bank(1, 13);
    mem_switch_bank(2, 14);
    mem_switch_bank(3, 15);

    assert(mem_read8(0x0000) == 0x0C);
    assert(mem_read8(0x4000) == 0x0D);
    assert(mem_read8(0x8000) == 0x0E);
    assert(mem_read8(0xC000) == 0x0F);

    mem_switch_bank(0, 0);
    mem_switch_bank(1, 1);
    mem_switch_bank(2, 2);
    mem_switch_bank(3, 3);

    assert(mem_read16(0x0000) == 0x0000);
    assert(mem_read16(0x4000) == 0x0101);
    assert(mem_read16(0x8000) == 0x0202);
    assert(mem_read16(0xC000) == 0x0303);

    /* split bank tests */

    assert(mem_read16(0x3FFF) == 0x0100);
    assert(mem_read16(0x7FFF) == 0x0201);
    assert(mem_read16(0xBFFF) == 0x0302);
    assert(mem_read16(0xFFFF) == 0x0003);

    /* clear all memory banks */

    for (i = 0; i < MAX_BANKS; i++) {
        memset(&memory_bank[i], 0, BANK_SIZE);
    }

    for (i = 0; i < DIRECT_BANKS; i++) {
        /* setup initial bank mappings, 1:1 */
        memory_bank_map[i] = i;
    }

    return true;
}


int bootloader_hack()
{

    uint16_t i = 0;
    char bootmem[256];
    FILE *bootdisk = NULL;

    bootdisk = fopen("disks/Drive0.disk", "rb");
    assert(bootdisk);
    assert(fread(&bootmem, 256, 1, bootdisk));
    for (i = 0; i < 256; i++) {
        mem_write8(i, bootmem[i]);
    }
    fclose(bootdisk);
    return 0;
}

int main(int argc, char *argv[])
{

    int i = 0;


    //printf("Initializing memory (%u banks of %u bytes)\n", MAX_BANKS, BANK_SIZE);

    if (!test_bank_switching()) {
        printf("SELF_TEST: bank switching test failed\n");
    }

    bootloader_hack();
    z80_execute(ENTRY_ADDRESS);

    exit(0);
}

