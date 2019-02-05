/* 
 * File:   Touch_Driver.h
 * Author: kjfrischman
 *
 * Created on January 18, 2019, 2:35 PM
 */

#ifndef TOUCH_DRIVER_H
#define	TOUCH_DRIVER_H

#ifdef	__cplusplus
extern "C" {
#endif

#define TINIT 0x90
#define LCD_W 240
#define LCD_H 320  
#define Xmin 0
#define Xmax 240
#define Ymin 0
#define Ymax 300
#define T_SAMPLES 7
    
    
#include <xc.h>
#include <sys/attribs.h>
       
    void touch_hw_init();
    void DrawScreen();
    void touch_Calibration();
    void touch_GetCoords(int * xOut, int * yOut);
    uint8_t touch_GetAverage(int * xOut, int * yOut, int numSamples);
    uint8_t touch_GetRaw();
    int touch_SPISend(uint8_t dataOut);
    int touch_getX();
    int touch_getY();


#ifdef	__cplusplus
}
#endif

#endif	/* TOUCH_DRIVER_H */

