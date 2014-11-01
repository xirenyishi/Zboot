#include "mmu.h"

void mem_map_init(void)
{
	unsigned long virtuladdr, physicaladdr;
	unsigned long *mmu_tlb_base = (unsigned long *)0x50000000;
	
    /* Steppingstone的起始物理地址为0，第一部分程序的起始运行地址也是0，
     * 为了在开启MMU后仍能运行第一部分的程序，
     * 将0～1M的虚拟地址映射到同样的物理地址
     *
     *virtuladdr = 0x0;
     *physicaladdr = 0x0;
     **(mmu_tlb_base + (virtuladdr >> 20)) = (physicaladdr & 0xFFF00000) | \
                                            MMU_SECDESC_WB;
     */ 
                                           
	 /*
     * 0x56000000是GPIO寄存器的起始物理地址，
     * GPBCON和GPBDAT这两个寄存器的物理地址0x56000010、0x56000014，
     * 为了在第二部分程序中能以地址0xA0000010、0xA0000014来操作GPBCON、GPBDAT，
     * 把从0xA0000000开始的1M虚拟地址空间映射到从0x56000000开始的1M物理地址空间
     */
    virtuladdr = 0xA0000000;
	physicaladdr = 0x7f000000;
    *(mmu_tlb_base + (virtuladdr >> 20)) = (physicaladdr & 0xFFF00000) | \
                                            MMU_SECDESC;
                                            
	 /*
     * SDRAM的物理地址范围是0x30000000～0x33FFFFFF，
     * 将虚拟地址0xB0000000～0xB3FFFFFF映射到物理地址0x30000000～0x33FFFFFF上，
     * 总共64M，涉及64个段描述符
     */
    virtuladdr = 0x50000000;
    physicaladdr = 0x50000000;
    while (virtuladdr < 0x54000000)
    {
        *(mmu_tlb_base + (virtuladdr >> 20)) = (physicaladdr & 0xFFF00000) | \
                                                MMU_SECDESC_WB;
        virtuladdr += 0x100000;
        physicaladdr += 0x100000;
    }
}

void mmu_init(void)
{
	__asm__(
		/*设置TTB*/
		"ldr    r0, =0x50000000\n"                  
    	"mcr    p15, 0, r0, c2, c0, 0\n"
		
		/*不进行权限检查*/
		"mvn    r0, #0\n"                   
    	"mcr    p15, 0, r0, c3, c0, 0\n"
    
		/*使能MMU*/
		"mrc    p15, 0, r0, c1, c0, 0\n"    
    	"orr    r0, r0, #0x0001\n"          
    	"mcr    p15, 0, r0, c1, c0, 0\n"
		:
		:
	);
}