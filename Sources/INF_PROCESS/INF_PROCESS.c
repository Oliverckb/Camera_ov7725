#include "INF_PROCESS.h"

extern uchar IMG[ROW][COLUMN];     //ͼ��ɼ����

extern X_Y SD_MID[ROW];    //������������ͼ���е�����
extern X_Y L[ROW];         //��߽���ͼ���е�����
extern X_Y R[ROW];         //�ұ߽���ͼ���е�����

/*******************************************************
 ��������MedFilter(schar last_dot,schar now_dot,schar next_dot)
 ���������������뵱ǰ��
 ���ܣ��������˲�ƽ�������ڴ�СΪ1x3
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
 ��������Black_Extract(void)
 ��������
 ���ܣ�ͼ�����������Լ������ߵ���ȡ���Լ���߽��������˲�ƽ������
       0--4�б߽���ȡ��5--24�и��ٱ����ұ߽�
*******************************************************/
void Black_Extract(void)
{
    schar i,j;
    uchar left_lost=0,rigth_lost=0; //ÿһ�е����ұ߽綪�߱�־  1:������  0������
    for(i=0;i<=24;i++)    //Ѱ�����ұ߽��Լ�����
    {
		left_lost=0,rigth_lost=0;  //���־λ
        for(j=79;j>=3;j--)   //Ѱ����߽�
        {
            if(IMG[i][j]==BLACK&&IMG[i][j-1]==BLACK && IMG[i][j-2]==WHITE&&IMG[i][j-3]==WHITE)
            {
                L[i].x = j-1;left_lost=0;break;      
            }
            else
            {
                left_lost=1; //��߽綪��
            }
        }
        for(j=0;j<=76;j++)    //Ѱ���ұ߽�
        {
            if(IMG[i][j]==BLACK&&IMG[i][j+1]==BLACK && IMG[i][j+2]==WHITE&&IMG[i][j+3]==WHITE)
            {
                R[i].x = j+1; rigth_lost=0;break;   
            }
            else
            {
                rigth_lost=1; //��߽綪��
            }
        }
        
        if(left_lost==1&&rigth_lost==0)    //ֻ������
        {
			if(i==0)
			{               
               L[0].x=  R[0].x + 65 ;//�ұ߽�Ԥ����߽�
			}
			else if(i==1)
			{                         
               L[1].x=R[1].x + (L[0].x- R[0].x-1);//�ұ߽�Ԥ����߽�
			}
			else
			{                                     
               L[i].x=R[i].x + (L[i-1].x- R[i-1].x-1); //�ұ߽�Ԥ����߽�
			}
        }
        
        if(left_lost==0&&rigth_lost==1)    //ֻ���Ҷ���
        {
			if(i==0)
			{           
               R[0].x=L[0].x - 65;//��߽�Ԥ���ұ߽�
			}
			else if(i==1)
			{                  
               R[1].x=L[1].x -(L[0].x- R[0].x-1);//��߽�Ԥ���ұ߽�
			}
			else
			{                                             
               R[i].x= L[i].x - (L[i-1].x- R[i-1].x-1);//��߽�Ԥ���ұ߽�
			}
        }
        
        if(left_lost==1&&rigth_lost==1)    //���Ҷ�����
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
				L[i].x=L[i-1].x + (L[i-1].x-L[i-2].x);  // ��߽�仯������Ԥ��
				R[i].x=R[i-1].x + (R[i-1].x-R[i-2].x);  // �ұ߽�仯������Ԥ��   	
			}
		}
    }
	
    for(i=0;i<=24;i++)//��������
    {
	    SD_MID[i].x=(sint)((L[i].x+R[i].x)/2);
    }
	
	for(i=0;i<=23;i++) //ƽ��������
	{
		SD_MID[i].x=MedFilter(SD_MID[i-1].x,SD_MID[i].x,SD_MID[i+1].x);
	}
		
}






