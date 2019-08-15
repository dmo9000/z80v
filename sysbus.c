#include <stdio.h>
#include <assert.h>

/* z80emu compatible BIOS */

uint8_t selected_disk = 0;
uint8_t selected_track = 0;
uint8_t selected_sector = 0;
uint16_t dma_addr = 0;


int sysbus_out(uint16_t port, uint8_t val)
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
