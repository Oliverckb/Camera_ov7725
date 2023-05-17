#include "COMMON.h"
#include "Users.h"
 
uchar StartStop;      //���ܸ��յ��ź�

uint  Current_Speed=0;    //С����ǰ�ٶ�
uint  Distance=0;         //С���н����� ����Ҫ����ֱ���䣬�����ڿ��ͳ�Ƶ�һ��������������

sint  Last_IMG_Diff=0;    //�ϴ�ͼ�����ĵ�ƫ��Ե���������Ϊͼ�����ģ��������ж��Ƿ�б��ʮ���䣬�������У�       

uchar IMG[ROW][COLUMN];     //ͼ��ɼ����
uchar vsync = 0;	 //��ͬ���źű�־��Ϊ1ʱ����ʼ��Ϊ2������

/*******���ұ߽��Լ���������*******/
X_Y SD_MID[ROW];    //������������ͼ���е�����
X_Y L[ROW];         //��߽���ͼ���е�����
X_Y R[ROW];         //�ұ߽���ͼ���е�����


/****************1.2.3.4.5������ֵ�����ĵ�ƫ��******************/
sint Se1_diff=0,Se2_diff=0,Se3_diff=0,Se4_diff=0,Se5_diff=0;


uchar lb=0,rb=0;     //�����ж�ֱ��ǰ�ĺڿ�


/*********����������־***********/
uchar ZhiDao_Flag=0;   //ֱ����־   1��ֱ��     
uchar Left_Flag=0;     //�����־   1������
uchar Right_Flag=0;    //�����־   1������
uchar Cross_Flag=0;    //ʮ�ֱ�־   1��ʮ��

 //��ֱ��ֱ�Ǻڿ��־�״�������1������ֱ�Ǳ�־������ֱ�ǻع��־
uchar ZhiJiao_Flag=0,L_Z_Flag=0,R_Z_Flag=0,L_HuiGui=0,R_HuiGui=0; 
uint speed=0;   //��������ٶ�        
void main(void) 
{
    Car_Init();            //��ʼ��С��
    EnableInterrupts;      //���ж� 
    Ignore();              //�ȴ�ͼ���ȶ�
    for(;;) 
    {   
        while(vsync<2);     //�ȴ�ͼ�����FIFO���
        GET_IMG();          //�ɼ��·�80X25��ͼ��
		IMG_START();        //ͼ��ɼ�����(ʵʱ����FIFO�е�ͼ��)
        IMG_PROCESS();      //ͼ����
	    SEND_IMG();         //����ͼ��
	
	
	
    }  
}


#pragma CODE_SEG __NEAR_SEG NON_BANKED 
void interrupt 8  IC0_ISR()   //���ж�,PT0�½��ش�������ͬ��)
{
    vsync++;
    if( vsync == 1 )
    {  
        WRITE_FIFO();     //дFIFO 
    }
    if(vsync == 2 )
    {
        DIS_WRITE_FIFO(); //��ֹдFIFO 	
    }
    
    
    TFLG1_C0F=1;  //�����־λ
                   
}


