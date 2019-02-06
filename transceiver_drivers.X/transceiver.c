#include <xc.h>
#include "RFM69registers.h"
#include "transceiver.h"


void transceiver_spi_init(void) {

    
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

uint32_t receiver_buffer(void)
{
    // Setup SPI
    transceiver_spi_init();
    
    return 1;
}

void transmit_buffer(uint32_t data)
{
    
}