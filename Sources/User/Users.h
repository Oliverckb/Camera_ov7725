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

#define IMG_START();    vsync = 0    //开启图像采集中断


//图像坐标结构体
typedef struct Coordinate
{
  	sint x;			  //横坐标(0--79)
}X_Y;


/*******************************************************
 函数名：Car_Init()
 参数：无     
 功能：车初始化
*******************************************************/
void Car_Init(void);

/*******************************************************
 函数名：WAIT_START()
 参数：无     
 功能：等待起跑信号（PT1输入捕抓中断）
*******************************************************/
void WAIT_START(void);

/*******************************************************
 函数名：CHECK_STOP()
 参数：无     
 功能：检测终点信号（PT1输入捕抓中断）
*******************************************************/
void CHECK_STOP(void);


/*******************************************************
 函数名：Get_Speed(void)
 参数：无     
 返回：当前速度脉冲
 功能：获取当前速度脉冲
*******************************************************/
uint Get_Speed(void);

/*******************************************************
 函数名：Ignore(void)
 参数：无     
 返回：无
 功能：等待图像稳定
*******************************************************/
void Ignore(void);



#endif