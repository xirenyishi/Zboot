#define GPKCON (volatile unsigned long*)0x7f008800
#define GPKDAT (volatile unsigned long*)0x7f008808

#include "mmu.h"
#include "uart.h"


int zboot_main()
{
	//步骤1：存储器映射初始化，MMU初始化
	mem_map_init();
	mmu_init();
	putstr("Succeed memory mapping.\r\n");   //现在zboot运行在RAM中，MMU被使能
	
	//步骤2：初始化串口,包括波特率、数据位、停止位、奇偶校验位等
	char c;
	uart_init();
	
	while(1)
	{
		c=getchar();
		putchar(c+1);	 /*发送1，显示2*/
		
	}
	
	*(GPKCON)=0x11110000;
	*(GPKDAT)=0xa0;
	return 0;	
}