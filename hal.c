#include "hal.h"
#include "util.h"

#define REALVIEW_UART0_OFFSET 0x10009000
#define PL011_FLAG_TXFF (1 << 3)

#define MMU_SECTION 0x2
#define MMU_BUFFERABLE (1 << 2)
#define MMU_CACHEABLE (1 << 3)
#define MMU_RESERVED1 (1 << 4)
#define MMU_AP_ALL (0x3 << 10)

static unsigned int* HalTTB = (void*) 0x000f0000;

void HalDebugPutc(char c) {
	while(HW_REG(REALVIEW_UART0_OFFSET + 0x18) & PL011_FLAG_TXFF) {
		BARRIER();
	}
	HW_REG(REALVIEW_UART0_OFFSET) = c;
}

void HalDebugPuts(const char* str) {
	while(*str) {
		HalDebugPutc(*str++);
	}
	HalDebugPutc('\r');
	HalDebugPutc('\n');
}

void HalDebugPutHex(unsigned int input) {
	for (int i = 7; i >= 0; i--) {
		unsigned int digit = (input >> (i << 2)) & 0xf;
		char c = (digit < 0xa? ('0' + digit) : ('a' + (digit - 0xa)));
		HalDebugPutc(c);
	}
	HalDebugPutc('\r');
	HalDebugPutc('\n');
}

void HalSetupMemory() {
	HalDebugPuts("Setting up MMU");
	int perms = MMU_SECTION | MMU_BUFFERABLE | MMU_CACHEABLE | MMU_RESERVED1 | MMU_AP_ALL;
	/* identity map the MMU */
	for (unsigned int i = 0; i < 0x1000; i++) {
		unsigned int ttbEntry = i << 20 | perms;
		HalTTB[i] = ttbEntry;
	}
	HalDebugPuts("Starting MMU");
	HalSetMMUTTB(HalTTB);
	HalSetMMUDomain();
	HalEnableMMU();
	HalEnableICache();
	HalEnableDCache();
}
