#include "Servo.h"



extern uchar IMG[ROW][COLUMN];     //ͼ��ɼ����

extern X_Y SD_MID[ROW];    //������������ͼ���е�����
extern X_Y L[ROW];         //��߽���ͼ���е�����
extern X_Y R[ROW];         //�ұ߽���ͼ���е�����

/****************1.2.3.4.5������ֵ�����ĵ�ƫ��******************/
extern sint Se1_diff,Se2_diff,Se3_diff,Se4_diff,Se5_diff;


/*********����������־***********/
extern uchar ZhiDao_Flag;   //ֱ����־      1��ֱ�� 
extern uchar Left_Flag;     //�����־λ    1������
extern uchar Right_Flag;    //�����־λ    1������

//��ֱ��ֱ�Ǻڿ��־�״�������1������ֱ�Ǳ�־������ֱ�ǻع��־
extern uchar ZhiJiao_Flag,L_Z_Flag,R_Z_Flag,L_HuiGui,R_HuiGui;
 

extern uchar Cross_Flag;    //ʮ�ֱ�־      1��ʮ��

/*******************************************************
 ��������Servo_Adjust
 ������duty  PWM23����ռ�ձ�
 ���ܣ������ұߵ�����ٶ�
*******************************************************/
void Servo_Adjust(uint duty)
{
    PWMDTY23=duty;  
}

/*******************************************************
 ��������ZhiDao_Servo_Control
 ��������
 ���ܣ�ֱ��������Ʋ���
*******************************************************/
static void ZhiDao_Servo_Control(void)
{
	if(ZhiDao_Flag==1)             //ֱ��΢�����
	{
		if(Se1_diff<0)    //������ƫ����Ҵ�΢��
		{
			Servo_Adjust(-11*Se1_diff+940);		
		}
		if(Se1_diff>=0)   //������ƫ������΢��
		{
			Servo_Adjust(-9*Se1_diff+910);	
		}
  	}

}

/*******************************************************
 ��������WanDao_Servo_Control
 ��������
 ���ܣ����������Ʋ���
*******************************************************/
static void WanDao_Servo_Control(void)
{
	if(Left_Flag==1 || Right_Flag==1 )      
	{
		if(	(Se1_diff+Se2_diff) < 0 )   //���������       
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
    	if(	(Se1_diff+Se2_diff) >=0 )   //���������
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
 ��������ZhiJiao_Servo_Control()
 ��������
 ���ܣ�����ֱ��ǰ�ζ�����Ʋ���
*******************************************************/
static void ZhiJiao_Servo_Control(void)
{
	uchar i,j;
	uchar B=0;
	uchar l=0,r=0;
	uchar temp=0;
	if(L_Z_Flag==1 || R_Z_Flag==1)
	{
		for(j=45;j>=36;j--)    //����Ƿ񵽴����������
		{
			for(i=7;i<=8;i++)
			{
				if(IMG[i][j]==WHITE && IMG[i+1][j]==WHITE && IMG[i+2][j]==BLACK)
				{
					B++;
				}
			}
		}
		
		if(B>=10)       //���˴������������ 
		{
			if(L_Z_Flag==1)  //��������������Ϊ��ֱ������λ��ع�Ϊ1
			{
				L_HuiGui=1;
			}
			if(R_Z_Flag==1)  //��������������Ϊ��ֱ������λ�һع�Ϊ1
			{
				R_HuiGui=1;
			}
		}
		else     //δ���������������
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
			if(Se1_diff<0 && temp<=10)    //������ƫ����Ҵ�΢��
			{
				Servo_Adjust(-11*Se1_diff+940);		
			}
		    if(Se1_diff>=0 && temp<=10)   //������ƫ������΢��
			{
				Servo_Adjust(-9*Se1_diff+910);	
			}
			
			if(temp>10)
			{
				Servo_Adjust(Serve_Middle);
			}
		
		}
		
		
		if(L_HuiGui==1)    //�����ع�Ϊ1���������
		{
			Servo_Adjust(Serve_Left_Max);
			L_Z_Flag=0;R_Z_Flag=0;        //������ֱ�Ǳ�־λ
			for(i=10;i>=6;i--)
			{
				for(j=79;j>=3;j--)    //����߽�
				{
					if(IMG[i][j]==BLACK&&IMG[i][j-1]==BLACK && IMG[i][j-2]==WHITE&&IMG[i][j-3]==WHITE)
					{
						l++;break;      
					}
				}
			}
			
			if(l>=2)
			{
				Servo_Adjust(Serve_Middle);   //�������			
				L_HuiGui=0;         //����ع��־λ
				ZhiJiao_Flag=2;     //��λֱ�Ǳ�־Ϊ2
			}
			
		}
		if(R_HuiGui==1)   //����һع�Ϊ1�����Ҵ���
		{
			Servo_Adjust(Serve_Right_Max);
			L_Z_Flag=0;R_Z_Flag=0;        //������ֱ�Ǳ�־λ
			for(i=10;i>=6;i--)
			{
				for(j=0;j<=76;j++)         //���ұ߽�
				{
					if(IMG[i][j]==BLACK&&IMG[i][j+1]==BLACK && IMG[i][j+2]==WHITE&&IMG[i][j+3]==WHITE)
					{
						r++;break;      
					}
				}
			}
			
			if(r>=2)
			{
				Servo_Adjust(Serve_Middle);   //�������
				R_HuiGui=0;         //���һع��־λ
				ZhiJiao_Flag=2;     //��λֱ�Ǳ�־Ϊ2
			}
		}
		
		
		
		
	}

}
/*******************************************************
 ��������Cross_Servo_Control()
 ��������
 ���ܣ�ʮ�ֶ�����Ʋ���
******************************************************
static void Cross_Servo_Control(void)
{
	

}*/

/*************************************************
������: Servo_Control()
����: �������
����: ��
���: ��
*************************************************/
void Servo_Control(void)
{
	ZhiDao_Servo_Control();   //ֱ�����ƣ����������
	WanDao_Servo_Control();   //������ƣ����������
	//ZhiJiao_Servo_Control();  //��ֱ��ǰ�ο��ƣ����������
	//Cross_Servo_Control();  //ʮ�ֿ��ƣ����������

}