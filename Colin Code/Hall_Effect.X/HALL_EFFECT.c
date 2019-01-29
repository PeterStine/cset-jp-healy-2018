#include "HALL_EFFECT.h"



void HALL_EFFECT_INIT (void) {
    
    HALL_EFFECT_DATA.FLOW_RATE = 0.0;
    HALL_EFFECT_DATA.FLOW_RATE_DELTA = 0.0;
    
    // Set PB3CLK
    asm("di");
    SYSKEY = 0;
    SYSKEY = 0xAA996655;
    SYSKEY = 0x556699AA;
    PB3DIVSET = 0x107F; // Divide by 128 (656,250 Hz))
    SYSKEY = 0;
    asm("ei");
    
    T1CON = 0;
    T1CONCLR = 0x30; // Set prescale = 1:1, 656,250 / 1 = 656,250 Hz
    
    INTCONSET = 0x1; // Set external interrupt 0 to rising edge
    
}

HALL_EFFECT_DATA_T HALL_EFFECT_GET_FREQ (void);

// External interrupt source 0 is on RPD0
void __ISR_AT_VECTOR(_EXTERNAL_0_VECTOR, IPL7SRS) HALL_EFFECT_ISR(void){
    
    T1CONCLR = 0x8000; // Turn timer 1 off
    TMR_DELTA = TMR1; // Store the timer delta
    PR1 = 0; // Reset TMR1 count value
    
    // Find the hall effect period, then invert to get freq, then divide by 6.6
    // to get the flow rate in L/Min.
    HALL_EFFECT_DATA.FLOW_RATE = (float)( (1.0 / ((float)TMR_DELTA / 656250)) / 6.6 ); 
    
    // Find the delta by subtracting the previous rate from the current one
    HALL_EFFECT_DATA.FLOW_RATE_DELTA = HALL_EFFECT_DATA.FLOW_RATE - PREV_FLOW_RATE;
    
    PREV_FLOW_RATE = HALL_EFFECT_DATA.FLOW_RATE; // Save current rate to use next time as previous
    
    T1CONSET = 0x8000; // Turn timer 1 on
}