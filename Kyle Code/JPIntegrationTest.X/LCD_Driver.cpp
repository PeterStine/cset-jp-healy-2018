//Kyle Frischman
//Adapted Adafruit Library for PIC32MZ


/*!
*
* Written by Limor "ladyada" Fried for Adafruit Industries.
*
*/

#include "LCD_Driver.h"
#include <xc.h>

#define MADCTL_MY  0x80  ///< Bottom to top
#define MADCTL_MX  0x40  ///< Right to left
#define MADCTL_MV  0x20  ///< Reverse Mode
#define MADCTL_ML  0x10  ///< LCD refresh Bottom to top
#define MADCTL_RGB 0x00  ///< Red-Green-Blue pixel order
#define MADCTL_BGR 0x08  ///< Blue-Green-Red pixel order
#define MADCTL_MH  0x04  ///< LCD refresh right to left


Adafruit_ILI9341::Adafruit_ILI9341()  {
}

static const uint8_t initcmd[] = {
  0xEF, 3, 0x03, 0x80, 0x02,
  0xCF, 3, 0x00, 0xC1, 0x30,
  0xED, 4, 0x64, 0x03, 0x12, 0x81,
  0xE8, 3, 0x85, 0x00, 0x78,
  0xCB, 5, 0x39, 0x2C, 0x00, 0x34, 0x02,
  0xF7, 1, 0x20,
  0xEA, 2, 0x00, 0x00,
  ILI9341_PWCTR1  , 1, 0x23,             // Power control VRH[5:0]
  ILI9341_PWCTR2  , 1, 0x10,             // Power control SAP[2:0];BT[3:0]
  ILI9341_VMCTR1  , 2, 0x3e, 0x28,       // VCM control
  ILI9341_VMCTR2  , 1, 0x86,             // VCM control2
  ILI9341_MADCTL  , 1, 0x48,             // Memory Access Control
  ILI9341_VSCRSADD, 1, 0x00,             // Vertical scroll zero
  ILI9341_PIXFMT  , 1, 0x55,
  ILI9341_FRMCTR1 , 2, 0x00, 0x18,
  ILI9341_DFUNCTR , 3, 0x08, 0x82, 0x27, // Display Function Control
  0xF2, 1, 0x00,                         // 3Gamma Function Disable
  ILI9341_GAMMASET , 1, 0x01,             // Gamma curve selected
  ILI9341_GMCTRP1 , 15, 0x0F, 0x31, 0x2B, 0x0C, 0x0E, 0x08, // Set Gamma
    0x4E, 0xF1, 0x37, 0x07, 0x10, 0x03, 0x0E, 0x09, 0x00,
  ILI9341_GMCTRN1 , 15, 0x00, 0x0E, 0x14, 0x03, 0x11, 0x07, // Set Gamma
    0x31, 0xC1, 0x48, 0x08, 0x0F, 0x0C, 0x31, 0x36, 0x0F,
  ILI9341_SLPOUT  , 0x80,                // Exit Sleep
  ILI9341_DISPON  , 0x80,                // Display on
  0x00                                   // End of list
};

/**************************************************************************/
/*!
    @brief   Initialize ILI9341 chip
    Connects to the ILI9341 over SPI and sends initialization procedure commands
    @param    freq  Desired SPI clock frequency
*/
/**************************************************************************/
void Adafruit_ILI9341::begin() {

    //Setup SPI2 For Transmission
    //SPI Configuration
    //SPI Clock 2MHz 
    SPI4BRG = 8;
    //Turn off AN3 in ANSELB<3>
    ANSELBCLR = 0x8;
    //Clear MSSEN Bit in SPI4CON<28>, CKE = 0, SMP = 0
    SPI4CONCLR = 0x10000300;
    // CKP = 1
    SPI4CONSET = 0x8060;
    //PPS Configuration
    //SDI4 = RPB3
    SDI4R = 0x8;
    //SD04 = RPF2
    RPF2R = 0x8;
    //Set LATF<8>
    LATFSET = 0x100;
    //Clear TRISF<8>
    TRISFCLR = 0x100;
    //SPI Write

    
    LATFCLR = _PORTF_RF8_MASK;
    LATFCLR = _PORTF_RF0_MASK;
    
    uint8_t        cmd, x, numArgs;
    const uint8_t *addr = initcmd;
    while((cmd = *(addr++)) > 0) {
        SPI4BUF = (cmd);
        x       = *(addr++);
        numArgs = x & 0x7F;
        while(numArgs--)
        {
            SPI4BUF = (*(addr++));
        }
        
        if(x & 0x80)
        {
            //delay(120);
        }
    }

    LATFSET = _PORTF_RF8_MASK;
    LATFSET = _PORTF_RF0_MASK;
    
    _width  = ILI9341_TFTWIDTH;
    _height = ILI9341_TFTHEIGHT;
}


