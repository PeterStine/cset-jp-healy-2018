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
    
    
    void touch_hw_init();
    int touch_SPISend(uint8_t dataOut);
    int touch_getX();
    int touch_getY();


#ifdef	__cplusplus
}
#endif

#endif	/* TOUCH_DRIVER_H */

