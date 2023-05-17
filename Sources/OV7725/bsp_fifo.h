#ifndef bsp_fifo_H
#define bsp_fifo_H


#include "COMMON.h"
#include "Users.h"

//OE��ʹ�ܿ�������   PE4  
#define FIFO_CS_H()     PORTE_PE4=1	  /*���߽�ֹFIFO���ʹ��*/
#define FIFO_CS_L()     PORTE_PE4=0	  /*����ʹFIFO���ʹ��*/
//��ʱ��RCLK�������� PE5
#define FIFO_RCLK_H()   PORTE_PE5=1	  
#define FIFO_RCLK_L()   PORTE_PE5=0	  /*FIFO�������ʱ��*/
//����λRRST�������� PE6
#define FIFO_RRST_H()   PORTE_PE6=1	  /*��������FIFO��(���ݴ�FIFO���)ָ���˶� */
#define FIFO_RRST_L()   PORTE_PE6=0	  /*����ʹFIFO��(���ݴ�FIFO���)ָ�븴λ */


//дʹ��WEN�������� PE2
#define FIFO_WE_H()     PORTE_PE2=1	  /*����ʹFIFOд����*/
#define FIFO_WE_L()     PORTE_PE2=0
//д��λWRST��������PE3
#define FIFO_WRST_H()   PORTE_PE3=1	  /*��������FIFOд(����from����ͷ)ָ���˶� */
#define FIFO_WRST_L()   PORTE_PE3=0	  /*����ʹFIFOд(����from����ͷ)ָ�븴λ*/




//FIFOΪ��׼��
#define FIFO_PREPARE()      FIFO_RRST_L();\
	                          FIFO_RCLK_L();\
	                          FIFO_RCLK_H();\
	                          FIFO_RCLK_L();\
	                          FIFO_RCLK_H();\
	                          FIFO_RRST_H();\
	                          FIFO_RCLK_L();\
	                          FIFO_RCLK_H();\
	                          FIFO_CS_L()  
	                          
 
 
 //дFIFO
 #define WRITE_FIFO()  FIFO_WRST_L();\
                       FIFO_WRST_H();\
                       FIFO_WE_H()                           

 //��ֹдFIFO
 #define DIS_WRITE_FIFO();    FIFO_WE_L()    //����ʹFIFOд��ͣ



/************************************************
 * ��������FIFO_Init
 * ����  ��FIFO��ʼ��
 * ����  ����
 * ���  ����
 ************************************************/
void FIFO_Init(void);
/************************************************
 * ��������FIFO_READ
 * ����  ����FIFO�ж���RGB565��16λ����
 * ����  ����
 * ���  ��16λuint������ֵ
************************************************/
uint FIFO_READ(void);




#endif