#include "bsp_sccb.h"

typedef struct Reg
{
  	uchar Address;			   /*�Ĵ�����ַ*/
    uchar Value;		      /*�Ĵ���ֵ*/
}Reg_Info;

/* �Ĵ����������� */
const Reg_Info Sensor_Config[] =
{
	{CLKRC,     0x00},/*ʱ������*/{COM7,      0x46}, /*QVGA RGB565 */
  {HSTART,    0x3f},            {HSIZE,     0x50},
  {VSTRT,     0x03},           	{VSIZE,     0x78},
	{HREF,      0x00},            {HOutSize,  0x50},
	{VOutSize,  0x78},            {EXHCH,     0x00},
	/*DSP control*/
 	{TGT_B,     0x7f},            {FixGain,   0x09},
 	{AWB_Ctrl0, 0xe0},            {DSP_Ctrl1, 0xff},
 	{DSP_Ctrl2, 0x20},	          {DSP_Ctrl3,	0x00},	{DSP_Ctrl4, 0x00},
	/*AGC AEC AWB*/
	{COM8,		  0xf0},            {COM4,		  0x81},/*Pll AEC CONFIG*/
	{COM6,		  0xc5},            {COM9,		  0x21},
	{BDBase,	  0xFF},            {BDMStep,	  0x01},
	{AEW,		    0x34},	          {AEB,		    0x3c},
 	{VPT,		    0xa1},            {EXHCL,		  0x00},
 	{AWBCtrl3,  0xaa}, 	          {COM8,		  0xff},
 	{AWBCtrl1,  0x5d},            {EDGE1,		  0x0a},	
 	{DNSOff,	  0x01},	          {EDGE2,		  0x01},
 	{EDGE3,		  0x01},          	{MTX1,		  0x5f},
 	{MTX2,		  0x53},            {MTX3,		  0x11},
 	{MTX4,		  0x1a},            {MTX5,		  0x3d},
 	{MTX6,		  0x5a},            {MTX_Ctrl,  0x1e},
 	{BRIGHT,	  0x00},            {CNST,		  0x25},
 	{USAT,		  0x65},          	{VSAT,		  0x65},
 	{UVADJ0,	  0x81},            {SDE,		    0x06},
    /*GAMMA config*/
 	{GAM1,		  0x0c},	          {GAM2,		  0x16},
 	{GAM3,		  0x2a},	          {GAM4,		  0x4e},
 	{GAM5,		  0x61},           	{GAM6,		  0x6f},
 	{GAM7,		  0x7b},          	{GAM8,		  0x86},
 	{GAM9,		  0x8e},          	{GAM10,		  0x97},
 	{GAM11,		  0xa4},          	{GAM12,		  0xaf},
 	{GAM13,		  0xc5},          	{GAM14,		  0xd7},
 	{GAM15,		  0xe8},          	{SLOP,		  0x20},
	{HUECOS,	  0x80},          	{HUESIN,	  0x80},
	{DSPAuto,	  0xff},           	{DM_LNL,	  0x00},
	{BDBase,	  0x99},            {BDMStep,	  0x03},
	{LC_RADI,	  0x00},            {LC_COEF,	  0x13},
	{LC_XC,		  0x08},            {LC_COEFB,  0x14},
	{LC_COEFR,  0x17},            {LC_CTR,	  0x05},
	{COM3,		  0xd0},/*Horizontal mirror image*/
	/*night mode auto frame rate control*/
  //{COM5,		0xf5},	 /*��ҹ�ӻ����£��Զ�����֡�ʣ���֤���նȻ�������*/
	{COM5,		0x31},	/*ҹ�ӻ���֡�ʲ���*/
};


uchar OV7725_REG_NUM=sizeof(Sensor_Config)/sizeof(Sensor_Config[0]);/*�ṹ�������Ա��Ŀ*/

/*************************************************
������: SCCB_Wait
����: ��ʱ
����: ��
���: ��
*************************************************/
static void SCCB_Wait(void)    
{
  unsigned char i;

  for(i=20;i>0;i--)
  {
    _asm nop;
  }
}

/*************************************************
������: SCCB_Start
����:SCCB��ʼ�ź�
����: ��
���: ��
*************************************************/
static void SCCB_Start(void)   
{
    SDA_DR=OUT;
    SDA = 1;
    SCL = 1;
    SCCB_Wait();
    SDA = 0;
    SCCB_Wait();
    SCL = 0;
}

/*************************************************
������: SCCB_Stop
����:SCCBֹͣ�ź�
����: ��
���: ��
*************************************************/
static void SCCB_Stop(void)    
{
    SDA_DR=OUT;
    SDA = 0;
    SCCB_Wait();
    SCL = 1;
    SCCB_Wait();
    SDA = 1;
    SCCB_Wait();
}



/*************************************************
������: SCCB_SendByte
����:��SCCB�Ĵ�����������
����: ����������
���: �ӻ�Ӧ���ź�   0�����ճɹ�     1������ʧ��
*************************************************/
static uchar SCCB_SendByte(uchar bytedata)  
{ 
   uchar i;
   uchar ack;
   SDA_DR=OUT;
   for(i=0;i<8;i++)
   {
        SCL = 0;
        SCCB_Wait();
        if(bytedata & 0x80)
          SDA = 1;
        else
          SDA = 0;
        
        bytedata <<= 1;
        SCCB_Wait();
        SCL = 1;
        SCCB_Wait();
        SCL = 0;
        SCCB_Wait();
    }
    SCL = 0;
    SCCB_Wait();
    
    SDA = 1;   
    SDA_DR=IN;
    SCCB_Wait();
    SCL = 1;
    SCCB_Wait();
    ack = SDA;   
    SCL = 0;
    SCCB_Wait();
    return ack;
}



/******************************************************
������:SCCB_ByteWrite
����:д���ݵ�ָ����ַ
����:  device���豸ID��OV7725:д0x42,��0x43�� 
      address: �Ĵ�����ַ 
     bytedata����д������
     
���: 0:�ɹ�    1��ʧ��
********************************************************/

static uchar SCCB_ByteWrite(uchar device,uchar address,uchar bytedata)
{     
     uchar i;
     uchar ack;
     for(i=0;i<10;i++)
     {
         SCCB_Start();
         ack = SCCB_SendByte(device);
         if(ack==1)
         {
             SCCB_Stop();
             continue;
         }
         
         ack = SCCB_SendByte(address);
         if(ack==1)
         {
             SCCB_Stop();
             continue;
         }
         
         ack = SCCB_SendByte(bytedata);
         if(ack==1)
         {
             SCCB_Stop();
             continue;
         }
         SCCB_Stop();
         
         if(ack==0) 
         break;    //����������ѭ��
     }
     return ack;
}


/************************************************
 * ��������SCCB_Init
 * ����  ��SCCB��ʼ��
 * ����  ����
 * ���  ������1�ɹ�������0ʧ��
 ************************************************/
uchar SCCB_Init(void)
{

    uchar i=0;
    SDA_DR=1;
    SCL_DR=1;
    SCCB_Wait();
    
    if( 1==SCCB_ByteWrite( DEV_ADR_W,0x12,0x80 ) )  /*��λ����Ĵ��� */
    {
           return 0;
    }
    
    for( i = 0 ; i < OV7725_REG_NUM ; i++ )
		{
    		if( 1==SCCB_ByteWrite( DEV_ADR_W,Sensor_Config[i].Address,Sensor_Config[i].Value ) )  /*��λ����Ĵ��� */
        {
               return 0;
        }
		}
    return 1;
	 
}







