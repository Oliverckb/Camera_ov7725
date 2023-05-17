
#include "PLL.h"



/*******************************************************
 函数名：SetSysCLK_16M
 参数：无
       锁相环时钟：PLLCLK=2*OSCLK*(SYNR+1) / (REFDV+1)
       总线时钟：BUSCLK=PLLCLK / 2
 功能：时钟初始化16M
*******************************************************/
void SetSysCLK_16M (void)
{   
    CLKSEL = 0X00;		  
    PLLCTL_PLLON = 1; 	// 启动PLL电路
    
    SYNR = 0x00|0x01; 	// VCOFRQ[7:6];SYNDIV[5:0]
                        // fVCO= 2*fOSC*(SYNDIV + 1)/(REFDIV + 1)
                        // fPLL= fVCO/(2 × POSTDIV) 
                        // fBUS= fPLL/2 
                        // VCOCLK Frequency Ranges  VCOFRQ[7:6]
                        // 32MHz <= fVCO <= 48MHz    00
                        // 48MHz <  fVCO <= 80MHz    01
                        // Reserved                  10
                        // 80MHz <  fVCO <= 120MHz   11				
    REFDV = 0x80|0x01;  // REFFRQ[7:6];REFDIV[5:0]
                        // fREF=fOSC/(REFDIV + 1)
                        // REFCLK Frequency Ranges  REFFRQ[7:6]
                        // 1MHz <= fREF <=  2MHz       00
                        // 2MHz <  fREF <=  6MHz       01
                        // 6MHz <  fREF <= 12MHz       10
                        // fREF >  12MHz               11                         
                        // pllclock=2*osc*(1+SYNR)/(1+REFDV)=32MHz;
    POSTDIV = 0x00;       // 4:0, fPLL= fVCO/(2xPOSTDIV)
                        // If POSTDIV = $00 then fPLL is identical to fVCO (divide by one).
    _asm (nop);          // BUS CLOCK=16M
    _asm (nop);
    while (!(CRGFLG_LOCK == 1));	  //  等待时锁相环时钟锁定
    CLKSEL_PLLSEL = 1;		        // 选定外部时钟 
}


/*******************************************************
 函数名：SetSysCLK_32M
 参数：无
       锁相环时钟：PLLCLK=2*OSCLK*(SYNR+1) / (REFDV+1)
       总线时钟：BUSCLK=PLLCLK / 2
 功能：时钟初始化32M
*******************************************************/
void SetSysCLK_32M (void)
{   
    CLKSEL = 0X00;			
    PLLCTL_PLLON = 1;			// 启动PLL电路
    SYNR = 0x40|0x03;  // pllclock=2*osc*(1+SYNR)/(1+REFDV)=64MHz;                      
    REFDV = 0x80|0x01; 
    POSTDIV = 0x00;  
    _asm (nop);           // BUS CLOCK=pllclock / 2=32M
    _asm (nop);
    while (!(CRGFLG_LOCK == 1));	  // 等待时锁相环时钟锁定
    CLKSEL_PLLSEL = 1;		        // 选定外部时钟  
}

/*******************************************************
 函数名：SetSysCLK_40M
 参数：无
       锁相环时钟：PLLCLK=2*OSCLK*(SYNR+1) / (REFDV+1)
       总线时钟：BUSCLK=PLLCLK / 2
 功能：时钟初始化40M
*******************************************************/
void SetSysCLK_40M (void)
{   
    CLKSEL = 0X00;			
    PLLCTL_PLLON = 1;			// 启动PLL电路
    SYNR = 0xc0|0x04;                        
    REFDV = 0x80|0x01; 
    POSTDIV = 0x00;       // pllclock=2*osc*(1+SYNR)/(1+REFDV)=80MHz;
    _asm (nop);           // BUS CLOCK=pllclock / 2=40M
    _asm (nop);
    while (!(CRGFLG_LOCK == 1));	  //  等待时锁相环时钟锁定
    CLKSEL_PLLSEL = 1;		        // 选定外部时钟 
}

