/* ����ͷ�ļ� */
#include <ioCC2530.h>

/*�궨��*/
#define LED1 P1_0 
#define LED2 P1_1
#define SW1 P1_2

/*�������*/
unsigned char counter = 0; //ͳ�ƶ�ʱ���������
unsigned char flag = 0;//�������´�����־λ��0Ϊż���ΰ��£�1Ϊ�����ΰ���

/*��������*/
void InitCLK(void);//ϵͳʱ�ӳ�ʼ��������Ϊ32MHz
void InitLED(void);//LED�Ƴ�ʼ��
void InitSW1(void);//������ʼ��
void InitT1(void);//��ʱ��1��ʼ��
void InitUART0(void);//����0��ʼ��
void UART0SendByte(unsigned char c);//UART0����һ���ֽں���
void UART0SendString(unsigned char *str);//UART0���������ַ���

/*���庯��*/
void InitCLK(void)
{
  CLKCONCMD &= 0x80;
  while(CLKCONSTA & 0x40);
}
void InitLED()
{
  /*.......������1��ʼ��LED��IO�˿ڳ�ʼ��....................*/
  P1SEL &= ~0x03;//����P1_0��P1_1ΪGPIO��
   //����P1_0��P1_1Ϊ���

  //����LED1��LED2�ĳ�ʼ״̬

  /*.......������1����.......................................*/
}

void InitSW1()
{
   /*.......������2��ʼ�������ж����빦�ܳ�ʼ��...............*/
  P1SEL &= ~0x04;//����P1_2ΪGPIO��
 //����P1_2Ϊ����

 //����P1_2�˿�Ϊ������/������ģʽ

 //��������P1�˿�Ϊ��������

  //����P1_2�˿��жϴ�����ʽΪ���½��ش���

 //ʹ��P1�˿��ж�

 //ʹ��P1_2�˿��ж�

  /*.......������2����.......................................*/
  
}

void InitT1()
{
  /*.......������3��ʼ����ʱ��1��ʼ��........................*/
 //T1CTL ���ö�ʱ��1Ϊ32��Ƶ����ͣ����

 //ʹ�ܶ�ʱ��1������ж�

 //ʹ�ܶ�ʱ��1�ж� 

  /*.......������3����.......................................*/

}
void InitUART0()
{
  /*.......������4��ʼ������0��ʼ��.........................*/
  PERCFG = 0x00;	
  P0SEL = 0x3c;	
   //U0CSR����USART0ΪUARTģʽ

 //���ò�����14400
 
  U0UCR |= 0x80;
  // ����USART0 TX�жϱ�־ 

  /*.......������4����.......................................*/
    
}

void UART0SendByte(unsigned char c)
{
  U0DBUF = c;// ��Ҫ���͵�1�ֽ�����д��U0DBUF
  while (!UTX0IF) ;// �ȴ�TX�жϱ�־����U0DBUF����
  UTX0IF = 0;// ����TX�жϱ�־
}

void UART0SendString(unsigned char *str)
{
  while(*str != '\0')
  {
    UART0SendByte(*str++);
  }
}

/*������*/
void main(void)
{
  InitCLK();//ϵͳʱ��
  InitLED();//LED��
  InitSW1();//����
  InitT1();//��ʱ��1  
  
  EA = 1;//ʹ�����ж�  
  while(1);
}

/*�жϷ�����*/
/*.......������5��ʼ�������жϷ�����...........*/
#pragma vector = P1INT_VECTOR
__interrupt void P1_ISR(void)
{
  if(P1IFG & 0x04)
  {
    if(flag == 0)
    {
      flag = 1;
    //����LED1��ʼ״̬

      //����LED2��ʼ״̬

     //T1CNTL ���㶨ʱ��1�����Ĵ���

      //T1CTL ��ʱ��1��������

     //ͨ�����ڷ��͡�run mode��

    }
    else
    {
      flag = 0;
       //Ϩ��LED1��LED2
     
       //��ʱ��1��ͣ����  ���λ��0ʵ����ͣ����

       //ͨ�����ڷ��͡�stop mode��
    }
    
   //P1IFG ���P1_2���жϱ�־λ

  }
  P1IF = 0;
}
/*.......������5����...........*/

#pragma vector = T1_VECTOR
__interrupt void T1_ISR(void)
{
  counter++;
  if(counter>10)
  {
    LED1 = ~LED1;
    LED2 = ~LED2;
    counter = 0;
  }
}
