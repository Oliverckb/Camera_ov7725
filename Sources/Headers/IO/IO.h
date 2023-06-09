
//PORTA读取摄像头数据

// PORTB读取左边编码器脉冲
//PORTAD读取右边编码器脉冲


#ifndef IO_H
#define IO_H


#include "COMMON.h"


/*******************************************************
 函数名Init_PORTA()
 参数：config   0--输入
                1--输出
       
 功能：初始化PORTA
*******************************************************/
void Init_PORTA(uchar);
/*******************************************************
 函数名：Set_PORTA()
 参数：config   0--PORTA=00000000
                1--PORTA=11111111
       
 功能：设置PORTA输出高低电平
*******************************************************/
void Set_PORTA(uchar);
/*******************************************************
 函数名：Read_PORTA()
 参数：无
 返回值:PORTA的数据     
 功能：读取PORTA电平
*******************************************************/
uchar Read_PORTA(void);



/*******************************************************
 函数名Init_PORTB()
 参数：config   0--输入
                1--输出
       
 功能：初始化PORTA
*******************************************************/
void Init_PORTB(uchar);
/*******************************************************
 函数名：Set_PORTB()
 参数：config   0--PORTB=00000000
                1--PORTB=11111111
       
 功能：设置PORTB输出高低电平
*******************************************************/
void Set_PORTB(uchar);
/*******************************************************
 函数名：Read_PORTB()
 参数：无
 返回值:PORTB的数据     
 功能：读取PORTB电平
*******************************************************/
uchar Read_PORTB(void);


/*******************************************************
 函数名Init_PORTAD()
 参数：config   0--输入
                1--输出
       
 功能：初始化PORTAD
*******************************************************/
void Init_PORTAD(uchar);
/*******************************************************
 函数名：Set_PORTAD()
 参数：config   0--PORTB=00000000
                1--PORTB=11111111
       
 功能：设置PORTAD输出高低电平
*******************************************************/
void Set_PORTAD(uchar);
/*******************************************************
 函数名：Read_PORTAD()
 参数：无
 返回值:PORTAD的数据     
 功能：读取PORTAD电平
*******************************************************/
uchar Read_PORTAD(void);


/*******************************************************
 函数名Init_PTM()
 参数：config   0--输入
                1--输出
       
 功能：初始化PTM
*******************************************************/
void Init_PTM(uchar);
/*******************************************************
 函数名：Set_PTM()
 参数：config   0--PTM=00000000
                1--PTM=11111111
       
 功能：设置PTM输出高低电平
*******************************************************/
void Set_PTM(uchar);
/*******************************************************
 函数名：Read_PORTM()
 参数：无
 返回值:PORTM的数据     
 功能：读取PORTA电平
*******************************************************/
uchar Read_PTM(void);








#endif