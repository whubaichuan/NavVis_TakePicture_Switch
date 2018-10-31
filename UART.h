//数据格式说明：8位数据位 无奇偶校验 1位停止位  固定波特率
#ifndef __HC06_H
#define __HC06_H

void Init_UART();
void UartPutchar(unsigned char c);
void UartPutStr(unsigned char *s);
void UartPutNum(unsigned long int n);//8位（十进制）
unsigned char UartGetChar();
void UartGetStr(unsigned char *s,unsigned int cnt);

#endif
