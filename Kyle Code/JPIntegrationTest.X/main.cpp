//Kyle Frischman

// PIC32MZ2048ECG144 Configuration Bit Settings
// DEVCFG2

// System PLL Input Divider (2x Divider) 12MHz/2 = 6MHz
#pragma config FPLLIDIV = DIV_2   
// System PLL Input Range (5-10 MHz Input)
#pragma config FPLLRNG = RANGE_5_10_MHZ 
// System PLL Input Clock Selection (POSC is input to the System PLL)
#pragma config FPLLICLK = PLL_POSC 
// System PLL Multiplier (PLL Multiply by 112) 6MHz * 112 = 672MHz
#pragma config FPLLMULT = MUL_112  
// System PLL Output Clock Divider (8x Divider) 672MHz / 8 = 84MHz
#pragma config FPLLODIV = DIV_8  
// USB PLL Input Frequency Selection (USB PLL input is 12 MHz)
#pragma config UPLLFSEL = FREQ_12MHZ
// USB PLL Enable (USB PLL is disabled)
//#pragma config UPLLEN = OFF             

// DEVCFG1
// Oscillator Selection Bits (Primary Osc (HS,EC))
#pragma config FNOSC = SPLL    
// Secondary Oscillator Enable (Disable SOSC)
#pragma config FSOSCEN = OFF  
// Primary Oscillator Configuration (HS osc mode)
#pragma config POSCMOD = HS  
// Clock Switching and Monitor Selection /Clock Switch Disabled, FSCM Disabled
#pragma config FCKSM = CSDCMD 
// Watchdog Timer Enable (WDT Disabled)
#pragma config FWDTEN = OFF   
// Deadman Timer Enable (Deadman Timer is disabled)
#pragma config FDMTEN = OFF  

// DEVCFG0
#pragma config JTAGEN = OFF             // JTAG Enable (JTAG Disabled)
#pragma config ICESEL = ICS_PGx2        // ICE/ICD Comm Channel Select 

#pragma config CP = OFF  

#define LED_TRIS    TRISHbits.TRISH2    // macro for direction register bit of the LED pin
#define LED_LAT     LATHbits.LATH2      // macro for output register bit of the LED pin

#include <xc.h>
#include <sys/attribs.h>

#include "Touch/Touch_Driver.h"
#include "RTC2.h"
#include "LCD_Interface.h"

int main(void)
{
    //PB2DIV = 84MHz (No Division)
    //System PB2DIV Setup
    SYSKEY = 0; // Ensure lock
    SYSKEY = 0xAA996655; // Write Key 1
    SYSKEY = 0x556699AA; // Write Key 2
    PB2DIV = _PB2DIV_ON_MASK | 0 & _PB2DIV_PBDIV_MASK; // 0 = div by 1
    SYSKEY = 0; // Re lock
    
    //Wait states = 1
    //Flash Prefetch On
    PRECON = (1 & _PRECON_PFMWS_MASK) | 
            ((2 << _PRECON_PREFEN_POSITION) & _PRECON_PREFEN_MASK);
    
     //Enable Multi-Vector Mode
    INTCONSET = _INTCON_MVEC_MASK;
    
    //Init LCD
    LCD_Init();
    
    touch_hw_init();
    
    //Init Clock
    clock_init();
    
   lcd_time_init();
    
    //Timer Init
   timer_config();
   
   
    
    //Enable Global Interrupts
    asm("ei");
    
    //Enable Timer 2 Interrupt
    IEC0SET = _IEC0_T2IE_MASK;
    
    //Start Timer 2
    T2CONSET = 0x8000;
    
    LED_TRIS = 0;   // LED set as output
    
    //Scrensaver
    ScreenSaver();
    while(1)
    {
        //Run system
        
        //Call Test Function
        
    }
    
    
    return 0;
}


