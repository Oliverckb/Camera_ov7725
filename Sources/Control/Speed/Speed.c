 #include "Speed.h"
 
 /*********赛道特征标志***********/
extern uchar ZhiDao_Flag;   //直道标志      1：直道 
extern uchar Left_Flag;     //左弯标志位    1：左弯
extern uchar Right_Flag;    //右弯标志位    1：右弯

//入直角直角黑块标志首次遇见置1，左右直角标志，左右直角回归标志
extern uchar ZhiJiao_Flag,L_Z_Flag,R_Z_Flag,L_HuiGui,R_HuiGui;
extern uint speed;  //给电机的速度
/*************************************************
函数名: Init_Spped_M()
描述: 初始化测速模块
输入: 无
输出: 无
*************************************************/ 
void Init_Spped_M(void)
{
  Init_PORTAD(0);        //初始化PAD为输入，左电机测速
  Init_PORTB(0);         //初始化PB 口输入，右电机测速
  DDRE_DDRE7=1;          //PE7为清零信号，读取一次速度就给其高电平清零
  PORTE_PE7=0;   //初始化为低电平，计数状态
}
 
/*************************************************
函数名: Left_Curret_Spped()
描述: 获取左电机的左右速度
输入: 无
输出: 当前左电机的速度
*************************************************/
uchar Left_Curret_Spped(void) 
{
	return  PT1AD0;
}

/*************************************************
函数名: Left_Curret_Spped()
描述: 获取左电机的左右速度
输入: 无
输出: 当前左电机的速度
*************************************************/
uchar Right_Curret_Spped(void) 
{
	return  PORTB;
}

/*************************************************
函数名: Spped_Clear()
描述: 测速清零
输入: 无
输出: 无
*************************************************/
void  Spped_Clear(void)
{
	PORTE_PE7=1;
	_asm(nop);_asm(nop);	_asm(nop);_asm(nop);	
	PORTE_PE7=0;
	_asm(nop);_asm(nop);	_asm(nop);_asm(nop);
	

}

/*************************************************
函数名: Speed_Control()
描述: 测速清零
输入: 无
输出: 无
*************************************************/
void Speed_Control(void)
{
  if(ZhiJiao_Flag>0)
  {
    	Left_Motor_Forward (130);
      Right_Motor_Forward(130); 
  }
  else
  {
     	Left_Motor_Forward (speed);
      Right_Motor_Forward(speed);
  }
  
}






