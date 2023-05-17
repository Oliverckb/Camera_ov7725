#ifndef Servo_H
#define Servo_H


#include "COMMON.h"
#include "Users.h"

#define Serve_Left_Max   650    //�����ת���ֵ
#define Serve_Middle     920   //�������
#define Serve_Right_Max  1200   //�����ת���ֵ

/*******************************************************
 ��������Servo_Adjust
 ������duty  PWM23����ռ�ձ�
 ���ܣ������ұߵ�����ٶ�
*******************************************************/
void Servo_Adjust(uint duty);

/*************************************************
������: Servo_Control()
����: �������
����: ��
���: ��
*************************************************/
void Servo_Control(void);




#endif