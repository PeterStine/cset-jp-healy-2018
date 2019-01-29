
#ifndef _BUZZER_H    /* Guard against multiple inclusion */
#define _BUZZER_H

#define BUZZER_PIN PORTAbits.RA0
#define BUZZER_ACTIVE_STATE 0
#define BUZZER_INACTIVE_STATE 1

typedef struct {
    uint8_t BUZZER_ON;
    float BUZZER_DURATION;
    float BUZZER_TIME_REMAINING;
} BUZZER_DATA_T;

BUZZER_DATA_T BUZZER_DATA;

void PIEZO_INIT(void);
void PIEZO_BUZZER(uint8_t state, float duration);
BUZZER_DATA_T BUZZER_STATUS (void);
void __ISR_AT_VECTOR(_TIMER_2_VECTOR, IPL6SOFT) PIEZO_BUZZER_ISR(void);
#endif