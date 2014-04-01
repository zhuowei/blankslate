#include "hal.h"
#include "util.h"

#define REALVIEW_UART0_OFFSET 0x10009000
#define PL011_FLAG_TXFF (1 << 3)

void HalDebugPutc(char c) {
	while(HW_REG(REALVIEW_UART0_OFFSET + 0x18) & PL011_FLAG_TXFF){
	}
	HW_REG(REALVIEW_UART0_OFFSET) = c;
}

void HalDebugPuts(const char* str) {
	while(*str) {
		HalDebugPutc(*str++);
	}
	HalDebugPutc('\n');
}
