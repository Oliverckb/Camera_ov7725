#ifndef Servo_H
#define Servo_H


#include "COMMON.h"
#include "Users.h"

#define Serve_Left_Max   650    //舵机左转最大值
#define Serve_Middle     920   //舵机正中
#define Serve_Right_Max  1200   //舵机左转最大值

/*******************************************************
 函数名：Servo_Adjust
 参数：duty  PWM23级联占空比
 功能：调节右边电机的速度
*******************************************************/
void Servo_Adjust(uint duty);

/*************************************************
函数名: Servo_Control()
描述: 舵机控制
输入: 无
输出: 无
*************************************************/
void Servo_Control(void);




#endif