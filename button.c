#define GPNCON (volatile unsigned long*)0x7f008830
#define GPL1CON (volatile unsigen long*)0x7f008814

void button_init(void)
{
	*(GPNCON)=0xaaa;  //设置btn0~5全部为中断输入
	*(GPL1CON)=0b0011<<16;  //设置btn12为中断输入	
}