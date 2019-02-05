//Kyle Frischman
//Junior Project 


#include <xc.h>
#include <sys/attribs.h>
#include "RTC2.h"


#include "GFX/tft_master.h"
#include "GFX/tft_gfx.h"


#define LCD_Color ILI9340_GREY
#define LCD_TXT ILI9340_WHITE 
#define LCD_Width 240
#define Time_H 12
#define TIME_SPACE 12
#define LCD_SEC 170
#define LCD_MIN 150
#define LCD_HR 130
#define LCD_DAY 70
#define LCD_MTH 50
#define LCD_YR 30


char buffer[20];
extern char TIME_INIT[20];

void app_clock(void)
{
    if (clock_count < 200)
    {
        clock_count++;
    }
    else
    {
        clock_count = 0;
    }
    
     switch (clock_state)
     {
         case 0:
             if (clock_count == 200)
             {
                //New Year
                if (clock_second >= 59 && clock_minute >= 59 && clock_hour >= 24 && clock_month >= 12 && clock_day >= 31)
                {
                    clock_second = 0;
                    clock_minute = 0;
                    clock_hour = 0;
                    clock_day = 1;
                    clock_month = 1;
                    clock_year++;
                    clock_state = 6;
                }
                //New Month
                else if (clock_second >= 59 && clock_minute >= 59 && clock_hour >= 24 && clock_day >= 28)
                {
                    switch(clock_month)
                    {
                        case 0:
                            //Error State
                            //Throw An Error
                        break; 
                        
                        case 1:
                            //January 31 Days
                            if (clock_day == 31)
                            {
                                clock_month_inc();
                            }
                            else
                            {
                                clock_day_inc();
                            }
                        break;    
                        
                        case 2:
                            //Check Leap Year
                            if (clock_year % 4)
                            {
                                if (clock_day == 29)
                                {
                                    clock_month_inc();
                                }
                                else
                                {
                                    clock_day_inc();
                                }
                            }
                            else
                            {
                                //28 Days
                                clock_month_inc();
                            }
                        break; 
                        
                        case 3:
                            //March 31 Days
                            if (clock_day == 31)
                            {
                                clock_month_inc();
                            }
                            else
                            {
                                clock_day_inc();
                            }
                        break; 
                        
                        case 4:
                            //April 30 Days
                            if (clock_day == 30)
                            {
                                clock_month_inc();
                            }
                            else
                            {
                                clock_day_inc();
                            }
                        break; 
                        
                        case 5:
                            //May 31 Days
                            if (clock_day == 31)
                            {
                                clock_month_inc();
                            }
                            else
                            {
                                clock_day_inc();
                            }
                        break; 
                        
                        case 6:
                            //June 30
                            if (clock_day == 30)
                            {
                                clock_month_inc();
                            }
                            else
                            {
                                clock_day_inc();
                            }
                        break; 
                        
                        case 7:
                            //July 31
                            if (clock_day == 31)
                            {
                                clock_month_inc();
                            }
                            else
                            {
                                clock_day_inc();
                            }
                        break;
                        
                        case 8:
                            //August 31
                            if (clock_day == 31)
                            {
                                clock_month_inc();
                            }
                            else
                            {
                                clock_day_inc();
                            }
                        break; 
                        
                        case 9:
                            //September 30
                            if (clock_day == 30)
                            {
                                clock_month_inc();
                            }
                            else
                            {
                                clock_day_inc();
                            }
                        break; 
                        
                        case 10:
                            //October 31
                            if (clock_day == 31)
                            {
                                clock_month_inc();
                            }
                            else
                            {
                                clock_day_inc();
                            }
                        break; 
                        
                        case 11:
                            //November 30
                            if (clock_day == 30)
                            {
                                clock_month_inc();
                            }
                            else
                            {
                                clock_day_inc();
                            }
                        break; 
                        
                        case 12:
                            //December ? Error State?
                        break; 
                    }
             
                }
                //New Day
                else if (clock_second >= 59 && clock_minute >= 59 && clock_hour >= 24)
                 {
                    clock_day_inc();
                 }
                //New Hour
                else if (clock_second >= 59 && clock_minute >= 59)
                {
                    clock_second = 0;
                    clock_minute = 0;
                    clock_hour++;
                    clock_state = 3;
                }
                //New Minute
                else if (clock_second >= 59)
                {
                    clock_second = 0;
                    clock_minute++;
                    clock_state = 2;
                }
                //New Second
                else
                {
                    clock_second++;
                    clock_state = 1;
                }
             }
             break;
        
         case 1:
            //Return to State 0
            clock_state = 0;
            //Set Seconds
            clockfield_to_lcdstr(clock_second, 1);
            //Blink LED
            LED_LAT = !LED_LAT;
            //Write Current Second Value
            TimeUpdate(LCD_SEC, 0, TIME_SPACE, Time_H);
    
             break;
             
         case 2:
             //Update Minute Display
             //Set Minutes
            clockfield_to_lcdstr(clock_minute, 1);
            //Write Current Minute Value
             TimeUpdate(LCD_MIN, 0, TIME_SPACE, Time_H);
             
             //Go To State 1
             clock_state = 1;
             break;
             
             
         case 3:
             //Update Hour Display
             //Set Hours
            clockfield_to_lcdstr(clock_hour, 0);
            //Move Cursor To Hour Position (0x86)
            TimeUpdate(LCD_HR, 0, TIME_SPACE, Time_H);
            
            //Go To State 2
            clock_state = 2;
            break;
             
        case 4:
             //Update Day
            clockfield_to_lcdstr(clock_day, 0);
            //Write Current Day
            TimeUpdate(LCD_DAY, 0, TIME_SPACE, Time_H);
            
            //Go To State 3
            clock_state = 3;
            break;
             
             
        case 5:
             //Update Month
            clockfield_to_lcdstr(clock_month, 0);
            //Set Month
            TimeUpdate(LCD_MTH, 0, TIME_SPACE, Time_H);
            
            //Go To State 4
            clock_state = 4;
            break;
             
             
        case 6:
            //Update Year
            clockfield_to_lcdstr(clock_year, 0);
            //Set Year
            TimeUpdate(LCD_YR, 0, TIME_SPACE, Time_H);
            
            //Go To State 5
            clock_state = 5;
            break;     
     }
     
}

