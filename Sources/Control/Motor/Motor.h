#ifndef Motor_H
#define Motor_H



#include "COMMON.h"
#include "Users.h"


/*************************************************
������: Motor_Stop()
����: ���ֹͣ
����: ��
���: ��
*************************************************/
void Motor_Stop(void); 


/*************************************************
������: Left_Motor_Forward
����: ����ǰ��
����: duty:PWM01ռ�ձ�
���: ��
*************************************************/
void Left_Motor_Forward(uint duty);
/*************************************************
������: Right_Motor_Forward
����: �ҵ��ǰ��
����: duty:PWM45ռ�ձ�
���: ��
*************************************************/
void Right_Motor_Forward(uint duty); 
/*************************************************
������: Left_Motor_Back
����: ��������
����: duty:PWM01ռ�ձ�
���: ��
*************************************************/
void Left_Motor_Back(uint duty);
/*************************************************
������: Right_Motor_Back
����: �ҵ������
����: duty:PWM45ռ�ձ�
���: ��
*************************************************/
void Right_Motor_Back(uint duty); 









#endif