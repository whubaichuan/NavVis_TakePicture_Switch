#include <msp430G2553.h>
#include "UART.h"

/***********************************************
函数名称：Init_UART
功    能：对BLE进行初始化设置波特率及收发串口，使能接收中断
参    数：无
返回值  ：无
***********************************************/
void Init_UART()
{
   	P1SEL  |= BIT1+BIT2;    //P1.1为RXD,P1.2为TXD
	P1SEL2  |= BIT1+BIT2;  //P1.1为RXD,P1.2为TXD
	UCA0CTL1 |= UCSSEL_2; //选择时钟BRCLK
	UCA0BR0 = 106;   //1Mhz 9600
	UCA0BR1 = 0;     //1Mhz 9600
	UCA0MCTL = UCBRS2 + UCBRS0;  //波特率=BRCLK/(UBR+(M7+...0)/8)
 	UCA0CTL1 &=~ UCSWRST;   //初始化顺序：SWRST=1设置串口 然后设置SWRST=0 最后设置相应中断
 	IE2 |= UCA0RXIE;    //使能接收中断
}

/***********************************************
函数名称：UartPutchar
功    能：将一个字符写入串口发送缓冲区
参    数：等待串口发送的数据
返回值  ：无
***********************************************/
void UartPutchar(unsigned char c)
{
	while(!(IFG2&UCA0TXIFG)); //(待发送为空)
	UCA0TXBUF = c;
	IFG2 &= ~UCA0TXIFG;
}
/***********************************************
函数名称：UartPutNum
功    能：通过串口发送一个数字
参    数：等待串口发送的数字
返回值  ：无
***********************************************/
void UartPutNum(unsigned long int n)
{
	unsigned char number[8];
	unsigned int i;
	number[0] = n / 10000000; //最高位
	number[1] = n % 10000000 / 1000000;
	number[2] = n % 1000000 / 100000;
	number[3] = n % 100000 / 10000;
	number[4] = n % 10000 / 1000;
    number[5] = n % 1000 / 100;
    number[6] = n % 100 / 10;
    number[7] = n % 10;
    for(i = 0;i<8;i++)
    	UartPutchar(number[i]+'0');
}
/***********************************************
函数名称：UartPutStr
功    能：通过串口发送一个字符串
参    数：等待串口发送的字符串
返回值  ：无
***********************************************/
void UartPutStr(unsigned char *s)
{
  while(*s!='\0')
  {
	  UartPutchar(*s++);
  }
}
/***********************************************
函数名称：UartGetchar
功    能：从串口接受缓冲区读取一个字符
参    数：无
返回值  ：读取到的字符
***********************************************/
unsigned char UartGetChar()
{
	unsigned char c;
	while(!(IFG2&UCA0RXIFG)); //(等待接收完成)
	c = UCA0RXBUF;
	IFG2 &= ~UCA0RXIFG;
	//UCA0RXBUF=0;
	return c;
}
/***********************************************
函数名称：UartGetStr
功    能：从串口接受缓冲区读取一个字符串
参    数：字符串指针和字符串长度
返回值  ：无
***********************************************/
void UartGetStr(unsigned char *s,unsigned int cnt)
{
	unsigned int i;
	for(i = 0;i < cnt;i++)
	{
		s[i] = UartGetChar();
	}
}
