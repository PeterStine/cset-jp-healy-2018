
#// Global Data variables used in conjunction with the app_clock file.
#//
#// Global variables
.global clock_second
.global clock_minute
.global clock_hour
.global clock_day
.global clock_month
.global clock_year
.global TIME_INIT
.global clock_state
.global clock_count
.global LCD_BUFFER

#// Variable declarations
.data
clock_count:		.word 0
clock_state:		.word 0
clock_second:		.word 53
clock_minute:		.word 59
clock_hour:		.word 9
clock_day:		.word 1
clock_month:		.word 1
clock_year:		.space 65
TIME_INIT:		.asciiz "Time:    :  : "
LCD_BUFFER:		.space 20

#//
#// Global Data variables used in conjunction with the app_clock file.


