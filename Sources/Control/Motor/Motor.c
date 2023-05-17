#include "Motor.h"

/*************************************************
函数名: Motor_Stop()
描述: 电机停止
输入: 无
输出: 无
*************************************************/
void Motor_Stop(void) 
{                     
    DDRS_DDRS2=1;
    DDRS_DDRS3=1;
    PTS_PTS2=0;
    PTS_PTS3=0;
    PWMDTY01=0; 
    PWMDTY45=0;  
}


/*************************************************
函数名: Left_Motor_Forward
描述: 左电机前进
输入: duty:PWM01占空比
输出: 无
*************************************************/
void Left_Motor_Forward(uint duty) 
{                     
    DDRS_DDRS2=1;
    PTS_PTS2=0;
    PWMDTY01=duty;  
}

/*************************************************
函数名: Right_Motor_Forward
描述: 右电机前进
输入: duty:PWM45占空比
输出: 无
*************************************************/
void Right_Motor_Forward(uint duty) 
{                     
    DDRS_DDRS3=1;
    PTS_PTS3=0;
    PWMDTY45=duty;  
}
/*************************************************
函数名: Left_Motor_Back
描述: 左电机后退
输入: duty:PWM01占空比
输出: 无
*************************************************/
void Left_Motor_Back(uint duty) 
{                     
  DDRS_DDRS2=1;
  PTS_PTS2=1;
  PWMDTY01=duty;
   
}
/*************************************************
函数名: Right_Motor_Back
描述: 右电机后退
输入: duty:PWM45占空比
输出: 无
*************************************************/
void Right_Motor_Back(uint duty) 
{                     
    DDRS_DDRS3=1;
    PTS_PTS3=1;
    PWMDTY45=duty;  
}


