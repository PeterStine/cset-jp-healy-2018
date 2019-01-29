
#ifndef _HALL_EFFECT_H    /* Guard against multiple inclusion */
#define _HALL_EFFECT_H

#include <xc.h>
#include <sys/attribs.h>

typedef struct{
    float FLOW_RATE; // Flow rate of sensor in L/Min
    float FLOW_RATE_DELTA; // Change in flow rate
}HALL_EFFECT_DATA_T;

HALL_EFFECT_DATA_T HALL_EFFECT_DATA;

uint32_t TMR_DELTA = 0; // difference between last edge and the current one
float PREV_FLOW_RATE;

// Frequency = 6.6 * Q. (Q = L/Min)
// Max frequency = 30 L/Min * 6.6 = 198 Hz

void HALL_EFFECT_INIT (void);
HALL_EFFECT_DATA_T HALL_EFFECT_GET_FREQ (void);
void __ISR_AT_VECTOR(_EXTERNAL_0_VECTOR, IPL7SRS) HALL_EFFECT_ISR(void);


#endif 

