#include "INF_PROCESS.h"

extern uchar IMG[ROW][COLUMN];     //图像采集存放

extern X_Y SD_MID[ROW];    //赛道中心线在图像中的坐标
extern X_Y L[ROW];         //左边界在图像中的坐标
extern X_Y R[ROW];         //右边界在图像中的坐标

/*******************************************************
 函数名：MedFilter(schar last_dot,schar now_dot,schar next_dot)
 参数：相邻两点与当前点
 功能：中心线滤波平滑处理窗口大小为1x3
*******************************************************/
static sint MedFilter(sint last_dot,sint now_dot,sint next_dot)
{
	sint a,b,c,x;
	a=last_dot;b=now_dot;c=next_dot;
	if(a>b) { x=b;b=a;a=x;}
	if(b>c) { x=c;c=b;b=x;}
	if(a>b) { x=b;b=a;a=x;}
	return b;
}


/*******************************************************
 函数名：Black_Extract(void)
 参数：无
 功能：图像左右赛道以及中心线的提取，以及其边界中心线滤波平滑处理
       0--4行边界提取，5--24行跟踪边沿找边界
*******************************************************/
void Black_Extract(void)
{
    schar i,j;
    uchar left_lost=0,rigth_lost=0; //每一行的左右边界丢线标志  1:不丢线  0：丢线
    for(i=0;i<=24;i++)    //寻找左右边界以及中线
    {
		left_lost=0,rigth_lost=0;  //清标志位
        for(j=79;j>=3;j--)   //寻找左边界
        {
            if(IMG[i][j]==BLACK&&IMG[i][j-1]==BLACK && IMG[i][j-2]==WHITE&&IMG[i][j-3]==WHITE)
            {
                L[i].x = j-1;left_lost=0;break;      
            }
            else
            {
                left_lost=1; //左边界丢线
            }
        }
        for(j=0;j<=76;j++)    //寻找右边界
        {
            if(IMG[i][j]==BLACK&&IMG[i][j+1]==BLACK && IMG[i][j+2]==WHITE&&IMG[i][j+3]==WHITE)
            {
                R[i].x = j+1; rigth_lost=0;break;   
            }
            else
            {
                rigth_lost=1; //左边界丢线
            }
        }
        
        if(left_lost==1&&rigth_lost==0)    //只有左丢线
        {
			if(i==0)
			{               
               L[0].x=  R[0].x + 65 ;//右边界预测左边界
			}
			else if(i==1)
			{                         
               L[1].x=R[1].x + (L[0].x- R[0].x-1);//右边界预测左边界
			}
			else
			{                                     
               L[i].x=R[i].x + (L[i-1].x- R[i-1].x-1); //右边界预测左边界
			}
        }
        
        if(left_lost==0&&rigth_lost==1)    //只有右丢线
        {
			if(i==0)
			{           
               R[0].x=L[0].x - 65;//左边界预测右边界
			}
			else if(i==1)
			{                  
               R[1].x=L[1].x -(L[0].x- R[0].x-1);//左边界预测右边界
			}
			else
			{                                             
               R[i].x= L[i].x - (L[i-1].x- R[i-1].x-1);//左边界预测右边界
			}
        }
        
        if(left_lost==1&&rigth_lost==1)    //左右都丢线
        {
			if(i==0)
      		{
      			R[0].x=10;   L[0].x=70;
      		}
      		else if(i==1)
      		{
      			R[1].x=11;   L[1].x=69;
      		}
			else
			{    
				L[i].x=L[i-1].x + (L[i-1].x-L[i-2].x);  // 左边界变化趋势自预测
				R[i].x=R[i-1].x + (R[i-1].x-R[i-2].x);  // 右边界变化趋势自预测   	
			}
		}
    }
	
    for(i=0;i<=24;i++)//求中心线
    {
	    SD_MID[i].x=(sint)((L[i].x+R[i].x)/2);
    }
	
	for(i=0;i<=23;i++) //平滑中心线
	{
		SD_MID[i].x=MedFilter(SD_MID[i-1].x,SD_MID[i].x,SD_MID[i+1].x);
	}
		
}






