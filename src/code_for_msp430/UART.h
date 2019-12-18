//���ݸ�ʽ˵����8λ����λ ����żУ�� 1λֹͣλ  �̶�������
#ifndef __HC06_H
#define __HC06_H

void Init_UART();
void UartPutchar(unsigned char c);
void UartPutStr(unsigned char *s);
void UartPutNum(unsigned long int n);//8λ��ʮ���ƣ�
unsigned char UartGetChar();
void UartGetStr(unsigned char *s,unsigned int cnt);

#endif
