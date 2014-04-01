
ARMGNU ?= arm-linux-gnueabi

CFLAGS = -Wall -O3 -nostdlib -nostartfiles -ffreestanding -mcpu=cortex-a9 -std=gnu99 -marm -mthumb-interwork
OBJS = kernel_init.o hal.o payload.o start.o
LIBGCC = /usr/lib/gcc-cross/arm-linux-gnueabi/4.7/libgcc.a

gcc : kernel.img

all : gcc

clean :
	rm -f *.o
	rm -f *.bin
	rm -f *.hex
	rm -f *.elf
	rm -f *.list
	rm -f *.img
	rm -f *.bc
	rm -f *.clang.s

%.o : %.c
	$(ARMGNU)-gcc $(CFLAGS) -c $^ -o $@

%.o : %.s
	$(ARMGNU)-gcc $(CFLAGS) -c $^ -o $@

%.o : %.S
	$(ARMGNU)-gcc $(CFLAGS) -c $^ -o $@

kernel.img : ldscript $(OBJS)
	$(ARMGNU)-ld $(OBJS) $(LIBGCC) -T ldscript -o bootldscript05.elf
	arm-linux-androideabi-objdump -D bootldscript05.elf > bootldscript05.list
	$(ARMGNU)-objcopy bootldscript05.elf -O ihex bootldscript05.hex
	$(ARMGNU)-objcopy bootldscript05.elf -O binary kernel.img

