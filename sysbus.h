#include <stdint.h>
#include "z80.h"

int sysbus_dump();
int sysbus_in(uint16_t port);
int sysbus_out(uint16_t port, uint8_t val);
