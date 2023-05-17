
//PORTA��ȡ����ͷ����

// PORTB��ȡ�ұ߱���������
//PORTAD��ȡ��߱���������






#include "IO.h"


/*******************************************************
 �������IInit_PORTA()
 ������config   0--����
                1--���
       
 ���ܣ���ʼ��PORTA
*******************************************************/
void Init_PORTA(unsigned char config)
{
    if(config==0)
    {
        DDRA=0x00; 
    }
    else
    {
        DDRA=0xff;
    }
}
/*******************************************************
 ��������Set_PORTA()
 ������config   0--PORTA=00000000
                1--PORTA=11111111
       
 ���ܣ�����PORTA����ߵ͵�ƽ
*******************************************************/
void Set_PORTA(uchar config)
{
    if(config==0)
    {
        PORTA=0x00; 
    }
    else
    {
        PORTA=0xff;
    }
}
/*******************************************************
 ��������Read_PORTA()
 ��������
 ����ֵ:PORTA������     
 ���ܣ���ȡPORTA��ƽ
*******************************************************/
uchar Read_PORTA(void)
{
    return PORTA;
}



/*******************************************************
 �������IInit_PORTB()
 ������config   0--����
                1--���
       
 ���ܣ���ʼ��PORTA
*******************************************************/
void Init_PORTB(uchar config)
{
    if(config==0)
    {
        DDRB=0x00; 
    }
    else
    {
        DDRB=0xff;
    }
}
/*******************************************************
 ��������Set_PORTB()
 ������config   0--PORTB=00000000
                1--PORTB=11111111
       
 ���ܣ�����PORTB����ߵ͵�ƽ
*******************************************************/
void Set_PORTB(uchar config)
{
    if(config==0)
    {
        PORTB=0x00; 
    }
    else
    {
        PORTB=0xff;
    }
}
/*******************************************************
 ��������Read_PORTB()
 ��������
 ����ֵ:PORTB������     
 ���ܣ���ȡPORTB��ƽ
*******************************************************/
uchar Read_PORTB(void)
{
    return PORTB;
}


/*******************************************************
 �������IInit_PORTAD()
 ������config   0--����
                1--���
       
 ���ܣ���ʼ��PORTAD
*******************************************************/
void Init_PORTAD(uchar config)
{    
    
    if(config==0)
    {
        ATD0DIEN=0xffff;
        PER1AD0=0XFF;  //����
        DDR1AD0=0x00;    
    }
    else
    {
	     ATD0DIEN=0xffff;
       DDR1AD0=0xff;
    }
}
/*******************************************************
 ��������Set_PORTAD()
 ������config   0--PORTB=00000000
                1--PORTB=11111111
       
 ���ܣ�����PORTAD����ߵ͵�ƽ
*******************************************************/
void Set_PORTAD(uchar config)
{
    if(config==0)
    {
        PT1AD0=0x00; 
    }
    else
    {
        PT1AD0=0xff;
    }
}
/*******************************************************
 ��������Read_PORTAD()
 ��������
 ����ֵ:PORTAD������     
 ���ܣ���ȡPORTAD��ƽ
*******************************************************/
uchar Read_PORTAD(void)
{
    
    
   
    return PT1AD0;
}


/*******************************************************
 �������IInit_PTM()
 ������config   0--����
                1--���
       
 ���ܣ���ʼ��PTM
*******************************************************/
void Init_PTM(uchar config)
{
    if(config==0)
    {
        DDRM=0x00; 
    }
    else
    {
        DDRM=0xff;
    }
}

/*******************************************************
 ��������Set_PTM()
 ������config   0--PTM=00000000
                1--PTM=11111111
       
 ���ܣ�����PTM����ߵ͵�ƽ
*******************************************************/
void Set_PTM(uchar config)
{
    if(config==0)
    {
        PTM=0x00; 
    }
    else
    {
        PTM=0xff;
    }
}
/*******************************************************
 ��������Read_PORTM()
 ��������
 ����ֵ:PORTM������     
 ���ܣ���ȡPORTA��ƽ
*******************************************************/
uchar Read_PTM(void)
{
    return PTM;
}