/*******************************************************
 函数名：SetSysCLK_48M
 参数：无
       锁相环时钟：PLLCLK=2*OSCLK*(SYNR+1) / (REFDV+1)
       总线时钟：BUSCLK=PLLCLK / 2
 功能：时钟初始化48M
*******************************************************/
void SetSysCLK_48M (void)
{   
    CLKSEL = 0X00;			
    PLLCTL_PLLON = 1;			// 启动PLL电路
    SYNR = 0xc0|0x05;                        
    REFDV = 0x80|0x01; 
    POSTDIV = 0x00;       // pllclock=2*osc*(1+SYNR)/(1+REFDV)=96MHz;
    _asm (nop);          // BUS CLOCK=pllclock / 2=48M
    _asm (nop);
    while(!(CRGFLG_LOCK==1));	  // 等待时锁相环时钟锁定
    CLKSEL_PLLSEL =1;		        //选定外部时钟 
}


/*******************************************************
 函数名：SetSysCLK_64M
 参数：无
       锁相环时钟：PLLCLK=2*OSCLK*(SYNR+1) / (REFDV+1)
       总线时钟：BUSCLK=PLLCLK / 2
 功能：时钟初始化64M
*******************************************************/
void SetSysCLK_64M (void)
{   
    CLKSEL = 0X00;			
    PLLCTL_PLLON = 1;			//启动PLL电路
    SYNR = 0xc0|0x07;                        
    REFDV = 0x80|0x01; 
    POSTDIV = 0x00;       // pllclock=2*osc*(1+SYNR)/(1+REFDV)=128MHz;
                          // BUS CLOCK=pllclock / 2=64M
   
    _asm (nop);_asm (nop);
    while (!(CRGFLG_LOCK == 1));	  // 等待时锁相环时钟锁定
    CLKSEL_PLLSEL = 1;		          //选定外部时钟 
}


/*******************************************************
 函数名：SetSysCLK_80M
 参数：无
       锁相环时钟：PLLCLK=2*OSCLK*(SYNR+1) / (REFDV+1)
       总线时钟：BUSCLK=PLLCLK / 2
 功能：时钟初始化80M
*******************************************************/
void SetSysCLK_80M (void)
{   
    CLKSEL = 0X00;			
    PLLCTL_PLLON = 1;			// 启动PLL电路
    SYNR = 0xc0|0x09;                        
    REFDV = 0x80|0x01; 
    POSTDIV = 0x00;       // pllclock=2*osc*(1+SYNR)/(1+REFDV)=160MHz;
                          // BUS CLOCK=pllclock / 2=80M
    
    _asm (nop);_asm (nop);          
    while (!(CRGFLG_LOCK == 1));	  // 等待时锁相环时钟锁定
    CLKSEL_PLLSEL = 1;		        // 选定外部时钟 
}


/*******************************************************
 函数名：SetSysCLK_88M
 参数：无
       锁相环时钟：PLLCLK=2*OSCLK*(SYNR+1) / (REFDV+1)
       总线时钟：BUSCLK=PLLCLK / 2
 功能：时钟初始化88M
*******************************************************/
void SetSysCLK_88M (void)
{   
    CLKSEL = 0X00;		
    PLLCTL_PLLON = 1;		// 启动PLL电路
    SYNR = 0xc0 | 0x0a;                        
    REFDV = 0x80 | 0x01; 
    POSTDIV = 0x00;       // pllclock=2*osc*(1+SYNR)/(1+REFDV)=176MHz;
                          //BUS CLOCK=pllclock / 2=88M
    
    _asm (nop);_asm (nop);
    while (!(CRGFLG_LOCK == 1));	  // 等待时锁相环时钟锁定
    CLKSEL_PLLSEL = 1;		          // 选定外部时钟 
}

/*******************************************************
 函数名：SetSysCLK_96M
 参数：无
       锁相环时钟：PLLCLK=2*OSCLK*(SYNR+1) / (REFDV+1)
       总线时钟：BUSCLK=PLLCLK / 2
 功能：时钟初始化96M
*******************************************************/
void SetSysCLK_96M(void)
{  
    CLKSEL=0X00;    
    PLLCTL_PLLON=1;   
    SYNR =0xc0 | 0x0b;                       
    REFDV=0x80 | 0x01;
    POSTDIV=0x00;       //pllclock=2*osc*(1+SYNR)/(1+REFDV)=192MHz;
    _asm(nop);          //BUS CLOCK=96M
    _asm(nop);
    while(!(CRGFLG_LOCK==1));   
    CLKSEL_PLLSEL =1;         
}


