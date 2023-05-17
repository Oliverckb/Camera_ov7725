#include "Identify.h"



extern uchar IMG[ROW][COLUMN];     //图像采集存放

extern X_Y SD_MID[ROW];    //赛道中心线在图像中的坐标
extern X_Y L[ROW];         //左边界在图像中的坐标
extern X_Y R[ROW];         //右边界在图像中的坐标

/****************1.2.3.4.5分区中值距中心的偏差******************/
extern sint Se1_diff,Se2_diff,Se3_diff,Se4_diff,Se5_diff;

extern uchar lb,rb;     //用于判断直角前的黑块


/*********赛道特征标志***********/
extern uchar ZhiDao_Flag;    //直道标志    1：直道 
extern uchar Left_Flag;     //左弯标志位   1：左弯
extern uchar Right_Flag;    //右弯标志位   1：右弯

//入直角直角黑块标志首次遇见置1，左右直角标志，左右直角回归标志
extern uchar ZhiJiao_Flag,L_Z_Flag,R_Z_Flag,L_HuiGui,R_HuiGui;
 
extern uchar Cross_Flag;    //十字标志     1：十字


//五点中位值滤波后取中位值
static sint MidFilter5(uchar start,uchar end)
{
	uchar i,j;
	sint p[5],t;
	p[0]=SD_MID[start].x;	
	p[1]=SD_MID[start+1].x;	
	p[2]=SD_MID[start+2].x;
	p[3]=SD_MID[start+3].x;
	p[4]=SD_MID[end].x;
	for(i=0;i<4;i++)
	{
		for(j=i+1;j<=4;j++)
		{
			if(p[i]>p[j]) { t=p[i]; p[i]=p[j]; p[j]=t; }
		}
	}
	return p[2];
}


//计算1.2.3.4.5分区的各自偏差
static void Diff(void)
{
	Se1_diff=MidFilter5(0,4)-40;
	Se2_diff=MidFilter5(5,9)-40;
    Se3_diff=MidFilter5(10,14)-40;
	Se4_diff=MidFilter5(15,19)-40;
  	Se5_diff=MidFilter5(20,24)-40;
  
}

/*************************************************
函数名: ZhiDao_Identify()
描述: 赛道类型的识别
输入: 无
输出: 无       **（使用全局变量置位赛道类型标志）
*************************************************/
static void ZhiDao_Identify(void)
{
	if( (Se4_diff+Se5_diff)>=-25 && (Se4_diff+Se5_diff)<=25)
	{
		ZhiDao_Flag=1;
	}
	else
	{
		ZhiDao_Flag=0;
	}
}

/*************************************************
函数名: Left_Identify()
描述: 赛道类型的识别
输入: 无
输出: 右弯识别
*************************************************/
static void Left_Identify(void)
{
    if( (Se4_diff+Se5_diff)>25 )
	{
		Left_Flag=1;
	}
	else
	{
		Left_Flag=0;
	}
  
}

/*************************************************
函数名: Right_Identify()
描述: 赛道类型的识别
输入: 无
输出: 右弯识别
*************************************************/
static void Right_Identify(void)
{
    if( (Se4_diff+Se5_diff)<-25 )
	{
		Right_Flag=1;
	}
	else
	{
		Right_Flag=0;
	}
  
}

