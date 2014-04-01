#include "payload.h"
#include "hal.h"

void KernelInit() {
	HalSetupMemory();
	PayloadInit();
	HalHaltCPU();
}
