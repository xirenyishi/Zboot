OBJS := start.o main.o mem.o dev/dev.o lib/lib.o
	
CFLAGS := -fno-builtin -I$(shell pwd)/include
export CFLAGS

zboot.bin : zboot.elf
	arm-linux-objcopy -O binary zboot.elf zboot.bin

zboot.elf : $(OBJS)	
	arm-linux-ld -Tzboot.lds -o zboot.elf $^
	
%.o : %.S
	arm-linux-gcc -g -c $^
	
%.o : %.c
	arm-linux-gcc -g $(CFLAGS) -c $^
	
lib/lib.o :
	make -C lib all
	
dev/dev.o :
	make -C dev all
	
.PHONY: clean
clean:
	rm *.o *.elf *.bin
	make -C lib clean
	make -C dev clean


