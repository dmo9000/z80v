#include <stdint.h>
#include <pthread.h>

#define ZEXTEST	char

int sysbus_init();
int sysbus_disks_init();
int sysbus_bootloader(ZEXTEST *context);
int sysbus_ReadFromDriveToMemory(ZEXTEST *context, int driveid, uint16_t tgt_addr, off_t src_offset, uint16_t bytes);
int run_emulation();

