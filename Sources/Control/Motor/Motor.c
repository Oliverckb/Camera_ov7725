#include "Motor.h"

/*************************************************
������: Motor_Stop()
����: ���ֹͣ
����: ��
���: ��
*************************************************/
void Motor_Stop(void) 
{                     
    DDRS_DDRS2=1;
    DDRS_DDRS3=1;
    PTS_PTS2=0;
    PTS_PTS3=0;
    PWMDTY01=0; 
    PWMDTY45=0;  
}


/*************************************************
������: Left_Motor_Forward
����: ����ǰ��
����: duty:PWM01ռ�ձ�
���: ��
*************************************************/
void Left_Motor_Forward(uint duty) 
{                     
    DDRS_DDRS2=1;
    PTS_PTS2=0;
    PWMDTY01=duty;  
}

/*************************************************
������: Right_Motor_Forward
����: �ҵ��ǰ��
����: duty:PWM45ռ�ձ�
���: ��
*************************************************/
void Right_Motor_Forward(uint duty) 
{                     
    DDRS_DDRS3=1;
    PTS_PTS3=0;
    PWMDTY45=duty;  
}
/*************************************************
������: Left_Motor_Back
����: ��������
����: duty:PWM01ռ�ձ�
���: ��
*************************************************/
void Left_Motor_Back(uint duty) 
{                     
  DDRS_DDRS2=1;
  PTS_PTS2=1;
  PWMDTY01=duty;
   
}
/*************************************************
������: Right_Motor_Back
����: �ҵ������
����: duty:PWM45ռ�ձ�
���: ��
*************************************************/
void Right_Motor_Back(uint duty) 
{                     
    DDRS_DDRS3=1;
    PTS_PTS3=1;
    PWMDTY45=duty;  
}


