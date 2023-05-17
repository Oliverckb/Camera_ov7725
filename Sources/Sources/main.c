#include "COMMON.h"
#include "Users.h"
 
uchar StartStop;      //起跑跟终点信号

uint  Current_Speed=0;    //小车当前速度
uint  Distance=0;         //小车行进距离 （主要用于直角弯，遇见黑块后统计到一定距离打死舵机）

sint  Last_IMG_Diff=0;    //上次图像中心的偏差（以第三分区作为图像中心）（用于判断是否斜入十字弯，避免误判）       

uchar IMG[ROW][COLUMN];     //图像采集存放
uchar vsync = 0;	 //场同步信号标志当为1时场开始，为2结束。

/*******左右边界以及中线坐标*******/
X_Y SD_MID[ROW];    //赛道中心线在图像中的坐标
X_Y L[ROW];         //左边界在图像中的坐标
X_Y R[ROW];         //右边界在图像中的坐标


/****************1.2.3.4.5分区中值距中心的偏差******************/
sint Se1_diff=0,Se2_diff=0,Se3_diff=0,Se4_diff=0,Se5_diff=0;


uchar lb=0,rb=0;     //用于判断直角前的黑块


/*********赛道特征标志***********/
uchar ZhiDao_Flag=0;   //直道标志   1：直道     
uchar Left_Flag=0;     //左弯标志   1：左弯
uchar Right_Flag=0;    //右弯标志   1：右弯
uchar Cross_Flag=0;    //十字标志   1：十字

 //入直角直角黑块标志首次遇见置1，左右直角标志，左右直角回归标志
uchar ZhiJiao_Flag=0,L_Z_Flag=0,R_Z_Flag=0,L_HuiGui=0,R_HuiGui=0; 
uint speed=0;   //给电机的速度        
void main(void) 
{
    Car_Init();            //初始化小车
    EnableInterrupts;      //开中断 
    Ignore();              //等待图像稳定
    for(;;) 
    {   
        while(vsync<2);     //等待图像存入FIFO完毕
        GET_IMG();          //采集衣服80X25的图像
		IMG_START();        //图像采集启动(实时更新FIFO中的图像)
        IMG_PROCESS();      //图像处理
	    SEND_IMG();         //发送图像
	
	
	
    }  
}


#pragma CODE_SEG __NEAR_SEG NON_BANKED 
void interrupt 8  IC0_ISR()   //场中断,PT0下降沿触发（场同步)
{
    vsync++;
    if( vsync == 1 )
    {  
        WRITE_FIFO();     //写FIFO 
    }
    if(vsync == 2 )
    {
        DIS_WRITE_FIFO(); //禁止写FIFO 	
    }
    
    
    TFLG1_C0F=1;  //清除标志位
                   
}


