/*interrupt registes*/
#define EXT_INT_0_CON       *((volatile unsigned int *)0x7f008900)   
#define EXT_INT_1_CON       *((volatile unsigned int *)0x7f008904)  
#define EXT_INT_0_MASK      *((volatile unsigned int *)0x7f008920) 
#define EXT_INT_0_PEND      *((volatile unsigned int *)0x7f008924)     
   
#define VIC1INTENABLE       *((volatile unsigned int *)0x71300010)

#define EINT0_VECTADDR      *((volatile unsigned int *)0x71200100)     
#define EINT20_VECTADDR     *((volatile unsigned int *)0x71300104) 
#define VIC0ADDRESS         *((volatile unsigned int *)0x71200f00)   
#define VIC1ADDRESS         *((volatile unsigned int *)0x71300f00)

#define PRIORITY    (*((volatile unsigned long *)0x7F008280))
#define SERVICE     (*((volatile unsigned long *)0x7F008284))
#define SERVICEPEND (*((volatile unsigned long *)0x7F008288))


#define VIC0IRQSTATUS  (*((volatile unsigned long *)0x71200000))
#define VIC0FIQSTATUS  (*((volatile unsigned long *)0x71200004))
#define VIC0RAWINTR    (*((volatile unsigned long *)0x71200008))
#define VIC0INTSELECT  (*((volatile unsigned long *)0x7120000c))
#define VIC0INTENABLE  (*((volatile unsigned long *)0x71200010))
#define VIC0INTENCLEAR (*((volatile unsigned long *)0x71200014))
#define VIC0PROTECTION (*((volatile unsigned long *)0x71200020))
#define VIC0SWPRIORITYMASK (*((volatile unsigned long *)0x71200024))
#define VIC0PRIORITYDAISY  (*((volatile unsigned long *)0x71200028))


void irq_init(void)
{
	
	/* 配置为下降沿触发 */
	EXT_INT_0_CON &= ~(0xfff);
	EXT_INT_0_CON |= 0xaaa;	
	
	/* 取消EINT0~EINT5屏蔽外部中断 */
	EXT_INT_0_MASK &= ~(0x3f);
	
	/* 使能外部中断*/
	VIC0INTENABLE |=0x3;   /* bit0: EINT0~3, bit1: EINT4~11 */
}