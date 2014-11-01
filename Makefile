all: start.o main.o mmu.o led.o mem.o interrupt.o button.o uart.o
	arm-linux-ld -Tzboot.lds -o zboot.elf $^
	arm-linux-objcopy -O binary zboot.elf zboot.bin
	
%.o : %.S
	arm-linux-gcc -g -c $^
	
%.o : %.c
	arm-linux-gcc -g -c $^
	
.PHONY: clean
clean:
	rm *.o *.elf *.bin