/*************************************************
函数名: ZhiJiao_Identify()
描述: 赛道类型的识别
输入: 无
输出: 直角黑块识别，以及左右直角的识别
*************************************************/
static void ZhiJiao_Identify(void)
{
	uchar i,j;
	uchar temp=0;
	if( (ZhiJiao_Flag==0|| ZhiJiao_Flag==2) && ( (Se4_diff+Se5_diff)>=-30 && (Se4_diff+Se5_diff)<=30 ) )  //初次进时，并且最远区偏差不是很大
	{
		lb=0;rb=0;
		for(j=50;j>40;j--){if(IMG[1][j]==BLACK){lb++;}}     //统计中线左边的第1行10列的白点数
		for(j=50;j>40;j--){if(IMG[2][j]==BLACK){lb++;}}     //统计中线左边的第2行10列的白点数
		for(j=50;j>40;j--){if(IMG[3][j]==BLACK){lb++;}}     //统计中线左边的第3行10列的白点数
		for(j=50;j>40;j--){if(IMG[4][j]==BLACK){lb++;}}     //统计中线左边的第4行10列的白点数
		for(j=50;j>40;j--){if(IMG[5][j]==BLACK){lb++;}}     //统计中线左边的第5行10列的白点数
		for(j=50;j>40;j--){if(IMG[6][j]==BLACK){lb++;}}     //统计中线左边的第5行10列的白点数
		for(j=50;j>40;j--){if(IMG[7][j]==BLACK){lb++;}}     //统计中线左边的第7行10列的白点数
				
		for(j=40;j>30;j--){if(IMG[1][j]==BLACK){rb++;}}   //统计中线右边的第1行10列的白点数
		for(j=40;j>30;j--){if(IMG[2][j]==BLACK){rb++;}}   //统计中线右边的第2行10列的白点数
		for(j=40;j>30;j--){if(IMG[3][j]==BLACK){rb++;}}   //统计中线右边的第3行10列的白点数
		for(j=40;j>30;j--){if(IMG[4][j]==BLACK){rb++;}}   //统计中线右边的第4行10列的白点数
		for(j=40;j>30;j--){if(IMG[5][j]==BLACK){rb++;}}   //统计中线右边的第5行10列的白点数
		for(j=40;j>30;j--){if(IMG[6][j]==BLACK){rb++;}}   //统计中线右边的第6行10列的白点数
		for(j=40;j>30;j--){if(IMG[7][j]==BLACK){rb++;}}   //统计中线右边的第7行10列的白点数
	
		if( (lb>=35) && (rb>=35) && (ZhiJiao_Flag==0) )   //左右两边黑点数都大于35则为直角黑块
		{
			ZhiJiao_Flag=1; 	
		}
		if((lb>=35) && (rb>=35) && ZhiJiao_Flag==2)
		{
			ZhiJiao_Flag=3;
		}
	}
	
	/**/
	if(ZhiJiao_Flag==1)
	{
		ZhiDao_Flag=0; Left_Flag=0; Right_Flag=0; //清直道，弯道的标志位，再特殊处理直角
		
		lb=0;rb=0;    //复用，用于判断左右直角
		for(i=24;i>=20;i--)     //远区20--24检测左右直角
		{
			for(j=78;j>=76;j--)    //检测左上角的白点数
			{
				if(IMG[i][j]==WHITE)
				{
					lb++;
				}
			}
			for(j=1;j<=3;j++)     //检测右上角的白点数
			{
				if(IMG[i][j]==WHITE)
				{
					rb++;
				}
			}	
		}
		/**/
		//左边白点数大于等于10，右边白点小于5.则为左拐直角弯
		if(lb>=10 && rb<5)  
		{
			L_Z_Flag=1;	
		}
		//右边白点数大于等于10，左边白点小于5.则为右拐直角弯
		if(rb>=10 && lb<5)
		{
			R_Z_Flag=1; 	
		}		
	}

	
	if(ZhiJiao_Flag==3)
	{
		for(i=7;i>=1;i--)
		{
			for(j=49;j>=30;j--)
			{
				if(IMG[i][j]==WHITE)
				{
					temp++;
				}
			}
		}
		
		if(temp>=100)
		{
			ZhiJiao_Flag=0;
			L_Z_Flag=0;
			R_Z_Flag=0;
			L_HuiGui=0;
			R_HuiGui=0;
		}
		
	}
}

/*************************************************
函数名: Cross_Identify()
描述: 赛道类型的识别
输入: 无
输出: 无       **（使用全局变量置位赛道类型标志）
************************************************
static void Cross_Identify(void)
{
    
  
}*/
/*************************************************
函数名: Identify()
描述: 赛道类型的识别
输入: 无
输出: 无       **（使用全局变量置位赛道类型标志）
*************************************************/
void Identify(void)
{
	Diff();     //计算1.2.3.4.5分区中值距中心的偏差,后续使用
	ZhiDao_Identify();   //判断直道
	Left_Identify();     //判断左弯
	Right_Identify();    //判断右弯
//	ZhiJiao_Identify();  //判断直角黑块 以及左右直角
	//Cross_Identify();    //判断十字
}


