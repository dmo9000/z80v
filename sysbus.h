#include <stdint.h>
#include "z80.h"

int sysbus_dump();
int sysbus_init();
int sysbus_in(Z80 *CPU, uint16_t port);
int sysbus_out(Z80 *CPU, uint16_t port, uint8_t val);

bool test_bank_switching();
int bootloader_hack();
