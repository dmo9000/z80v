#define _GNU_SOURCE
#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>
#include <time.h>
#include <sys/time.h>
#include <signal.h>
#include <pthread.h>
#include "zextest.h"
#include "sysbus.h"
#include "ansitty.h"
#include "ttyinput.h"
#include "network.h"
#include "disk.h"


DiskDrive *Selected_Drive = NULL;
uint8_t current_drive_id = 0;
uint16_t DMA = 0;
uint32_t pos = 0;
uint8_t rc = 0;
volatile uint16_t clockticks = 0;

#define SECTOR_SIZE 128

char *banner = "Z80 REFERENCE PLATFORM V0.1\r\n\r\n";

pthread_t clock_thread;
pthread_t display_thread;
pthread_t idle_thread;
pthread_mutex_t display_mutex;

int debuglevel = 0;
bool hydrogen_enabled = true;


void *sysbus_idle()
{
    time_t current_time = 0, next_time = 0;
    printf("*** IDLE THREAD ***\n");
    while (1) {
        run_emulation();
        current_time = time(NULL);
        next_time = current_time + 1;
        while (current_time != next_time) {
            current_time = time(NULL);
            pthread_yield();
            usleep(1000);
        }
        printf("*** IDLE TICK ***\n");
    }

}

void *sysbus_videoupdate()
{
    printf("*** DISPLAY STARTED ***\n");
    while (1) {
        usleep(20000);
        while (pthread_mutex_trylock(&display_mutex) != 0) {
            pthread_yield();
        }
        if (ansitty_canvas_getdirty()) {
            //printf("** CANVAS IS DIRTY ***\n");
            ansitty_expose();
            ansitty_canvas_setdirty(false);
        }
        pthread_mutex_unlock(&display_mutex);
    }
}

void *sysbus_clockfunction()
{
    printf("*** CLOCK STARTED ***\n");
    while (1) {
        /* 20000 microseconds, or 200 millseconds */
        /* TODO: replace with nanosleep */
        //printf("TICK\n");
        clockticks++;
        usleep(20000);
    }
}

int sysbus_init()
{

    char *ptr = banner;
    printf("System bus initialization ...\n");

    if (!TCP_init()) {
        printf("couldn't initalize TCP\n");
        assert(NULL);
    }

    ansitty_init();
		sleep(1);


    while (ptr[0] != '\0') {
        ansitty_putc(ptr[0]);
        ptr++;
    }

    pthread_create( &clock_thread, NULL, sysbus_clockfunction, NULL);
    pthread_create( &display_thread, NULL, sysbus_videoupdate, NULL);
    //pthread_create( &idle_thread, NULL, sysbus_idle, NULL);

    return 1;


}

int sysbus_disks_init()
{
    return disk_init();
}

int sysbus_bootloader(ZEXTEST *context)
{
    printf("sysbus_bootloader()\n");
    return sysbus_ReadFromDriveToMemory(context, 0, 0, 0, 256);
}


int sysbus_ReadFromDriveToMemory(ZEXTEST *context, int driveid, uint16_t tgt_addr, off_t src_addr, uint16_t bytes)
{
    if (debuglevel) {
        printf("sysbus_ReadFromDriveToMemory(driveid=%d, tgt_addr=0x%04x, src_addr=0x%08x, %u)\n",
               driveid, tgt_addr, (unsigned int) src_addr, bytes);
    }

    disk_readfromdrivetomemory(context, driveid, tgt_addr, src_addr, bytes);

    return 0;

}
int sysbus_WriteFromMemoryToDrive(ZEXTEST *context, int driveid, uint16_t src_addr, off_t tgt_addr, uint16_t bytes)
{
    if (debuglevel) {
        printf("sysbus_ReadFromDriveToMemory(driveid=%d, tgt_addr=0x%04lx, src_addr=0x%08x, %u)\n",
               driveid, tgt_addr, (unsigned int) src_addr, bytes);
    }

    disk_writefrommemorytodrive(context, driveid, src_addr, tgt_addr, bytes);
    return 0;
}


