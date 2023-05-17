#ifndef User_H
#define User_H


#include "COMMON.h"
#include "math.h"

#include "IO.h"
#include "PLL.h"
#include "PWM.h"
#include "Delay.h"
#include "IC.h"
#include "PIT.h"
#include "SCI.h"

#include "bsp_sccb.h"
#include "bsp_fifo.h"
#include "Image.h"
#include "INF_PROCESS.h"


#include "Identify.h"
#include "Motor.h"
#include "Servo.h"


#include "Speed.h"



#define  uchar   unsigned  char
#define  schar   signed  char
 
#define  uint    unsigned  int
#define  sint    signed  int

#define RESET_WATCHDOG();   _FEED_COP();__RESET_WATCHDOG()

#define IMG_START();    vsync = 0    //����ͼ��ɼ��ж�


//ͼ������ṹ��
typedef struct Coordinate
{
  	sint x;			  //������(0--79)
}X_Y;


/*******************************************************
 ��������Car_Init()
 ��������     
 ���ܣ�����ʼ��
*******************************************************/
void Car_Init(void);

/*******************************************************
 ��������WAIT_START()
 ��������     
 ���ܣ��ȴ������źţ�PT1���벶ץ�жϣ�
*******************************************************/
void WAIT_START(void);

/*******************************************************
 ��������CHECK_STOP()
 ��������     
 ���ܣ�����յ��źţ�PT1���벶ץ�жϣ�
*******************************************************/
void CHECK_STOP(void);


/*******************************************************
 ��������Get_Speed(void)
 ��������     
 ���أ���ǰ�ٶ�����
 ���ܣ���ȡ��ǰ�ٶ�����
*******************************************************/
uint Get_Speed(void);

/*******************************************************
 ��������Ignore(void)
 ��������     
 ���أ���
 ���ܣ��ȴ�ͼ���ȶ�
*******************************************************/
void Ignore(void);



#endif