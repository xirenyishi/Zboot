char *buf = "Hello World!";  //我们要发送的数据

#define DISRC0 (*(volatile unsigned long*)0x4B000000)
#define DISRCC0 (*(volatile unsigned long*)0x4B000004)
#define DIDST0 (*(volatile unsigned long*)0x4B000008)
#define DIDSTC0 (*(volatile unsigned long*)0x4B00000C)
#define DCON0 (*(volatile unsigned long*)0x4B000010)
#define DMASKTRIG0 (*(volatile unsigned long*)0x4B000020)

#define UTXH0 (volatile unsigned long*)0x50000020

void dma_init()
{
	//1.初始化源地址
	DISRC0 = (unsigned int)buf;
	DISRCC0 = (0<<1)|(0<0);
	
	//2.初始化目的地址	
	DIDST0 = UTXH0;    //把UTXH0的地址赋值给DIDST0的内容
	DIDSTC0 = (0<<2)|(1<<1)|(1<<0);
	
	DCON0 = (1<<24)|(1<<23)|(1<<22)|(12<<0);   //Hello World!=12字符
}

void dma_start()
{
	DMASKTRIG0 = (1<<1);	
}