void clock_day_inc (void)
{
    clock_second = 0;
    clock_minute = 0;
    clock_hour = 1;
    clock_day++;
    clock_state = 4;
}

void clock_month_inc (void)
{
    clock_second = 0;
    clock_minute = 0;
    clock_hour = 1;
    clock_day = 1;
    clock_month++;
    clock_state = 5;
}

void lcd_time_init (void)
{
    //MUST be called AFTER LCD_Init
    //Set 'Time:    :  :  '
    
    tft_fillRect(0,0,240,12,LCD_Color );
    
    tft_setCursor(0, 0);
    tft_setTextColor(LCD_TXT );  
    tft_setTextSize(1);
    tft_writeString(TIME_INIT);
    
    //Set Month
    tft_setCursor(LCD_MTH, 0);
    clockfield_to_lcdstr(clock_month, 1);
    tft_writeString(buffer);
    
    //Set Day
    tft_setCursor(LCD_DAY, 0);
    clockfield_to_lcdstr(clock_day, 1);
    tft_writeString(buffer);
    
    //Set Year
    tft_setCursor(LCD_YR, 0);
    clockfield_to_lcdstr(clock_year, 1);
    tft_writeString(buffer);
    
    //Set Hours
    clockfield_to_lcdstr(clock_hour, 0);
    //Move Cursor To Hour Position (0x86)
    tft_setCursor(LCD_HR, 0);
    tft_writeString(buffer);
    
    //Set Minutes
    clockfield_to_lcdstr(clock_minute, 1);
    //Move Cursor To Minute Position (0x10)
    tft_setCursor(LCD_MIN, 0);
    tft_writeString(buffer);
    
    //Set Seconds
    clockfield_to_lcdstr(clock_second, 1);
    //Move Cursor To Second Position (0x13)
    tft_setCursor(LCD_SEC , 0);
    tft_writeString(buffer);
}

void clockfield_to_lcdstr (int clockfield, int field_type)
{
    //Convert Values
    int temp = 0;
    
    temp = clockfield % 10;
    clockfield = clockfield / 10;
    if (clockfield == 0 && field_type == 0)
    {
        clockfield = 0x20;
    }
    else
    {
        clockfield += 0x30;
    }
    
    temp += 0x30;
    
    //Place In Buffer
    buffer[0] = clockfield;
    buffer[1] = temp;
    buffer[2] = '\n';
    
    //Return
}

void clock_init(void)
{
    //Set Year
    clock_year = 19;
    //Set Month
    clock_month = 1;        
    //Set Day
    clock_day = 11;
    //Set Hour
    clock_hour = 14;
    //Set Minute
    clock_minute = 1;
    //Set Second
    clock_second = 1;
}

//Timer 1 Config
void timer_config(void)
{
    //Turn off Timer 2, CLR Interrupt Flag (IFS0 Bit 9)
    T2CONCLR = 0x8000;
    IFS0CLR = _IFS0_T2IF_MASK;
    IEC0CLR = _IEC0_T2IE_MASK;
    
    //Timer 2 1:4, Roll Over, 13036 = Interrupt
    T2CONSET = 0x50;
    PR2 = 13036;
    
    //Set Timer 2 Priority to 4
    IPC2SET = 0x1000;
    
}

//Timer 1 ISR
void __ISR_AT_VECTOR(_TIMER_2_VECTOR, IPL4SOFT) TIMER1Handler(void)
{
    //Clear Flag
    IFS0bits.T2IF = 0;
    //Call Real Time Clock
    app_clock();
}

//Time Change Function
void TimeUpdate(short x, short y, short w, short h)
{
    tft_fillRect(x,y,w,h,LCD_Color ); 
    tft_setTextColor(LCD_TXT); 
    tft_setCursor(x, 0);
    tft_writeString(buffer);
}