#include <xc.h>
#include "UART.h"

// Configures the UART and DMA module for character storage
void UART_CONFIG(void){
    
    
    //IEC3SET = 0x20000; // Enable receive interrupt IFS3
    //IPC28SET = 0x1C00; // Set receive priority = 7
    
    //*** UART Initialization *** 
    TRISHCLR = 0x700;  // Set PORTH8-11 output
    U1MODESET = 0x200; // Set UEN to RTS and CTS enabled and used
    U1STACLR = 0xC0C0; // Clear RXsel and TXsel
    U1STASET = 0x8000; // TXsel: while not empty, RXsel: while > 1 character
    U1MODESET = 0x10; // RX invert
    U1MODESET = 0x800; // simplex mode
    U1BRG = 0x222; // 9600 baud
    //U1STASET = 0x400;  // Set TX enable
    U1STASET = 0x1000; // Set RX enable
    U1MODESET = 0x8000; // Turn UART1 on 
    
    // PPS
    RPD11R = 0x1; // Select output pin RPD11 for U1TX
    U1RXR = 0xE; // Select input pin RPD6 for U1RX
    RPD5R = 0x1; // Select output pin RPD5 for U1RTS
    U1CTSR = 0x4; // Select input pin RPD4 for U1CTS

    // Enable prefetch and set waitstates to 1
    PRECON = (1 & _PRECON_PFMWS_MASK) | ((2 << _PRECON_PREFEN_POSITION) & _PRECON_PREFEN_MASK); 
    
    //*** Oscillator Configuration ***
    SYSKEY = 0;
    SYSKEY = 0xAA996655;
    SYSKEY = 0x556699AA;
    PB2DIVCLR = 0x7F; // Divide by 1 (84 Mhz))
    PB3DIVSET = 0x107F; // Divide by 128 (656,250 Hz))
    SYSKEY = 0;
    
    //*** Timer Configuration ***
    T1CONSET = 0x30; // Timer 1 prescale = 256: 2,563 Hz
    T2CONSET = 0x30; // Timer 2 prescale = 256: 2,563 Hz
    
    //*** DMA Configuration ***
    DMACONSET=0x00008000; // enable the DMA controller
    // DCH0ECON
    // DMAADDR
    // DCH0CON
    DCH0CONSET = 0x3; // Channel 0 priority 3
    DCH0CONSET = 0x80; // Channel 0 enabled
    DCH0ECONbits.CHSIRQ = 113; // U1RX vector triggers transfer event
    //DCH0ECONbits.CHAIRQ = 134; // Abort triggered by channel complete
    DCH0ECONSET = 0x10; // Enable IRQ trigger
    
    // program the transfer
    DCH0SSA = 0x1F822030; // Physical location of U1RXREG
    DCH0DSA = (0x1FFFFFFF & (uint32_t)UART_BUF); // transfer destination physical address
    
    DCH0SSIZ = 0x1; // source size 1 bytes
    DCH0DSIZ = BUFFER_SIZE; // destination size 8192 bytes
    DCH0CSIZ = 0x1; // 1 bytes transferred per event
    // DCH0INT
    DCH0INTCLR = 0x00ff00ff; // clear existing events, disable all interrupts
    
    DCH0CONbits.CHAEN = 0x1;
    
    DCH0CONSET = 0x80; // turn channel on

}
// Copies the current contents of the UART buffer into the public 40 Byte array,
// then returns the pointer to the beginning of this array.
uint8_t * UART_GET_BUFFER(void) {
    
    DCH0CONbits.CHEN = 0x0; // Disable channel to prevent writes
    while(DCH0CONbits.CHBUSY == 0x1) { asm("nop"); } // Wait for transfer to complete
    
    uint8_t i = 0;
    while(i < BUFFER_SIZE){
        UART_PUBLIC_BUFFER[i] = UART_BUF[i]; // Copy the contents of the buffer to the public one
        i++;
    }
    
    DCH0CONbits.CHEN = 0x1; // Re-enable the channel
    
    return (UART_PUBLIC_BUFFER); // return the starting address of the buffer.
    
}
