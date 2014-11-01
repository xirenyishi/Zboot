#define GPKCON (volatile unsigned long*)0x7f008800
#define GPKDAT (volatile unsigned long*)0x7f008808

#include "mmu.h"
#include "uart.h"


int zboot_main()
{
	//����1���洢��ӳ���ʼ����MMU��ʼ��
	mem_map_init();
	mmu_init();
	putstr("Succeed memory mapping.\r\n");   //����zboot������RAM�У�MMU��ʹ��
	
	//����2����ʼ������,���������ʡ�����λ��ֹͣλ����żУ��λ��
	char c;
	uart_init();
	
	while(1)
	{
		c=getchar();
		putchar(c+1);	 /*����1����ʾ2*/
		
	}
	
	*(GPKCON)=0x11110000;
	*(GPKDAT)=0xa0;
	return 0;	
}