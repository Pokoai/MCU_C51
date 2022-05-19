#include <REG52.H>
#include <intrins.h>

typedef unsigned int u16;
typedef unsigned char u8;

// 全局变量
u8 cnt = 0; 


// 定时器初始化
void timer0_init()
{
    TMOD = 0x01;    // 16位定时器工作方式1
    TH0 = 0x3C;     // 装初值 50ms
    TL0 = 0xB0;
    // TH0 = (65535 - 50000) / 256;    // 这样也可以，但是较低了CPU效率     
    // TL0 = (65535 - 50000) % 256;
    ET0 = 1;       // 允许定时器中断
    EA = 1;        // 开总中断
    TR0 = 1;       // 启动定时器
}

// 定时器中断服务程序
void timer0() interrupt 1
{
    // 装初值
    TH0 = 0x3C;
    TL0 = 0xB0;

    cnt++;
}


void main(void)
{    
    u8 LED = 0x01;  // 第一个灯亮
    u8 cnt2 = 0;    // 闪动10次计数
    u8 temp = 0; 

    timer0_init();  // 定时器0初始化
     
    while(1) {
        P0 = LED;

        if ( 2 == cnt ) {
            cnt = 0;
			cnt2++;

            if ( LED != 0 ) {
                temp = LED;
                LED = 0;
            } else {
                LED = temp;
            }
        }

        if ( 20 == cnt2 ) {
            cnt2 = 0;
            LED = _crol_(LED, 1); // 千万要注意：不能少了 LED = 这部分，
                                  // 移位后记得要重新赋给 LED
        }
    }
}


