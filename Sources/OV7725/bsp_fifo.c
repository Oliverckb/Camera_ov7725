#include "bsp_fifo.h"



/************************************************
 * ��������FIFO_Init
 * ����  ��FIFO��ʼ��
 * ����  ����
 * ���  ����
 ************************************************/
void FIFO_Init(void)
{

     //дFIFO
 //    DDRE_DDRE2=1;   //дʹ��WEN���� ��PE2�����
  //   DDRE_DDRE3=1;   //д��λWRST���ƣ�PE3�����
     
     
     //��FIFO
 //    DDRE_DDRE4=1;   //��ʹ��OE����   (PE4���)
  //   DDRE_DDRE5=1;   //��ʱ��RCLK���� (PE5���) 
  //   DDRE_DDRE6=1;   //����λRRST���� (PE6���)                              
     
     //FIFO����
  //   DDRA=0x00;     //PORTAΪFIFO���ݽ��տ�  �����룩
     
 //    FIFO_WE_L();   //д��ֹ

  
}

/************************************************
 * ��������FIFO_READ
 * ����  ����FIFO�ж���RGB565��16λ����
 * ����  ����
 * ���  ��16λuint������ֵ
************************************************/
uint FIFO_READ(void)
{
    uint RGB565=0;
  //  FIFO_RCLK_L();
    FIFO_RCLK_H();
  //  RGB565=PORTA;               //   R    G
    RGB565=(RGB565<<8)&0XFF00;  // ***** *** ........  R��5λ��G��3λ
    FIFO_RCLK_L();   
    FIFO_RCLK_H();   //  R      G     B
    RGB565|=PORTA;   //***** ****** *****
      
    return RGB565;
  
}