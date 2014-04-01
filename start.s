.section .text.boot
.global _start
_start:
	mov sp, #0x00100000
	bl KernelInit

.section .text

.global HalSetMMUTTB
HalSetMMUTTB:
	mcr p15, 0, r0, c2, c0, 0
	bx lr

.global HalEnableMMU
HalEnableMMU:
	mrc p15, 0, r0, c1, c0, 0
	orr r0, #1
	mcr p15, 0, r0, c1, c0, 0
	bx lr

.global HalEnableDCache
HalEnableDCache:
	mrc p15, 0, r0, c1, c0, 0
	orr r0, #(1 << 2)
	mcr p15, 0, r0, c1, c0, 0
	bx lr

.global HalEnableICache
HalEnableICache:
	mrc p15, 0, r0, c1, c0, 0
	orr r0, #(1 << 12)
	mcr p15, 0, r0, c1, c0, 0
	bx lr

.global HalSetMMUDomain
HalSetMMUDomain:
	mov r0, #0x3
	mcr p15, 0, r0, c3, c0, 0
	bx lr

.global HalHaltCPU
HalHaltCPU:
	cpsid if
endlessloop:
	wfi
	b endlessloop
