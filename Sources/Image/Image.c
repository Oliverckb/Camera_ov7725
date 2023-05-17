#include "Image.h"

extern uchar IMG[ROW][COLUMN];     //ͼ��ɼ����

extern X_Y SD_MID[ROW];    //������������ͼ���е�����
extern X_Y L[ROW];         //��߽���ͼ���е�����
extern X_Y R[ROW];         //�ұ߽���ͼ���е�����

//�궨��ɼ�һ�����ص�ĺ꺯��
#define ONE_DOT()  RGB565=FIFO_READ();\
                   IMG[IMR][IMC++]=((RGB565&RGB565_RED)>>11) + ((RGB565&RGB565_GREEN)>>5) + (RGB565&RGB565_BLUE);\
                   J1();J1();J1()
//�ɼ�һ��80������                   
#define CAIJI_ONE_LINE();  for(i=5;i>0;i--){ONE_DOT();ONE_DOT();ONE_DOT();ONE_DOT();ONE_DOT();ONE_DOT();ONE_DOT();ONE_DOT();\
                                            ONE_DOT();ONE_DOT();ONE_DOT();ONE_DOT();ONE_DOT();ONE_DOT();ONE_DOT();ONE_DOT();\
                                            if(IMC==80) {IMC=0;IMR++;}}                 
 
//����һ������                   
#define ONE_LINE();   for(i=5;i>0;i--){J1();J1();J1();J1();J1();J1();J1();J1();J1();J1();J1();J1();J1();J1();J1();J1();\
                                       J1();J1();J1();J1();J1();J1();J1();J1();J1();J1();J1();J1();J1();J1();J1();J1();\
                                       J1();J1();J1();J1();J1();J1();J1();J1();J1();J1();J1();J1();J1();J1();J1();J1();\
                                       J1();J1();J1();J1();J1();J1();J1();J1();J1();J1();J1();J1();J1();J1();J1();J1();\
                                       }
    
       
/*******************************************************
 ��������GET_IMG()
 ��������
 ���ܣ���ȡһ��80X25��ͼ��
 8 16 24 32 40 48 56 64 72 80 88 96 104 112 120 128 136 144 152 160 168 176 184 192 200
*******************************************************/
void GET_IMG(void)
{   
    uchar k,i,IMR=0,IMC=0;
    uint RGB565;
    FIFO_PREPARE(); //FIFOΪ����׼��
    ONE_LINE();ONE_LINE();ONE_LINE();ONE_LINE();ONE_LINE();  //����5��
    for(k=25;k>0;k--)
    {
       CAIJI_ONE_LINE();
       ONE_LINE();ONE_LINE();ONE_LINE();ONE_LINE();ONE_LINE();  //����5��    
    }   
}


/*******************************************************
 ��������Binary_IMG()
 ��������
 ����:��80X25��ͼ���ֵ��
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
 ������:IMG_PROCESS()
 ��������
 ����:��80X25��ͼ���� 
*******************************************************/
void IMG_PROCESS(void)
{
    Binary_IMG();
       
}

/*******************************************************
 ��������SEND_IMG()
 ��������
 ����:��80X25��ͼ���͸���λ��
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
 ��������SHOW_Black_Line(void)
 ��������
 ����:��80X25��ͼ���͸���λ��
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







