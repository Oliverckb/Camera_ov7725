#include "Image.h"

extern uchar IMG[ROW][COLUMN];     //图像采集存放

extern X_Y SD_MID[ROW];    //赛道中心线在图像中的坐标
extern X_Y L[ROW];         //左边界在图像中的坐标
extern X_Y R[ROW];         //右边界在图像中的坐标

//宏定义采集一个像素点的宏函数
#define ONE_DOT()  RGB565=FIFO_READ();\
                   IMG[IMR][IMC++]=((RGB565&RGB565_RED)>>11) + ((RGB565&RGB565_GREEN)>>5) + (RGB565&RGB565_BLUE);\
                   J1();J1();J1()
//采集一行80个数据                   
#define CAIJI_ONE_LINE();  for(i=5;i>0;i--){ONE_DOT();ONE_DOT();ONE_DOT();ONE_DOT();ONE_DOT();ONE_DOT();ONE_DOT();ONE_DOT();\
                                            ONE_DOT();ONE_DOT();ONE_DOT();ONE_DOT();ONE_DOT();ONE_DOT();ONE_DOT();ONE_DOT();\
                                            if(IMC==80) {IMC=0;IMR++;}}                 
 
//跳过一行数据                   
#define ONE_LINE();   for(i=5;i>0;i--){J1();J1();J1();J1();J1();J1();J1();J1();J1();J1();J1();J1();J1();J1();J1();J1();\
                                       J1();J1();J1();J1();J1();J1();J1();J1();J1();J1();J1();J1();J1();J1();J1();J1();\
                                       J1();J1();J1();J1();J1();J1();J1();J1();J1();J1();J1();J1();J1();J1();J1();J1();\
                                       J1();J1();J1();J1();J1();J1();J1();J1();J1();J1();J1();J1();J1();J1();J1();J1();\
                                       }
    
       
/*******************************************************
 函数名：GET_IMG()
 参数：无
 功能：获取一幅80X25的图像
 8 16 24 32 40 48 56 64 72 80 88 96 104 112 120 128 136 144 152 160 168 176 184 192 200
*******************************************************/
void GET_IMG(void)
{   
    uchar k,i,IMR=0,IMC=0;
    uint RGB565;
    FIFO_PREPARE(); //FIFO为读做准备
    ONE_LINE();ONE_LINE();ONE_LINE();ONE_LINE();ONE_LINE();  //跳过5行
    for(k=25;k>0;k--)
    {
       CAIJI_ONE_LINE();
       ONE_LINE();ONE_LINE();ONE_LINE();ONE_LINE();ONE_LINE();  //跳过5行    
    }   
}


/*******************************************************
 函数名：Binary_IMG()
 参数：无
 功能:将80X25的图像二值化
*******************************************************/
static void Binary_IMG(void)
{
   uchar i,j;
   for(i=0;i<=24;i++)
   {
       for(j=0;j<=79;j++)
       {
            if(IMG[i][j]>=FZ)
  	        {
  		         IMG[i][j]=WHITE;
          	}
          	else
          	{
  		         IMG[i][j]=BLACK;
          	}
       }
   }
}



/*******************************************************
 函数名:IMG_PROCESS()
 参数：无
 功能:将80X25的图像处理 
*******************************************************/
void IMG_PROCESS(void)
{
    Binary_IMG();
       
}

/*******************************************************
 函数名：SEND_IMG()
 参数：无
 功能:将80X25的图像发送给上位机
*******************************************************/
void SEND_IMG(void)
{
    uchar i,j;
    SCI0_Write(0xff);
    for(i=0;i<25;i++)
    {
        for(j=0;j<80;j++)
        {
             SCI0_Write(IMG[i][j]);
         }
     }
     SCI0_Write(0xff);
}

/*******************************************************
 函数名：SHOW_Black_Line(void)
 参数：无
 功能:将80X25的图像发送给上位机
*******************************************************/
void SHOW_Black_Line(void)
{
    uchar i;
    for(i=0;i<=24;i++)
    {
       // IMG[i][L[i].x]=240;
        //IMG[i][R[i].x]=240;
        IMG[i][SD_MID[i].x]=240;
    }
    SEND_IMG();
    
}







