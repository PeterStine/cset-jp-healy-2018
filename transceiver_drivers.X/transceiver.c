/*************************************************************
* Author:		Peter Stine
* Filename:		transceiver.c
* Date Created:	2/6/2019
* Modifications: See Git Log
*
**************************************************************/
/*************************************************************
*   Oregon Institute of Technology
* Junior Project Healy 2018: Transceiver drivers 
* 
* Overview:
*	The transceiver modules draws 3.6V at 130mA producing
*   a range of less than 400 meters with horizontally
*   spread signal. Packet transmission is fully configurable
*   in software using commands sent over MISO line. The
 *  network node and network number fields are assigned
 * to each node so that they can identify each other.
 * 
 * The packet header and footer will be 228 bits, while the
 * data payload will be equal to the SPI1BUF buffer register.
 * The total packet size si 488 bits, hence the payload will
 * need to be a uint32_t or 32-bits long. Header will contain
 * network and node numbers, as well as a timestamp. Network
 * number is from 0-255 and node number is from 0-254; node
 * number 255 is reserved for whole network broadcast. Data
 * payload is the only component that will be recorded to
 * SD card storage, and is sized to be compatible with the
 * PIC32MZ 32-bit SPIxBUF buffer. The packet footer may 
 * contain the cyclic redundancy checking value.
 * 
* Input:
*	To check data incoming:
 *      uint32_t receiver_buffer(void)
* 	
* Output:
 *  To send data on the antenna:
*       transmit_buffer(uint32_t data)
* 	
* 	
* 	
* 	References:
*   https://github.com/sergev/LiteBSD/wiki/Olimex-HMZ144-board
*
************************************************************/



#include <xc.h>
#include "RFM69registers.h"
#include "transceiver.h"


/**********************************************************************	
* Purpose: This function initializes SPI status and control registers
*
* Precondition: 
*     No Global variables changed, SPI1 Special Function registers are 
 *      written and read from
*
* Postcondition: 
*      
*
************************************************************************/

void transceiver_spi_init(void) {

    
    //Setup SPI2 For Transmission
    //SPI Configuration
    //SPI Clock 2MHz 
    SPI1BRG = 0x8;
    
    //Turn off AN3 in ANSELB<3>
    ANSELBCLR = 0x8;
    //Clear MSSEN Bit in SPI4CON<28>, CKE = 0, SMP = 0
    SPI1CONCLR = 0x10000300;
    // CKP = 1
    SPI1CONSET = 0x8060;
    
    //PPS Configuration
    SDI1R = 0b0101; // RB9
    RPB10R = 0b0101; // RB10 = Serial Clock SDO1
    
    //Set LATF<8>
    LATGbits.LATG1 = 1; // Setting to output
    
    //Clear TRISF<8>
    TRISGbits.TRISG1 = 0;  // Set open-drain enable
}

/**********************************************************************	
* Purpose: This function writes to the MOSI SPI register
*
* Precondition: 
 *  
*
* Postcondition: 
*      
*
************************************************************************/
void tft_spiwrite(uint32_t c){ // Transfer to SPI
    
    PORTGbits.RG1 = 0; // Set chip select low
    SPI1BUF = c;       // Write data to MOSI buffer
    PORTGbits.RG1 = 1; // Done with SPI1BUF
}


void tft_spiwrite16(unsigned short c){  // Transfer two bytes "c" to SPI
    while (SPI4STATbits.TXBUFELM);
    SPI4BUF = (c);
    while (SPI4STATbits.SPIBUSY); // wait for it to end of transaction
}

uint32_t receiver_buffer(void)
{
    // Setup SPI
    transceiver_spi_init();
    
    //
    //tft_spiwrite(0b110010100000000); // [1=write][address=0x25][data=0xff]
    
    // Rx Start Procedure Page 38
    
    // RxReady interrupt warns Microcontroller that receiver is ready
    
    /* Continuous mode with bit synchronizer (minimum 12 bits of received preamble)
       
     */
    
    return 1;
}

/**********************************************************************	
* Purpose: This function writes to the MOSI SPI register, and will
 *          fill up the FIFO register on RFM69HCW
*
* Precondition: 
 *  
*
* Postcondition: 
*      
*
************************************************************************/
void transmit_buffer(uint32_t data)
{
    transceiver_spi_init();
    
    // TX start procedure Page 36 RFM69HCW-V1.1.pdf
    // ModeReady and TxReady interrupts warn microcontroller that
    // transmitter is ready to transmit data.
    // Status and control registers can be found on table 6.3 page 66
    
}