

#include "Touch_Driver.h"

    int cal_x = 0; 
    int cal_y = 0;
    int raw_x = 0;
    int raw_y = 0;

void touch_hw_init()
{
    LATFbits.LATF5 = 1;
    TRISFbits.TRISF5 = 0;
    
    //Set Chip Select Low
    LATFCLR = _PORTF_RF5_MASK;
    
    //Setup IRQ Pin
    TRISFbits.TRISF4 = 1;
    CNENFbits.CNIEF4 = 1;
    IFS3bits.CNFIF = 0;
    CNPUFbits.CNPUF4=1;// Enable push up. 
    IEC3bits.CNFIE = 1;
    IPC30bits.CNFIP = 6;
    //Detect Low Voltage
    CNCONFbits.EDGEDETECT = 0;
    CNCONFbits.ON = 1;
    //IFS3
    //Set Chip Select High
    LATFSET = _PORTF_RF5_MASK;
    
    //Send Init Byte (0x90)
    touch_SPISend(TINIT);
    
    //Calibrate Screen
    touch_Calibration();
}

int touch_SPISend(uint8_t dataOut)
{
    int toReturn = 0;
    
    
    //Set Chip Select Low
    LATFCLR = _PORTF_RF5_MASK;
  
    //Write data
    SPI4BUF = dataOut;
    while (SPI4STATbits.SPIBUSY);
    SPI4BUF = 0;
    while (SPI4STATbits.SPIBUSY);
    //delay_ms(2);
    toReturn = SPI4BUF;
    
    
    LATFSET = _PORTF_RF5_MASK;
    
    return toReturn;
}



void touch_Calibration()
{
    cal_x = (3968-255) / LCD_W;
    cal_y = (3775-200) / LCD_H;
}

void touch_GetCoords(int * xOut, int * yOut)
{
    int allX[T_SAMPLES];
    int allY[T_SAMPLES];
    int count = 0;
    int count2 = 0;
    
    //Send Request for Coords
    touch_SPISend(0xD1);
    touch_SPISend(0x91);
    
    for (count = 0; count < T_SAMPLES; count++)
    {
        allX[count] = touch_SPISend(0xD1);
        allY[count] = touch_SPISend(0x91);
    }
    
	for ( count = 0 ; count < 4 ; count ++ ) {
		for ( count2 = count ; count2 < 7 ; count2 ++ ) {
			int temp = allX[ count ];
			if ( temp > allX[ count2 ] ) {
				allX[ count ] = allX[ count2 ];
				allX[ count2 ] = temp;
			}
			temp = allY[ count ];
			if ( temp > allY[ count2 ] ) {
				allY[ count ] = allY[ count2 ];
				allY[ count2 ] = temp;
			}
		}
	}
	touch_SPISend( 0x90 );

	*xOut = allX[ 3 ];
	*yOut = allY[ 3 ];
    
    
}

uint8_t touch_GetAverage(int * xOut, int * yOut, int numSamples)
{
    int x = 0;
    int y = 0;
    int numRead = 0;
    int xAcc = 0; 
    int yAcc = 0;
    
    for (; numRead < numSamples; numRead++)
    {
        if (!PORTFbits.RF4)
        {
            touch_GetCoords(&x, &y);
            
            xAcc += x;
            yAcc += y;
            
        }
    }
    
    *xOut = xAcc / numSamples;
    *yOut = yAcc / numSamples;
    
}

uint8_t touch_GetRaw()
{
    int x = 0; 
    int y = 0;
    int valid = touch_GetAverage(&x, &y, 5);
    
    if (valid)
    {
        raw_x = (x - 255) / cal_x;
        raw_y = (y - 200) / cal_y;
    }
    
    return valid;
}

void DrawScreen()
{
    int x = 0;
    int y = 0;
    
    touch_GetCoords(&x, &y);
    
    if (y > 15 && y < 300)
    {
        tft_drawCircle(x, y, 5 ,0xFFFF);
    }
}

//Touch ISR
void __ISR_AT_VECTOR(_CHANGE_NOTICE_F_VECTOR, IPL7SOFT) TOUCHCHISR(void)
{
    DrawScreen();
    //Clear interrrupt
    PORTF;
    IFS3bits.CNFIF = 0;
}