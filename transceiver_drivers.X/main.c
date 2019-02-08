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
#include "transceiver.h"

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

int main()
{
    transceiver_spi_init();
    /// Send data payload
    while(1)
    {
        rfm_spiwrite(REG_OPMODE);
    }
    
    // Trigger interrupt for when data is received
    
    
	return 0;
}
