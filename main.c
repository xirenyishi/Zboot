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
	
	//����3����ʼ��DMA������
	dma_init();
	dma_start();
	
	while(1)
	{
		c=getchar();
		putchar(c+1);	 /*����1����ʾ2*/
		
		printf("\n\r***************************************\n\r");
    	printf("\n\r*****************GBOOT*****************\n\r");
    	printf("1:Download Linux Kernel from TFTP Server!\n\r");
    	printf("2:Boot Linux from RAM!\n\r");
    	printf("3:Boor Linux from Nand Flash!\n\r");
    	printf("\n Plese Select:");
    	
    	scanf("%d",&num);
    
        switch (num)
        {
            case 1:
            //tftp_load();
            break;
            
            case 2:
            //boot_linux_ram();
            break;
            
            case 3:
            //boot_linux_nand();
            break;
            
            default:
                printf("Error: wrong selection!\n\r");
            break;	
		}
	}
	
	*(GPKCON)=0x11110000;
	*(GPKDAT)=0xa0;
	return 0;	
}