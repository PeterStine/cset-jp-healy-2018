#include <xc.h>
#include <sys/attribs.h>
#include "BUZZER.h"


void PIEZO_INIT(void) {
    
    asm("di");
    SYSKEY = 0;
    SYSKEY = 0xAA996655;
    SYSKEY = 0x556699AA;
    PB3DIVSET = 0x107F; // Divide by 128 (656,250 Hz))
    SYSKEY = 0;
    asm("ei");
    
    BUZZER_DATA.BUZZER_DURATION = 0.0;
    BUZZER_DATA.BUZZER_ON = 0;
    BUZZER_DATA.BUZZER_TIME_REMAINING = 0.0;
    
    T2CON = 0;
    T2CONSET = 0x30; // Set prescale = 1:256, 656,250 / 1 = 2,563 Hz
    
    IEC0SET = 0x200; // Enable Timer 2 interrupt
    
}
/*
void PIEZO_BUZZER(uint8_t state, float duration) {
  
    BUZZER_DATA.BUZZER_DURATION = duration;
    BUZZER_DATA.BUZZER_ON = state;
    
    if (state > 0) { // Buzzer set to active
        
        BUZZER_PIN = BUZZER_ACTIVE_STATE; // activate buzzer
        
        PR2 = duration * 2563; // Set timer to trigger interrupt after duration
        T2CONSET = 0x8000; // Turn Timer 2 on
    }
    else { // Buzzer set to inactive
        
        BUZZER_PIN = BUZZER_INACTIVE_STATE;
    }
    
}

void __ISR_AT_VECTOR(_TIMER_2_VECTOR, IPL6SOFT) PIEZO_BUZZER_ISR(void){
    
    T2CONCLR = 0x8000; // Turn timer 2 off
    PR2 = 0x0; // Clear count value
    
    BUZZER_DATA.BUZZER_TIME_REMAINING = 0.0;
    
    BUZZER_PIN = BUZZER_INACTIVE_STATE;   
}

BUZZER_DATA_T BUZZER_STATUS(void) {
    
    // Calculate the remaining time, and return the status data
    if (T2CON & 0x8000){
        BUZZER_DATA.BUZZER_TIME_REMAINING = BUZZER_DATA.BUZZER_DURATION - ((float)PR2 / 2563);
    }
    else {
        BUZZER_DATA.BUZZER_TIME_REMAINING = 0.0;
    }
    
    return (BUZZER_DATA);
}
 */