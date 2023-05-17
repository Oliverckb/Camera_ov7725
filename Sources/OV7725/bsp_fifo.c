#include "bsp_fifo.h"



/************************************************
 * 函数名：FIFO_Init
 * 描述  ：FIFO初始化
 * 输入  ：无
 * 输出  ：无
 ************************************************/
void FIFO_Init(void)
{

     //写FIFO
 //    DDRE_DDRE2=1;   //写使能WEN控制 （PE2输出）
  //   DDRE_DDRE3=1;   //写复位WRST控制（PE3输出）
     
     
     //读FIFO
 //    DDRE_DDRE4=1;   //读使能OE控制   (PE4输出)
  //   DDRE_DDRE5=1;   //读时钟RCLK控制 (PE5输出) 
  //   DDRE_DDRE6=1;   //读复位RRST控制 (PE6输出)                              
     
     //FIFO数据
  //   DDRA=0x00;     //PORTA为FIFO数据接收口  （输入）
     
 //    FIFO_WE_L();   //写禁止

  
}

/************************************************
 * 函数名：FIFO_READ
 * 描述  ：从FIFO中读出RGB565的16位像素
 * 输入  ：无
 * 输出  ：16位uint的像素值
************************************************/
uint FIFO_READ(void)
{
    uint RGB565=0;
  //  FIFO_RCLK_L();
    FIFO_RCLK_H();
  //  RGB565=PORTA;               //   R    G
    RGB565=(RGB565<<8)&0XFF00;  // ***** *** ........  R的5位，G的3位
    FIFO_RCLK_L();   
    FIFO_RCLK_H();   //  R      G     B
    RGB565|=PORTA;   //***** ****** *****
      
    return RGB565;
  
}