void memory_dump(unsigned char *ptr, uint16_t addr, uint16_t size)
{
    int i = 0;
    int c = 0;

    printf("memory_dump(0x%08lx, 0x%04x, 0x%04x)\n", (unsigned long) ptr, addr, size);

    for (i = 0; i < size; i++) {
        if (!(c % 16)) {
            printf("0x%08x: ", addr);
        }
        printf("%02x ", ptr[i]);
        addr++;
        c++;
        if (!(c % 16)) {
            printf("\n");
        }
    }
    printf("\n");
}




int _Z80_INPUT_BYTE(ZEXTEST *context, uint16_t port, uint8_t x)
{
    uint8_t c = 0;
    uint8_t d = 0;
    //printf("     _Z80_INPUT_BYTE(0x%02X, %02X)\n", port, x);
    //fflush(NULL);

    switch (port) {
    case 0x00:
        tty_processinput();
        c = tty_getbuflen();
        if (!c) {
            context->state.registers.byte[Z80_A] = 0x00;
            return 1;
        }
        /* CONST - console status, return 0x00 if no character is ready, otherwise return 0xFF */
        context->state.registers.byte[Z80_A] = 0xff;
        return 1;
        break;
    case 0x01:
        //    printf("CONIN:\n");
        c = tty_getbuflen();
        while (!c) {
            d = tty_processinput();
            if (!d) {
                usleep(20000);
                pthread_yield();
            } else {
                c = tty_getbuflen();
            }
        }
        d = tty_popkeybuf();
        //printf("Returning [%c]\n", d);
        context->state.registers.byte[Z80_A] = d;
        return 1;
        break;
    case 0x0E:
        /* DISK IO - acknowledge controller */
        Selected_Drive = (DiskDrive *) GetDriveReference(current_drive_id);
        assert(Selected_Drive);
        assert(Selected_Drive->io_in_progress);
        Selected_Drive->io_in_progress = false;
        if (debuglevel) {
            printf("    + RDWR_END: DMA=0x%04X reading/writing drive %u, track %u, sector %u\n", DMA, current_drive_id, Selected_Drive->selected_track, Selected_Drive->selected_sector);
        }
        context->state.registers.byte[Z80_A] = 0;
        return 0;
        break;
    case 0xF0:
        printf("/* HYDROGEN BUS DETECTION! */\n");
        switch (hydrogen_enabled) {
        case true:
            context->state.registers.byte[Z80_A] = 0x21;
            break;
        case false:
            context->state.registers.byte[Z80_A] = 0x00;
            break;
        }
        return 0;
        break;
    case 0xF1:
        context->state.registers.byte[Z80_A] = 0; /* SUCCESS */
        context->state.registers.byte[Z80_H] = (clockticks & 0xff00) >> 8;
        context->state.registers.byte[Z80_L] = (clockticks & 0x00ff);
        return 0;
        break;
    default:
        printf("_Z80_INPUT_BYTE: UNHANDLED PORT: 0x%04x, 0x%02x\n", port, x);
        exit(1);
        break;
    }

    return 1;
}

