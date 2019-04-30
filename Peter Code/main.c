/* Author: 			Peter Stine, <others>
 * Date Created:		12/17/18
 * Last Modification Date:	12/17/18
 * Filename:			main.cpp
 * Dependency Level:		Top-Level
 *
 * Functional Overview:
 *
 * 	This program will utilize several other c++ and c-language libraries similar in function
 * 	to the github repositories listed in the references section of this header block.
 * 	This main.c file will act as the top level dependency for the LCD driver and
 * 	Radio Transciever Module Driver functions.
 *
 * Junior Project Specific Use Policies:
 *
 * 	For maintaining integrity of the function of this code repository, only the person
 * 	who's name is listed at the beginning of the file is permitted to write changes to
 * 	that file. All other persons will be allowed read-only access to a file where 
 * 	their name does not appear in the header.
 *
*/


#include <xc.h>
#include "RFM69registers.h"
#include ""

#pragma config FPLLIDIV = DIV_2         // System PLL Input Divider (2x Divider) 12MHz/2 = 6MHz
#pragma config FPLLRNG = RANGE_5_10_MHZ // System PLL Input Range (5-10 MHz Input)
#pragma config FPLLICLK = PLL_POSC      // System PLL Input Clock Selection (POSC is input to the System PLL)
#pragma config FPLLMULT = MUL_112       // System PLL Multiplier (PLL Multiply by 112) 6MHz * 112 = 672MHz
#pragma config FPLLODIV = DIV_8         // System PLL Output Clock Divider (8x Divider) 672MHz / 8 = 84MHz
#pragma config UPLLFSEL = FREQ_12MHZ    // USB PLL Input Frequency Selection (USB PLL input is 12 MHz)

// DEVCFG1
#pragma config FNOSC = SPLL             // Oscillator Selection Bits (Primary Osc (HS,EC))
#pragma config FSOSCEN = OFF            // Secondary Oscillator Enable (Disable SOSC)
#pragma config POSCMOD = HS             // Primary Oscillator Configuration (HS osc mode)
#pragma config FCKSM = CSDCMD           // Clock Switching and Monitor Selection (Clock Switch Disabled, FSCM Disabled)
#pragma config FWDTEN = OFF             // Watchdog Timer Enable (WDT Disabled)
#pragma config FDMTEN = OFF             // Deadman Timer Enable (Deadman Timer is disabled)

// DEVCFG0
#pragma config JTAGEN = OFF             // JTAG Enable (JTAG Disabled)
#pragma config ICESEL = ICS_PGx2        // ICE/ICD Comm Channel Select (Communicate on PGEC2/PGED2)

void tft_init_hw(void) {

    
    //Setup SPI2 For Transmission
    //SPI Configuration
    //SPI Clock 2MHz 
    SPI4BRG = 1;
    //Turn off AN3 in ANSELB<3>
    ANSELBCLR = 0x8;
    //Clear MSSEN Bit in SPI4CON<28>, CKE = 0, SMP = 0
    SPI4CONCLR = 0x10000300;
    // CKP = 1
    SPI4CONSET = 0x8060;
    //PPS Configuration
    //SDI4 = RPB3
    SDI4R = 0x1000;
    //SD04 = RPF2 --> set the output pin
    RPD5R = 0x1000; // RD10 = Serial Clock SDO4
    //Set LATF<8>
    LATFSET = 0x100;
    //Clear TRISF<8>
    TRISFCLR = 0x100;
    TRISDCLR = 0x20;
  
}

void tft_spiwrite(uint32_t c){ // Transfer to SPI
    SPI4BUF = c;
   // while (SPI4STATbits.SPIBUSY); // wait for it to end of transaction
}


void tft_spiwrite16(unsigned short c){  // Transfer two bytes "c" to SPI
    while (SPI4STATbits.TXBUFELM);
    SPI4BUF = (c);
    while (SPI4STATbits.SPIBUSY); // wait for it to end of transaction
}

int main()
{
	// Setup SPI
    tft_init_hw();
    
    /// Send data payload
    while(1)
    {
        tft_spiwrite(0b110010100000000); // [1=write][address=0x25][data=0xff]
    }
    
    // Trigger interrupt for when data is receivedNp 
    
    
	return 0;
}
