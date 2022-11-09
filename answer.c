/* 包含头文件 */
#include <ioCC2530.h>

/*宏定义*/
#define LED1 P1_0 
#define LED2 P1_1
#define SW1 P1_2

/*定义变量*/
unsigned char counter = 0; //统计定时器溢出次数
unsigned char flag = 0;//按键按下次数标志位，0为偶数次按下，1为奇数次按下

/*声明函数*/
void InitCLK(void);//系统时钟初始化函数，为32MHz
void InitLED(void);//LED灯初始化
void InitSW1(void);//按键初始化
void InitT1(void);//定时器1初始化
void InitUART0(void);//串口0初始化
void UART0SendByte(unsigned char c);//UART0发送一个字节函数
void UART0SendString(unsigned char *str);//UART0发送整个字符串

/*定义函数*/
void InitCLK(void)
{
  CLKCONCMD &= 0x80;
  while(CLKCONSTA & 0x40);
}
void InitLED()
{
  /*.......答题区1开始：LED灯IO端口初始化....................*/
  P1SEL &= ~0x03;//设置P1_0、P1_1为GPIO口
  P1DIR |= 0x03;//设置P1_0和P1_1为输出
  LED1 = LED2 = 0;//设置LED1和LED2的初始状态
  /*.......答题区1结束.......................................*/
}

void InitSW1()
{
   /*.......答题区2开始：按键中断输入功能初始化...............*/
  P1SEL &= ~0x04;//设置P1_2为GPIO口
  P1DIR &= ~0x04;//设置P1_2为输入
  P1INP &= ~0x04;//设置P1_2端口为“上拉/下拉”模式
  P2INP &= ~0x40;//设置所有P1端口为“上拉”
  PICTL |= 0x02;//设置P1_2端口中断触发方式为：下降沿触发
  IEN2 |= 0x10;//使能P1端口中断
  P1IEN |= 0x04;//使能P1_2端口中断
  /*.......答题区2结束.......................................*/
  
}

void InitT1()
{
  /*.......答题区3开始：定时器1初始化........................*/
  T1CTL = 0x08;//设置定时器1为32分频、暂停运行
  TIMIF |= 0x40;//使能定时器1的溢出中断
  T1IE = 1;//使能定时器1中断 
  /*.......答题区3结束.......................................*/

}
void InitUART0()
{
  /*.......答题区4开始：串口0初始化.........................*/
  PERCFG = 0x00;	
  P0SEL = 0x3c;	
  U0CSR |= 0x80;//设置USART0为UART模式
  U0BAUD = 216;//设置波特率14400
  U0GCR = 8;
  U0UCR |= 0x80;
  UTX0IF = 0;  // 清零USART0 TX中断标志 
  /*.......答题区4结束.......................................*/
    
}

void UART0SendByte(unsigned char c)
{
  U0DBUF = c;// 将要发送的1字节数据写入U0DBUF
  while (!UTX0IF) ;// 等待TX中断标志，即U0DBUF就绪
  UTX0IF = 0;// 清零TX中断标志
}

void UART0SendString(unsigned char *str)
{
  while(*str != '\0')
  {
    UART0SendByte(*str++);
  }
}

/*主函数*/
void main(void)
{
  InitCLK();//系统时钟
  InitLED();//LED灯
  InitSW1();//按键
  InitT1();//定时器1  
  InitUART0();//初始化串口
  
  EA = 1;//使能总中断  
  while(1);
}

/*中断服务函数*/
/*.......答题区5开始：按键中断服务函数...........*/
#pragma vector = P1INT_VECTOR
__interrupt void P1_ISR(void)
{
  if(P1IFG & 0x04)
  {
    if(flag == 0)
    {
      flag = 1;
      LED1 = 1; //设置LED1初始状态
      LED2 = 0; //设置LED2初始状态
      T1CNTL = 1;//清零定时器1计数寄存器
      T1CTL |= 0x01;//定时器1自由运行
      UART0SendString("run mode\r\n");//通过串口发送“run mode”
    }
    else
    {
      flag = 0;
      LED1 = 0;//熄灭LED1和LED2
      LED2 = 0;
      T1CTL &= ~0x01;//定时器1暂停运行  最低位清0实现暂停运行
      UART0SendString("stop mode\r\n");//通过串口发送“stop mode”
    }
    
    P1IFG &= ~0x04;//清除P1_2口中断标志位
  }
  P1IF = 0;
}
/*.......答题区5结束...........*/

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
