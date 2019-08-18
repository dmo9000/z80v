
#include "disk.h"


#define MAX_DRIVES      26
#define SECTOR_SIZE     128

DiskDrive drives[MAX_DRIVES];
DiskDrive *Current_Drive = NULL;

extern int debuglevel;


int disk_init()
{
    off_t offset = 0;
    int id = 0;
    int r = 0;
    struct stat statbuf;
    FILE *fh = NULL;
    int detected = 0;
    for (id = 0; id < MAX_DRIVES; id++) {
        memset(&drives[id], 0, sizeof(DiskDrive));
        memset(&drives[id].diskfilename, 0, 256);
        snprintf((char *) &drives[id].diskfilename, 255, "disks/Drive%c.disk", 48 + id);
        if (!lstat(drives[id].diskfilename, &statbuf)) {
            drives[id].size = statbuf.st_size;

            switch (drives[id].size) {
            case 256256:
                drives[id].num_tracks = 77;
                drives[id].num_spt = 26;
                break;
            case 4177920:
                drives[id].num_tracks = 255;
                drives[id].num_spt = 128;
                break;
            default:
                printf("+++ unrecognized disk format\n");
                assert(NULL);
                break;
            }

            drives[id].present = true;
            printf(" * detected drive %c: %s, size = %lu", 65 + id, drives[id].diskfilename, drives[id].size);
            drives[id].backingstore = malloc(drives[id].size);
            memset(drives[id].backingstore, 0, drives[id].size);
            assert(drives[id].backingstore);
            fh = fopen(drives[id].diskfilename, "rb");
            assert(fh);
            fseek(fh, 0, SEEK_SET);
            for (offset = 0; offset < drives[id].size; offset += SECTOR_SIZE) {
                unsigned char *ptr = drives[id].backingstore;
                ptr += offset;
                r = fread(ptr, SECTOR_SIZE, 1, fh);
                assert(r);
            }
            assert(offset == drives[id].size);
            printf(" ... OK\n");
            drives[id].present = true;
            detected++;
            fclose(fh);
        }
    }


    for (id = 0; id < MAX_DRIVES ; id++) {
        if (drives[id].present) {
            printf("DEFAULT DRIVE SLOT SELECTED: %u\n", id);
            Current_Drive = &drives[id];
            return detected;
        }
    }

    return detected;
}
