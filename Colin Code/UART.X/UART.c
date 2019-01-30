#include <xc.h>
#include <sys/attribs.h>

// PIC32MZ2048ECG144 Configuration Bit Settings
// DEVCFG2
#pragma config FPLLIDIV = DIV_2         // System PLL Input Divider (2x Divider) 12MHz/2 = 6MHz
#pragma config FPLLRNG = RANGE_5_10_MHZ // System PLL Input Range (5-10 MHz Input)
#pragma config FPLLICLK = PLL_POSC      // System PLL Input Clock Selection (POSC is input to the System PLL)
#pragma config FPLLMULT = MUL_112       // System PLL Multiplier (PLL Multiply by 112) 6MHz * 112 = 672MHz
#pragma config FPLLODIV = DIV_8         // System PLL Output Clock Divider (8x Divider) 672MHz / 8 = 84MHz
#pragma config UPLLFSEL = FREQ_12MHZ    // USB PLL Input Frequency Selection (USB PLL input is 12 MHz)
#pragma config UPLLEN = OFF             // USB PLL Enable (USB PLL is disabled)

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

// Initialized UART, and enables DMA transfers to the UART_BUFFER array.
int UART_INIT(void) {
    
    TRISHCLR = 0x700;  // Set PORTH8-11 output
    //U1MODESET = 0x200; // Set UEN to RTS and CTS enabled and used
    
    CNPUHSET = 0x78;
    ANSELH = 0x0;
    
    // PPS
    RPD11R = 0x1; // Select output pin RPD11 for U1TX
    U1RXR = 0xE; // Select input pin RPD6 for U1RX
    
    PRECON = (1 & _PRECON_PFMWS_MASK) | ((2 << _PRECON_PREFEN_POSITION) & _PRECON_PREFEN_MASK); // Enable prefetch and set waitstates to 1
    
    SYSKEY = 0;
    SYSKEY = 0xAA996655;
    SYSKEY = 0x556699AA;
    PB2DIVCLR = 0x7F; // Divide by 1 (84 Mhz))
    PB3DIVSET = 0x107F; // Divide by 128 (656,250 Hz))
    SYSKEY = 0;
    
    // U1MODE
    //TMR1 = 1280; // half second period
    
    U1MODESET = 0x10; // RX invert
    U1MODESET = 0x800; // simplex mode
    U1BRG = 0x222; // BRG = 181, BR = 115,384 baud
    
    U1STACLR = 0xC; // RXISEL = 0
    IEC3SET = 0x20000; // Enable receive interrupt IFS3
    IPC28SET = 0x1C00; // Set receive priority = 7
    IPC28SET = 0x1C0000;
    INTCONSET = 0x1000;
    
    //U1STASET = 0x400;  // Set TX e
    U1STASET = 0x1000; // Set RX enable
    U1MODESET = 0x8000; // Turn UART1 on
    
    asm("ei");
    
    //U1TXREG = 0x65;
    
    LATHCLR = 0x700; // Turn LEDs off
    
    /* This code example illustrates the DMA channel 0 configuration for a data transfer. */
    IEC1CLR=0x00010000; // disable DMA channel 0 interrupts
    IFS1CLR=0x00010000; // clear existing DMA channel 0 interrupt flag
    
    DMACONSET=0x00008000; // enable the DMA controller
    
    DCH0CON=0x3; // channel off, priority 3, no chaining
    DCH0ECONbits.CHSIRQ = 113; // U1RX vector triggers transfer event
    DCH0ECONSET = 0x10; // Enable IRQ trigger
    
    // program the transfer
    DCH0SSA = 0x1F822030 // Physical location of U1RXREG
    DCH0DSA = (0x1FFFFFFF & &UART_BUFFER); // transfer destination physical address
    
    DCH0SSIZ = 0x1; // source size 1 bytes
    DCH0DSIZ = 0x8; // destination size 8 bytes
    DCH0CSIZ = 0x1; // 1 bytes transferred per event
    
    DCH0INTCLR=0x00ff00ff; // clear existing events, disable all interrupts
    DCH0CONSET=0x80; // turn channel on

}