/**************************************************************************/
/*!
    @brief   Set origin of (0,0) and orientation of TFT display
    @param   m  The index for rotation, from 0-3 inclusive
*/
/**************************************************************************/
void Adafruit_ILI9341::setRotation(uint8_t m) {
    uint8_t rotation = m % 4; // can't be higher than 3
    switch (rotation) {
        case 0:
            m = (MADCTL_MX | MADCTL_BGR);
            _width  = ILI9341_TFTWIDTH;
            _height = ILI9341_TFTHEIGHT;
            break;
        case 1:
            m = (MADCTL_MV | MADCTL_BGR);
            _width  = ILI9341_TFTHEIGHT;
            _height = ILI9341_TFTWIDTH;
            break;
        case 2:
            m = (MADCTL_MY | MADCTL_BGR);
            _width  = ILI9341_TFTWIDTH;
            _height = ILI9341_TFTHEIGHT;
            break;
        case 3:
            m = (MADCTL_MX | MADCTL_MY | MADCTL_MV | MADCTL_BGR);
            _width  = ILI9341_TFTHEIGHT;
            _height = ILI9341_TFTWIDTH;
            break;
    }

   // startWrite();
   SPI4BUF = (ILI9341_MADCTL);
   SPI2BUF = (m);
   
}

/**************************************************************************/
/*!
    @brief   Enable/Disable display color inversion
    @param   invert True to invert, False to have normal color
*/
/**************************************************************************/
void Adafruit_ILI9341::invertDisplay(bool invert) {
    //startWrite
    SPI2BUF = (invert ? ILI9341_INVON : ILI9341_INVOFF);
    
}

/**************************************************************************/
/*!
    @brief   Scroll display memory
    @param   y How many pixels to scroll display by
*/
/**************************************************************************/
void Adafruit_ILI9341::scrollTo(uint16_t y) {
    //startWrite
    SPI2BUF = (ILI9341_VSCRSADD);
    SPI2BUF = (y);
    
}

/**************************************************************************/
/*!
    @brief   Set the "address window" - the rectangle we will write to RAM with the next chunk of SPI data writes. The ILI9341 will automatically wrap the data as each row is filled
    @param   x  TFT memory 'x' origin
    @param   y  TFT memory 'y' origin
    @param   w  Width of rectangle
    @param   h  Height of rectangle
*/
/**************************************************************************/
void Adafruit_ILI9341::setAddrWindow(uint16_t x, uint16_t y, uint16_t w, uint16_t h) {
    uint32_t xa = ((uint32_t)x << 16) | (x+w-1);
    uint32_t ya = ((uint32_t)y << 16) | (y+h-1);
    SPI2BUF = (ILI9341_CASET); // Column addr set
    SPI2BUF = (xa);
    SPI2BUF = (ILI9341_PASET); // Row addr set
    SPI2BUF = (ya);
    SPI2BUF = (ILI9341_RAMWR); // write to RAM
}

/**************************************************************************/
/*!
   @brief  Read 8 bits of data from ILI9341 configuration memory. NOT from RAM!
           This is highly undocumented/supported, it's really a hack but kinda works?
    @param    command  The command register to read data from
    @param    index  The byte index into the command to read from
    @return   Unsigned 8-bit data read from ILI9341 register
*/
/**************************************************************************/
uint8_t Adafruit_ILI9341::readcommand8(uint8_t command, uint8_t index) {
   // startWrite
   SPI2BUF = (0xD9);  
   SPI2BUF = (0x10 + index);
   SPI2BUF = (command);
   uint8_t r = SPI2BUF;
   
    return r;
}

void Adafruit_ILI9341::fillscreen()
{
    int x0 = 0;
    int x1 = 240;
    int y0 = 0;
    int y1 = 320;
    
    LATFCLR = _PORTF_RF8_MASK;
    
    for (int16_t i=0; i<240; i++) {
        int16_t steep = abs(y1 - y0) > abs(x1 - x0);

    int16_t dx, dy;
    dx = x1 - x0;
    dy = abs(y1 - y0);

    int16_t err = dx / 2;
    int16_t ystep;

    if (y0 < y1) {
        ystep = 1;
    } else {
        ystep = -1;
    }

    for (; x0<=x1; x0++) {
        if (steep) {
            SPI4BUF = 0x2C;
            SPI4BUF = 0xFF;
        } else {
            SPI4BUF = 0x2C;
            SPI4BUF = 0x88;
        }
        err -= dy;
        if (err < 0) {
            y0 += ystep;
            err += dx;
        }
    }
    }
    
    
    LATFSET = _PORTF_RF8_MASK;
}


