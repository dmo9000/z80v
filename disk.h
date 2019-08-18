#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <stdint.h>
#include <stdbool.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string.h>
#include "z80.h"

struct _disk_drive {
                    int driveid;
                    char diskfilename[256];
                    bool present;
                    size_t size;
                    uint8_t num_tracks;
                    uint8_t num_spt;
                    uint16_t selected_track;
                    uint16_t selected_sector;
                    bool io_in_progress;
                    unsigned char *backingstore;
                    };

typedef struct _disk_drive DiskDrive;


int disk_init();
int disk_readfromdrivetomemory(Z80 *CPU, int driveid, uint16_t tgt_addr, off_t src_offset, uint16_t bytes);
int disk_writefrommemorytodrive(Z80 *CPU, int driveid, uint16_t src_addr, off_t tgt_addr, uint16_t bytes);
DiskDrive *GetDriveReference(int id);

