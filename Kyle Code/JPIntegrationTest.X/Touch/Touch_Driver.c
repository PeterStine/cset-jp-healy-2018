

#include "Touch_Driver.h"
#include <xc.h>

void touch_hw_init()
{
    //Set Chip Select Low
    LATFbits.LATF5 = 1;
    TRISFbits.TRISF5 = 0;
    //Setup IRQ Pin
    TRISFbits.TRISF4 = 1;
    CNENFbits.CNIEF4 = 1;
    IFS3bits.CNFIF = 0;
    IFS3bits.CNFIF = 1;
    IPC30bits.CNFIP = 6;
    
    //Set Chip Select High
    LATFCLR = _PORTF_RF5_MASK;
    
    //Send Init Byte (0x90)
    touch_SPISend(TINIT);
}

int touch_SPISend(uint8_t dataOut)
{
    //Set Chip Select High
    
    //Set Chip Select Low
    
    //Send 
    SPI4BUF = dataOut;
    
    //Delay 2 ms
    
    //Set CS High
    
    return SPI4BUF;
}

int touch_getX()
{
    int x = 0;
    //Send Get X Command (0x90)
    x = touch_SPISend(0x90);
    
    //Conversion Logic
    
    
    if (x<=0) x = 0;
    if (x >= LCD_W) x = LCD_W;
    
    return x;
}

int touch_getY()
{
    int y = 0;
    
    //Send Get Y Command (0xD0))
    y = touch_SPISend(0x90);
    
    //Conversion Logic
    
    
    if (y <= 0) y = 0;
    if (y >= LCD_H) y = LCD_H;
    
    return y;
}