int _Z80_OUTPUT_BYTE(ZEXTEST *context, uint16_t port, uint8_t x)
{
    //printf("    _Z80_OUTPUT_BYTE(0x%02X, %02X)\n", port, x);
    //((ZEXTEST *) context)->is_done = !0;
    //fflush(NULL);
    //

    switch (port) {
    case 0x01:
        /* CONOUT */
        //printf("CONOUT->[%c]\n", context->state.registers.byte[Z80_A]);

        while (pthread_mutex_trylock(&display_mutex) != 0) {
            //usleep(1000);
            pthread_yield();
        }
        //printf("PUTC acquired lock\n");
        ansitty_putc(context->state.registers.byte[Z80_A]);
        pthread_mutex_unlock(&display_mutex);
        //printf("PUTC released lock\n");
        return 1;
        break;
    case 0x0A:
        /* SELDSK */
        current_drive_id = context->state.registers.byte[Z80_A];
        if (debuglevel) {
            printf("    + SELDSK selecting disk 0x%02x\n", current_drive_id);
        }
        Selected_Drive = (DiskDrive *) GetDriveReference(current_drive_id);
        assert(Selected_Drive);
        return 1;
        break;
    case 0x0B:
        /* SETTRK */
        Selected_Drive = (DiskDrive *) GetDriveReference(current_drive_id);
        assert(Selected_Drive);
        if (debuglevel) {
            printf("    + SETTRK selecting track %u/%u\n", context->state.registers.byte[Z80_A], Selected_Drive->num_tracks);
        }
        Selected_Drive->selected_track = context->state.registers.byte[Z80_A];
        return 1;
        break;
    case 0x0C:
        /* SETSEC */
        Selected_Drive = (DiskDrive *) GetDriveReference(current_drive_id);
        assert(Selected_Drive);
        if (debuglevel) {
            printf("    + SETSEC selecting sector %u/%u\n", context->state.registers.byte[Z80_A], Selected_Drive->num_spt);
        }
        Selected_Drive->selected_sector = context->state.registers.byte[Z80_A];
        return 1;
        break;
    case 0x0D:
        /* DRIVE OPERATION */
        Selected_Drive = (DiskDrive *) GetDriveReference(current_drive_id);
        assert(Selected_Drive);
        if (Selected_Drive->io_in_progress) {
            //printf("IO_IN_PROGRESS on drive %u\n", current_drive_id);
            //assert(!Selected_Drive->io_in_progress);
        }
        pos = (((long)Selected_Drive->selected_track) * ((long)Selected_Drive->num_spt) + Selected_Drive->selected_sector - 1) << 7;
        switch (context->state.registers.byte[Z80_A]) {
        case 0x00:
            /* READ OPERATION */
            if (debuglevel) {
                printf("    + READSEC_START: DMA=0x%04X reading drive %u, track %u, sector %u\n", DMA, current_drive_id, Selected_Drive->selected_track, Selected_Drive->selected_sector);
            }
            Selected_Drive->io_in_progress = true;
            rc = sysbus_ReadFromDriveToMemory(context, current_drive_id, DMA, pos, SECTOR_SIZE);
            //memory_dump(context->memory + DMA, DMA, 128);
            break;
        case 0x01:
            /* WRITE OPERATION */
            if (debuglevel) {
                printf("    + WRITESEC_START: DMA=0x%04X writing drive %u, track %u, sector %u\n", DMA, current_drive_id, Selected_Drive->selected_track, Selected_Drive->selected_sector);
            }
            Selected_Drive->io_in_progress = true;
            rc = sysbus_WriteFromMemoryToDrive(context, current_drive_id, DMA, pos, SECTOR_SIZE);
            break;
        default:
            /* OTHER OPERATION */
            printf("unsupported operation\n");
            assert(NULL);
            break;
        }
        return 1;
        break;
    case 0x0F:
        /* SETDMA (LO) */
        if (debuglevel) {
            printf("    + SETDMA (LO) set low byte 0x%02x\n",  context->state.registers.byte[Z80_A]);
        }
        DMA = (DMA & 0xFF00) + (context->state.registers.byte[Z80_A]);
        return 1;
        break;
    case 0x10:
        /* SETDMA (HI) */
        if (debuglevel) {
            printf("    + SETDMA (HI) set high byte 0x%02x\n",  context->state.registers.byte[Z80_A]);
        }
        DMA = (DMA & 0x00FF) + (context->state.registers.byte[Z80_A] * 0x100);
        return 1;
        break;
    case 0xF0:
        /* HYDROGEN CONTROLLER FUNCTIONS */
        switch(x) {
        case 0x36:
            context->state.registers.byte[Z80_A] = TCP_dispatch(context, DMA, 128);
            //printf("sysbus: context->state.registers.byte[Z80_A] = %d\n", (int8_t) context->state.registers.byte[Z80_A]);
            break;
        default:
            printf("HYDROGEN_CONTROLLER: UNKNOWN FUNCTION %u (0x%02x) \n", x, x);
            assert(NULL);
            break;
        }
        break;
    default:
        printf("_Z80_OUTPUT_BYTE: UNHANDLED PORT: 0x%04x, 0x%02x\n", port, x);
        exit(1);
        break;
    }

    return 0;
}

