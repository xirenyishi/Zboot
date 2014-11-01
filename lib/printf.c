 #include "vsprintf.h"

unsigned char outbuf[1024];
unsigned char inbuf[1024];


int printf(const char *fmt, ...)
{
	va_list args;
	int i;
	
	//1.�����ת��Ϊ�ַ���;ʹ����3���Ѿ����ڵĺ���	
	va_start(args,fmt);     //����fmt�õ���εĸ�����Ȼ��ѱ�ηŵ�args����
	vsprintf((char*)outbuf,fmt,args);     //�����argsת��Ϊ�ַ���
	va_end();    //����ת��
	
	//2.��ӡ�ַ���������
	for(i=0;i<strlen((char*)outbuf);i++)
	{
		putchar(outlen[i]);	
	}
	 return i;
}

int scanf(const char * fmt, ...)
{
	unsigned char c;
	int i = 0;
	va_list args;
	
	//1. ��ȡ������ַ���
	while(1)
	{
		c = getchar();	
		if((c==0x0d)||(c==0x0a))
		{
			inbuf[i] = '\n';
			break;	
		}
		else
		{
			inbuf[i++] = c;	
		}
	}
	//2. ��ʽת��	
	va_start(args, fmt);
	vsscanf((char *)inbuf,fmt,args);
	va_end(args);
	return i;
}