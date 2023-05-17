#ifndef bsp_fifo_H
#define bsp_fifo_H


#include "COMMON.h"
#include "Users.h"

//OE读使能控制引脚   PE4  
#define FIFO_CS_H()     PORTE_PE4=1	  /*拉高禁止FIFO输出使能*/
#define FIFO_CS_L()     PORTE_PE4=0	  /*拉低使FIFO输出使能*/
//读时钟RCLK控制引脚 PE5
#define FIFO_RCLK_H()   PORTE_PE5=1	  
#define FIFO_RCLK_L()   PORTE_PE5=0	  /*FIFO输出数据时钟*/
//读复位RRST控制引脚 PE6
#define FIFO_RRST_H()   PORTE_PE6=1	  /*拉高允许FIFO读(数据从FIFO输出)指针运动 */
#define FIFO_RRST_L()   PORTE_PE6=0	  /*拉低使FIFO读(数据从FIFO输出)指针复位 */


//写使能WEN控制引脚 PE2
#define FIFO_WE_H()     PORTE_PE2=1	  /*拉高使FIFO写允许*/
#define FIFO_WE_L()     PORTE_PE2=0
//写复位WRST控制引脚PE3
#define FIFO_WRST_H()   PORTE_PE3=1	  /*拉高允许FIFO写(数据from摄像头)指针运动 */
#define FIFO_WRST_L()   PORTE_PE3=0	  /*拉低使FIFO写(数据from摄像头)指针复位*/




//FIFO为读准备
#define FIFO_PREPARE()      FIFO_RRST_L();\
	                          FIFO_RCLK_L();\
	                          FIFO_RCLK_H();\
	                          FIFO_RCLK_L();\
	                          FIFO_RCLK_H();\
	                          FIFO_RRST_H();\
	                          FIFO_RCLK_L();\
	                          FIFO_RCLK_H();\
	                          FIFO_CS_L()  
	                          
 
 
 //写FIFO
 #define WRITE_FIFO()  FIFO_WRST_L();\
                       FIFO_WRST_H();\
                       FIFO_WE_H()                           

 //禁止写FIFO
 #define DIS_WRITE_FIFO();    FIFO_WE_L()    //拉低使FIFO写暂停



/************************************************
 * 函数名：FIFO_Init
 * 描述  ：FIFO初始化
 * 输入  ：无
 * 输出  ：无
 ************************************************/
void FIFO_Init(void);
/************************************************
 * 函数名：FIFO_READ
 * 描述  ：从FIFO中读出RGB565的16位像素
 * 输入  ：无
 * 输出  ：16位uint的像素值
************************************************/
uint FIFO_READ(void);




#endif