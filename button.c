#define GPNCON (volatile unsigned long*)0x7f008830
#define GPL1CON (volatile unsigen long*)0x7f008814

void button_init(void)
{
	*(GPNCON)=0xaaa;  //����btn0~5ȫ��Ϊ�ж�����
	*(GPL1CON)=0b0011<<16;  //����btn12Ϊ�ж�����	
}