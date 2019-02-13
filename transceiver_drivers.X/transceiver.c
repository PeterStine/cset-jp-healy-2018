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
#include <stdio.h>
#include "RFM69registers.h"
#include "transceiver.h"

// Global Variables used for debugging and not for deployment purposes
const uint8_t verbosity = 0;

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
    
    // SPI1CON
    
    //Setup SPI2 For Transmission
    //SPI Configuration
    //SPI Clock 2MHz 
    SPI1BRG = 0x8;
    
    //Turn off AN3 in ANSELB<3>
    ANSELBCLR = 0xC00;
    
    //Clear MSSEN Bit in SPI4CON<28>, CKE = 0, SMP = 0
    SPI1CONCLR = 0x10000300;
    // CKP = 1
    SPI1CONSET = 0x8460; // 16-bit mode
    
    //PPS Configuration
    SDI1R = 0b0101; // RB9
    RPB10R = 0b0101; // RB10 = Serial Clock SDO1
    
    //Set LATF<8>
    LATGbits.LATG1 = 1; // Setting open-drain enable
    
    //Clear TRISF<8>
    TRISGbits.TRISG1 = 0;  // Setting pin to output 
}

/**********************************************************************	
* Purpose: This function writes to the MOSI SPI register
*          RFM69HCW datasheet page 44 specifies that only 16 bits 
*          should be written at a time for MOSI
*
* Precondition: 
*  	MOSI should be ready to write to
*  	Must set chip select low
*
* Postcondition: 
*      Set chip select high after writing.
*
************************************************************************/
void rfm_spiwrite16_raw(uint16_t c){ // Transfer to SPI
    PORTGbits.RG1 = 0; // Set chip select low
    SPI1BUF = c;       // Write data to MOSI buffer
    PORTGbits.RG1 = 1; // Done with SPI1BUF
}

/**********************************************************************	
* Purpose: This function writes to the MOSI SPI register
*          RFM69HCW datasheet page 44 specifies that only 16 bits 
*          should be written at a time for MOSI
*
*          *THis function is different from rfm_spriwrite16_raw in that
*          it will construct a read/write by passing logical bytes that 
*          will utiliize register definitions from rfmRegisters.h to
*          produce more readable and maintainable use of functions
*          that write/read to the MOSI line.
*
* Precondition: 
*  	MOSI should be ready to write/read
*  	MOSI Line will be high-impedance before read/write operation
*  	Must set chip select low
*
* Postcondition: 
*      Set chip select high after writing.
*
* References: 
* https://stackoverflow.com/questions/15249791/combining-two-uint8-t-as-uint16-t
**************************************************************************/
void rfm_spiwrite_single_access(uint8_t mode, uint8_t addr, uint8_t data){
	uint16_t combination = 0x0000;
    
    switch(mode) {
		case 0: // Read access
			break;
		case 1: // Write access
			
            combination = mode;
            combination  = combination << 15;
			combination = combination | (((uint16_t)addr << 7) | data);// concatenate addr and data			
            
			PORTGbits.RG1 = 0;      // Set chip select low
			SPI1BUF = combination;  // Write data to MOSI buffer
            while(SPI1STATbits.SPIBUSY); // Wait for SPI to finish being busy
			PORTGbits.RG1 = 1;      // Done with SPI1BUF

			if(verbosity == 1){
				printf("Contents of SPI1BUF: %d \n",combination);
			}

			break;
           
	}
}

//////////////////////////////////////////////////////////////////////////
// Below is unused. Delete if above function is successful
void tft_spiwrite16(uint32_t c){  // Transfer two bytes "c" to SPI
    while (SPI1STATbits.TXBUFELM);
    SPI1BUF = (c);
    while (SPI1STATbits.SPIBUSY); // wait for it to end of transaction
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
void transmit_buffer(uint16_t data)
{
    transceiver_spi_init();
    
    // TX start procedure Page 36 RFM69HCW-V1.1.pdf
    // ModeReady and TxReady interrupts warn microcontroller that
    // transmitter is ready to transmit data.
    // Status and control registers can be found on table 6.3 page 66
    
    // 5.2.2 SPI Interface Page 44
    
    while(1)
   {
       // Following code is for testing behavior only, not for deployment
   // write mode 1, address 7, data 8
    // Continuous Mode uses DIO pins, not SPI
       // Packet mode uses SPI control interface
       // What is NRZ Data
     
       
       // Begin setup of packet format on RFM6969HCW-V1.1.pdf Page 51
       // packet handler sequence for Tx
       //rfm_spiwrite_single_access(1, PacketFormat, 0xff);
       
       // Preamble      <0:65535>   bytes
       // Sync Word     <0:8>       bytes
       // Address       <1>         byte
       // Message       <8:255>     bits
       // CRC           <2>         bytes
       
        // Page 53 - TX Processing without AES
        // Configuration and status registers page 60
       
       //Begin Transceiver in Stdby/Sleep mode
       
       // Fill FIFO
       rfm_spiwrite_single_access(1, REG_FIFO, 0b000); // 4444
       
       // GIve transmit command
   }

}

// Kyle put your code down here

