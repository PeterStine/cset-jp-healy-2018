
#ifndef RTC2_H
#define RTC2_H

#define HOUR_POS    0x87
#define MIN_POS     0x8A
#define SEC_POS     0x8D

#define LED_TRIS    TRISHbits.TRISH2    // macro for direction register bit of the LED pin
#define LED_LAT     LATHbits.LATH2      // macro for output register bit of the LED pin

extern int clock_count;
extern int clock_state;
extern int clock_second;
extern int clock_minute;
extern int clock_hour;
extern int clock_day;
extern int clock_month;
extern long long clock_year;

extern char TIME_INIT[20];

void    lcd_time_init(void);

void clock_day_inc(void);
void clock_month_inc(void);
void clockfield_to_lcdstr (int clockfield, int field_type);
void clock_init(void);
void timer_config(void);
void app_clock(void);
void TimeUpdate(short x, short y, short w, short h);

#endif