#include "Identify.h"



extern uchar IMG[ROW][COLUMN];     //ͼ��ɼ����

extern X_Y SD_MID[ROW];    //������������ͼ���е�����
extern X_Y L[ROW];         //��߽���ͼ���е�����
extern X_Y R[ROW];         //�ұ߽���ͼ���е�����

/****************1.2.3.4.5������ֵ�����ĵ�ƫ��******************/
extern sint Se1_diff,Se2_diff,Se3_diff,Se4_diff,Se5_diff;

extern uchar lb,rb;     //�����ж�ֱ��ǰ�ĺڿ�


/*********����������־***********/
extern uchar ZhiDao_Flag;    //ֱ����־    1��ֱ�� 
extern uchar Left_Flag;     //�����־λ   1������
extern uchar Right_Flag;    //�����־λ   1������

//��ֱ��ֱ�Ǻڿ��־�״�������1������ֱ�Ǳ�־������ֱ�ǻع��־
extern uchar ZhiJiao_Flag,L_Z_Flag,R_Z_Flag,L_HuiGui,R_HuiGui;
 
extern uchar Cross_Flag;    //ʮ�ֱ�־     1��ʮ��


//�����λֵ�˲���ȡ��λֵ
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


//����1.2.3.4.5�����ĸ���ƫ��
static void Diff(void)
{
	Se1_diff=MidFilter5(0,4)-40;
	Se2_diff=MidFilter5(5,9)-40;
    Se3_diff=MidFilter5(10,14)-40;
	Se4_diff=MidFilter5(15,19)-40;
  	Se5_diff=MidFilter5(20,24)-40;
  
}

/*************************************************
������: ZhiDao_Identify()
����: �������͵�ʶ��
����: ��
���: ��       **��ʹ��ȫ�ֱ�����λ�������ͱ�־��
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
������: Left_Identify()
����: �������͵�ʶ��
����: ��
���: ����ʶ��
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
������: Right_Identify()
����: �������͵�ʶ��
����: ��
���: ����ʶ��
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
������: ZhiJiao_Identify()
����: �������͵�ʶ��
����: ��
���: ֱ�Ǻڿ�ʶ���Լ�����ֱ�ǵ�ʶ��
*************************************************/
static void ZhiJiao_Identify(void)
{
	uchar i,j;
	uchar temp=0;
	if( (ZhiJiao_Flag==0|| ZhiJiao_Flag==2) && ( (Se4_diff+Se5_diff)>=-30 && (Se4_diff+Se5_diff)<=30 ) )  //���ν�ʱ��������Զ��ƫ��Ǻܴ�
	{
		lb=0;rb=0;
		for(j=50;j>40;j--){if(IMG[1][j]==BLACK){lb++;}}     //ͳ��������ߵĵ�1��10�еİ׵���
		for(j=50;j>40;j--){if(IMG[2][j]==BLACK){lb++;}}     //ͳ��������ߵĵ�2��10�еİ׵���
		for(j=50;j>40;j--){if(IMG[3][j]==BLACK){lb++;}}     //ͳ��������ߵĵ�3��10�еİ׵���
		for(j=50;j>40;j--){if(IMG[4][j]==BLACK){lb++;}}     //ͳ��������ߵĵ�4��10�еİ׵���
		for(j=50;j>40;j--){if(IMG[5][j]==BLACK){lb++;}}     //ͳ��������ߵĵ�5��10�еİ׵���
		for(j=50;j>40;j--){if(IMG[6][j]==BLACK){lb++;}}     //ͳ��������ߵĵ�5��10�еİ׵���
		for(j=50;j>40;j--){if(IMG[7][j]==BLACK){lb++;}}     //ͳ��������ߵĵ�7��10�еİ׵���
				
		for(j=40;j>30;j--){if(IMG[1][j]==BLACK){rb++;}}   //ͳ�������ұߵĵ�1��10�еİ׵���
		for(j=40;j>30;j--){if(IMG[2][j]==BLACK){rb++;}}   //ͳ�������ұߵĵ�2��10�еİ׵���
		for(j=40;j>30;j--){if(IMG[3][j]==BLACK){rb++;}}   //ͳ�������ұߵĵ�3��10�еİ׵���
		for(j=40;j>30;j--){if(IMG[4][j]==BLACK){rb++;}}   //ͳ�������ұߵĵ�4��10�еİ׵���
		for(j=40;j>30;j--){if(IMG[5][j]==BLACK){rb++;}}   //ͳ�������ұߵĵ�5��10�еİ׵���
		for(j=40;j>30;j--){if(IMG[6][j]==BLACK){rb++;}}   //ͳ�������ұߵĵ�6��10�еİ׵���
		for(j=40;j>30;j--){if(IMG[7][j]==BLACK){rb++;}}   //ͳ�������ұߵĵ�7��10�еİ׵���
	
		if( (lb>=35) && (rb>=35) && (ZhiJiao_Flag==0) )   //�������ߺڵ���������35��Ϊֱ�Ǻڿ�
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
		ZhiDao_Flag=0; Left_Flag=0; Right_Flag=0; //��ֱ��������ı�־λ�������⴦��ֱ��
		
		lb=0;rb=0;    //���ã������ж�����ֱ��
		for(i=24;i>=20;i--)     //Զ��20--24�������ֱ��
		{
			for(j=78;j>=76;j--)    //������Ͻǵİ׵���
			{
				if(IMG[i][j]==WHITE)
				{
					lb++;
				}
			}
			for(j=1;j<=3;j++)     //������Ͻǵİ׵���
			{
				if(IMG[i][j]==WHITE)
				{
					rb++;
				}
			}	
		}
		/**/
		//��߰׵������ڵ���10���ұ߰׵�С��5.��Ϊ���ֱ����
		if(lb>=10 && rb<5)  
		{
			L_Z_Flag=1;	
		}
		//�ұ߰׵������ڵ���10����߰׵�С��5.��Ϊ�ҹ�ֱ����
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
������: Cross_Identify()
����: �������͵�ʶ��
����: ��
���: ��       **��ʹ��ȫ�ֱ�����λ�������ͱ�־��
************************************************
static void Cross_Identify(void)
{
    
  
}*/
/*************************************************
������: Identify()
����: �������͵�ʶ��
����: ��
���: ��       **��ʹ��ȫ�ֱ�����λ�������ͱ�־��
*************************************************/
void Identify(void)
{
	Diff();     //����1.2.3.4.5������ֵ�����ĵ�ƫ��,����ʹ��
	ZhiDao_Identify();   //�ж�ֱ��
	Left_Identify();     //�ж�����
	Right_Identify();    //�ж�����
//	ZhiJiao_Identify();  //�ж�ֱ�Ǻڿ� �Լ�����ֱ��
	//Cross_Identify();    //�ж�ʮ��
}


