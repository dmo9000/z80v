#include <stdio.h>
#include <assert.h>
#include "sysbus.h"
#include "disk.h"

/* z80emu compatible BIOS */

uint8_t selected_disk = 0;
uint8_t selected_track = 0;
uint8_t selected_sector = 0;
uint16_t dma_addr = 0;

int sysbus_dump()
{
    printf("\n*** SYSTEM BUS PARAMETERS ***\n\n");
    printf("  selected_disk   = %02XH\n", selected_disk);
    printf("  selected_track  = %02XH\n", selected_track);
    printf("  selected_sector = %02XH\n", selected_sector);
    printf("  dma_addr        = %04XH\n", dma_addr);
    printf("\n");
    return 1;
}

int sysbus_init()
{

	/* power on self-test */

    if (!test_bank_switching()) {
        printf("SELF_TEST: bank switching test failed\n");
    }

	/* load the first 512 bytes of the first disk into RAM */

		disk_init();

    bootloader_hack();

		return 0;
}



int sysbus_in(Z80 *CPU, uint16_t port)
{

    printf("\n                   |");
    switch (port) {
    case 0x0E:
        /* acknowledge drive controller */
        CPU->a = 0;
        printf(" DRVACK %03u (%02XH)|", CPU->a, CPU->a);
        return 1;
        break;
    default:
        printf("+++ sysbus_in(%04XH) unhandled\n", port);
        assert(NULL);
        break;
    }
    return 0;

}


int sysbus_out(Z80 *CPU, uint16_t port, uint8_t val)
{

    printf("\n                   |");
    switch (port) {
    case 0x0A:
        printf(" SELDSK %03u (%02XH)|", val, val);
        selected_disk = val;
        return 1;
        break;
    case 0x0B:
        printf(" SETTRK %03u (%02XH)|", val, val);
        selected_track = val;
        return 1;
        break;
    case 0x0C:
        printf(" SETSEC %03u (%02XH)|", val, val);
        selected_sector = val;
        return 1;
        break;
    case 0x0D:
        /* read/write */
        switch (val) {
        case 0:
            printf(" RD_SEC %03u (%02XH)|", val, val);
            /* HIGHPRIORITY TODO: implement */
            return 1;
            break;
        case 1:
            printf(" WR_SEC %03u (%02XH)|", val, val);
            /* TODO: implement */
            return 1;
            break;
        default:
            printf("+++ unsupported disk operation type  (%u)\n", val);
            assert(NULL);
            break;
        }

    case 0x0F:
        printf(" LSBDMA %03u (%02XH)|", val, val);
        dma_addr = (dma_addr & 0xFF00) + val;
        return 1;
        break;
    case 0x10:
        printf(" MSBDMA %03u (%02XH)|", val, val);
        dma_addr = (dma_addr & 0x00FF) + (val * 0x100);
        return 1;
        break;
    default:
        printf("+++ sysbus_out(%04XH, %02xH) unhandled\n", port, val);
        assert(NULL);
        break;
    }

    return 0;

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
