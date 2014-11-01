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
	//1.����GPA���Ź���ΪUART
	GPACON &= ~0xff;
	GPACON |= 0x22;
	
	//2.1 �������ݸ�ʽ
	ULCON0 = 0x3; /* ����λ:8; �޽���; ֹͣλ: 1; 8n1 */
	
	//2.2���ù���ģʽ
	UCON0 = 0x5;  /*ʹ��UART���͡�����*/
	
	//2.3FIFO ENABLE
	UFCON0 = 0x1;
	
	//2.4 �������ƹر�
	UMCON0 = 0x0;
	
	//3���ò����ʣ�DIV_VAL = (PCLK / (bps x 16 ) ) - 1�� bps = 115200  DIV_VAL = (66500000 / (115200 x 16 ) ) - 1 = 35.08
	UBRDIV0 = 35;
	/* x/16 = 0.08
	 * x = 1
	 */
	UDIVSLOT0 = 0x1;
	
}

char getchar(void)
{
	//ֻҪUFSTAT0 bit5��6��Ϊ0����������
	while((UFSTAT0 & 0x7f) == 0);  /*���RX FIFO�գ���ȴ�*/
	return URXH0;                  /*ȡ����*/
}

void putchar(unsigned char c)
{
    while (UTRSTAT0 & (1<<14));  /*���TX FIFO������ȴ�*/
	UTXH0 = c;                    /*д����*/
}