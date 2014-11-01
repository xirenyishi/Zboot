#define GPACON (*((volatile unsigned long *)0x7f008000))

#define ULCON0 (*((volatile unsigned long *)0x7f005000))
#define UCON0 (*((volatile unsigned long *)0x7f005004))
#define UFCON0 (*((volatile unsigned long *)0x7f005008))
#define UMCON0 (*((volatile unsigned long *)0x7f00500c))
#define UBRDIV0 (*((volatile unsigned short *)0x7f005028))
#define UDIVSLOT0 (*((volatile unsigned short *)0x7f00502c))

#define UFSTAT0 (*((volatile unsigned long *)0x7f005018))
#define URXH0 (*((volatile unsigned char *)0x7f005024 ))
#define UTXH0 (*((volatile unsigned char *)0x7f005020))

void uart_init(void)
{
	//1.配置GPA引脚功能为UART
	GPACON &= ~0xff;
	GPACON |= 0x22;
	
	//2.1 设置数据格式
	ULCON0 = 0x3; /* 数据位:8; 无较验; 停止位: 1; 8n1 */
	
	//2.2设置工作模式
	UCON0 = 0x5;  /*使能UART发送、接收*/
	
	//2.3FIFO ENABLE
	UFCON0 = 0x1;
	
	//2.4 流量控制关闭
	UMCON0 = 0x0;
	
	//3设置波特率：DIV_VAL = (PCLK / (bps x 16 ) ) - 1； bps = 115200  DIV_VAL = (66500000 / (115200 x 16 ) ) - 1 = 35.08
	UBRDIV0 = 35;
	/* x/16 = 0.08
	 * x = 1
	 */
	UDIVSLOT0 = 0x1;
	
}

char getchar(void)
{
	//只要UFSTAT0 bit5、6不为0就是有数据
	while((UFSTAT0 & 0x7f) == 0);  /*如果RX FIFO空，则等待*/
	return URXH0;                  /*取数据*/
}

void putchar(unsigned char c)
{
    while (UTRSTAT0 & (1<<14));  /*如果TX FIFO满，则等待*/
	UTXH0 = c;                    /*写数据*/
}