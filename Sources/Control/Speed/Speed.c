 #include "Speed.h"
 
 /*********����������־***********/
extern uchar ZhiDao_Flag;   //ֱ����־      1��ֱ�� 
extern uchar Left_Flag;     //�����־λ    1������
extern uchar Right_Flag;    //�����־λ    1������

//��ֱ��ֱ�Ǻڿ��־�״�������1������ֱ�Ǳ�־������ֱ�ǻع��־
extern uchar ZhiJiao_Flag,L_Z_Flag,R_Z_Flag,L_HuiGui,R_HuiGui;
extern uint speed;  //��������ٶ�
/*************************************************
������: Init_Spped_M()
����: ��ʼ������ģ��
����: ��
���: ��
*************************************************/ 
void Init_Spped_M(void)
{
  Init_PORTAD(0);        //��ʼ��PADΪ���룬��������
  Init_PORTB(0);         //��ʼ��PB �����룬�ҵ������
  DDRE_DDRE7=1;          //PE7Ϊ�����źţ���ȡһ���ٶȾ͸���ߵ�ƽ����
  PORTE_PE7=0;   //��ʼ��Ϊ�͵�ƽ������״̬
}
 
/*************************************************
������: Left_Curret_Spped()
����: ��ȡ�����������ٶ�
����: ��
���: ��ǰ�������ٶ�
*************************************************/
uchar Left_Curret_Spped(void) 
{
	return  PT1AD0;
}

/*************************************************
������: Left_Curret_Spped()
����: ��ȡ�����������ٶ�
����: ��
���: ��ǰ�������ٶ�
*************************************************/
uchar Right_Curret_Spped(void) 
{
	return  PORTB;
}

/*************************************************
������: Spped_Clear()
����: ��������
����: ��
���: ��
*************************************************/
void  Spped_Clear(void)
{
	PORTE_PE7=1;
	_asm(nop);_asm(nop);	_asm(nop);_asm(nop);	
	PORTE_PE7=0;
	_asm(nop);_asm(nop);	_asm(nop);_asm(nop);
	

}

/*************************************************
������: Speed_Control()
����: ��������
����: ��
���: ��
*************************************************/
void Speed_Control(void)
{
  if(ZhiJiao_Flag>0)
  {
    	Left_Motor_Forward (130);
      Right_Motor_Forward(130); 
  }
  else
  {
     	Left_Motor_Forward (speed);
      Right_Motor_Forward(speed);
  }
  
}






