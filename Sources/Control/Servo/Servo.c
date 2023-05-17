#include "Servo.h"



extern uchar IMG[ROW][COLUMN];     //图像采集存放

extern X_Y SD_MID[ROW];    //赛道中心线在图像中的坐标
extern X_Y L[ROW];         //左边界在图像中的坐标
extern X_Y R[ROW];         //右边界在图像中的坐标

/****************1.2.3.4.5分区中值距中心的偏差******************/
extern sint Se1_diff,Se2_diff,Se3_diff,Se4_diff,Se5_diff;


/*********赛道特征标志***********/
extern uchar ZhiDao_Flag;   //直道标志      1：直道 
extern uchar Left_Flag;     //左弯标志位    1：左弯
extern uchar Right_Flag;    //右弯标志位    1：右弯

//入直角直角黑块标志首次遇见置1，左右直角标志，左右直角回归标志
extern uchar ZhiJiao_Flag,L_Z_Flag,R_Z_Flag,L_HuiGui,R_HuiGui;
 

extern uchar Cross_Flag;    //十字标志      1：十字

/*******************************************************
 函数名：Servo_Adjust
 参数：duty  PWM23级联占空比
 功能：调节右边电机的速度
*******************************************************/
void Servo_Adjust(uint duty)
{
    PWMDTY23=duty;  
}

/*******************************************************
 函数名：ZhiDao_Servo_Control
 参数：无
 功能：直道舵机控制策略
*******************************************************/
static void ZhiDao_Servo_Control(void)
{
	if(ZhiDao_Flag==1)             //直道微调舵机
	{
		if(Se1_diff<0)    //车身左偏舵机右打微调
		{
			Servo_Adjust(-11*Se1_diff+940);		
		}
		if(Se1_diff>=0)   //车身右偏舵机左打微调
		{
			Servo_Adjust(-9*Se1_diff+910);	
		}
  	}

}

/*******************************************************
 函数名：WanDao_Servo_Control
 参数：无
 功能：弯道舵机控制策略
*******************************************************/
static void WanDao_Servo_Control(void)
{
	if(Left_Flag==1 || Right_Flag==1 )      
	{
		if(	(Se1_diff+Se2_diff) < 0 )   //右弯道控制       
    	{
    		if( (-3*(Se1_diff+Se2_diff)+963 ) >1130 )
    		{
    			Servo_Adjust(Serve_Right_Max);
    		}
    		else
    		{
    			Servo_Adjust(-3*(Se1_diff+Se2_diff)+1110);	 //990
    		}	
    	}
    	if(	(Se1_diff+Se2_diff) >=0 )   //左弯道控制
    	{
    		if( (-3*(Se1_diff+Se2_diff)+867 ) <700 )
    		{
    			Servo_Adjust(Serve_Left_Max);
    		}
    		else
    		{
    			Servo_Adjust(-3*(Se1_diff+Se2_diff)+847);  //867
    		}	
    	}
	}
}


/*******************************************************
 函数名：ZhiJiao_Servo_Control()
 参数：无
 功能：进入直角前段舵机控制策略
*******************************************************/
static void ZhiJiao_Servo_Control(void)
{
	uchar i,j;
	uchar B=0;
	uchar l=0,r=0;
	uchar temp=0;
	if(L_Z_Flag==1 || R_Z_Flag==1)
	{
		for(j=45;j>=36;j--)    //检查是否到打死舵机区域
		{
			for(i=7;i<=8;i++)
			{
				if(IMG[i][j]==WHITE && IMG[i+1][j]==WHITE && IMG[i+2][j]==BLACK)
				{
					B++;
				}
			}
		}
		
		if(B>=10)       //到了打死舵机的区域 
		{
			if(L_Z_Flag==1)  //到打死的区域且为左直角则置位左回归为1
			{
				L_HuiGui=1;
			}
			if(R_Z_Flag==1)  //到打死的区域且为右直角则置位右回归为1
			{
				R_HuiGui=1;
			}
		}
		else     //未到打死舵机的区域
		{
			for(i=0;i<=5;i++)
			{
				for(j=49;i>=30;j--)
				{
					if(IMG[i][j]==BLACK)
					{
						temp++;
					}
				}
			}
			if(Se1_diff<0 && temp<=10)    //车身左偏舵机右打微调
			{
				Servo_Adjust(-11*Se1_diff+940);		
			}
		    if(Se1_diff>=0 && temp<=10)   //车身右偏舵机左打微调
			{
				Servo_Adjust(-9*Se1_diff+910);	
			}
			
			if(temp>10)
			{
				Servo_Adjust(Serve_Middle);
			}
		
		}
		
		
		if(L_HuiGui==1)    //如果左回归为1，则左打死
		{
			Servo_Adjust(Serve_Left_Max);
			L_Z_Flag=0;R_Z_Flag=0;        //清左右直角标志位
			for(i=10;i>=6;i--)
			{
				for(j=79;j>=3;j--)    //找左边界
				{
					if(IMG[i][j]==BLACK&&IMG[i][j-1]==BLACK && IMG[i][j-2]==WHITE&&IMG[i][j-3]==WHITE)
					{
						l++;break;      
					}
				}
			}
			
			if(l>=2)
			{
				Servo_Adjust(Serve_Middle);   //舵机回正			
				L_HuiGui=0;         //清左回归标志位
				ZhiJiao_Flag=2;     //置位直角标志为2
			}
			
		}
		if(R_HuiGui==1)   //如果右回归为1，则右打死
		{
			Servo_Adjust(Serve_Right_Max);
			L_Z_Flag=0;R_Z_Flag=0;        //清左右直角标志位
			for(i=10;i>=6;i--)
			{
				for(j=0;j<=76;j++)         //找右边界
				{
					if(IMG[i][j]==BLACK&&IMG[i][j+1]==BLACK && IMG[i][j+2]==WHITE&&IMG[i][j+3]==WHITE)
					{
						r++;break;      
					}
				}
			}
			
			if(r>=2)
			{
				Servo_Adjust(Serve_Middle);   //舵机回正
				R_HuiGui=0;         //清右回归标志位
				ZhiJiao_Flag=2;     //置位直角标志为2
			}
		}
		
		
		
		
	}

}
/*******************************************************
 函数名：Cross_Servo_Control()
 参数：无
 功能：十字舵机控制策略
******************************************************
static void Cross_Servo_Control(void)
{
	

}*/

/*************************************************
函数名: Servo_Control()
描述: 舵机控制
输入: 无
输出: 无
*************************************************/
void Servo_Control(void)
{
	ZhiDao_Servo_Control();   //直道控制（详见函数）
	WanDao_Servo_Control();   //弯道控制（详见函数）
	//ZhiJiao_Servo_Control();  //入直角前段控制（详见函数）
	//Cross_Servo_Control();  //十字控制（详见函数）

}