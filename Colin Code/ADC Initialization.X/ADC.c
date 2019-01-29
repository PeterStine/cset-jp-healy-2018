#include <xc.h>
#include <sys/attribs.h>
#include "ADC.h"

void ADC_Init(void) {
    
     /* Set up the CAL registers */
     AD1CAL1 = DEVADC1; // Copy the configuration data to the AD1CAL2 = DEVADC2;
     AD1CAL2 = DEVADC2;
     AD1CAL3 = DEVADC3;
     AD1CAL4 = DEVADC4;
     AD1CAL5 = DEVADC5;
     
     /* Configure AD1CON1 */
     AD1CON1 = 0;

     /* Configure AD1CON2 */
     AD1CON2 = 0;
     AD1CON2 = 0x4000; // Boost on
     AD1CON2bits.ADCSEL = 1; // 1 = SYSCLK, 2 REFCLK03, 3 FRC
     AD1CON2bits.ADCDIV = 4; // TQ = 1/200 MHz; Tad = 4* (TQ * 2) = 40 ns; 25 MHz ADC clock
     
     /* Configure AD1CON3 */
     AD1CON3 = 0; // ADINSEL is not configured for this example. VREFSEL of ?0?
    // selects AVDD and AVSS as the voltage reference.
     /* Configure AD1MOD */
     AD1IMOD = 0; // All channels configured for default input and single-ended
    // with unsigned output results.
     /* Configure AD1GIRGENx */
     AD1GIRQEN1 = 0; // No global interrupts are used.
     AD1GIRQEN2 = 0;
     /* Configure AD1CSSx */
     AD1CSS1 = 0; // No channel scanning is used.
     AD1CSS2 = 0;
     /* Configure AD1CMPCONx */
     AD1CMPCON1 = 0; // No digital comparators are used. Setting the AD1CMPCONx
     AD1CMPCON2 = 0; // register to 0 ensures that the comparator is disabled. Other
     AD1CMPCON3 = 0; // registers are dont care.
     AD1CMPCON4 = 0;
     AD1CMPCON5 = 0;
     AD1CMPCON6 = 0;
     
     /* Configure AD1FLTRx */
     AD1FLTR1 = 0; // No oversampling filters are used.
     AD1FLTR2 = 0;
     AD1FLTR3 = 0;
     AD1FLTR4 = 0;
     AD1FLTR5 = 0;
     AD1FLTR6 = 0;
     
     /* Set up the trigger sources */
     AD1TRG1 = 0; // Initialize all sources to no trigger.
     AD1TRG2 = 0;
     AD1TRG3 = 0;
     
     
     AD1TRG1bits.TRGSRC0 = 1; // Set AN0 to trigger from software.
     AD1TRG1bits.TRGSRC1 = 1; // Set AN1 to trigger from software.
     AD1TRG1bits.TRGSRC2 = 1; // Set AN2 to trigger from software.
     AD1TRG1bits.TRGSRC3 = 1; // Set AN3 to trigger from software.
     AD1TRG2bits.TRGSRC4 = 1; // Set AN4 to trigger from software.
     AD1TRG2bits.TRGSRC5 = 1; // Set AN5 to trigger from software.
     
     /* Turn the ADC on, start calibration */
     AD1CON1bits.ADCEN = 1;
     /* Wait for calibration to complete */
     while (AD1CON2bits.ADCRDY == 0);

     return;
}

uint16_t ADC_READ(uint8_t inputSel){
    
    uint16_t retVal = 0x0000;
    
    switch (inputSel){
        
        case 0:{
        
            if (AD1TRG1bits.TRGSRC0) {// If The input is under software trigger, trigger it. 
                /* Trigger a conversion */
                AD1CON3bits.GSWTRG = 1;
                /* Wait the conversions to complete */
                while (AD1DSTAT1bits.ARDY0 == 0);
                
            }
            retVal = AD1DATA0; // get data from encoder
        }
        case 1:{
        
            if (AD1TRG1bits.TRGSRC1) {// If The input is under software trigger, trigger it. 
                /* Trigger a conversion */
                AD1CON3bits.GSWTRG = 1;
                /* Wait the conversions to complete */
                while (AD1DSTAT1bits.ARDY1 == 0);
                
            }
            retVal = AD1DATA1; // get data from encoder
        }
        case 2:{
        
            if (AD1TRG1bits.TRGSRC2) {// If The input is under software trigger, trigger it. 
                /* Trigger a conversion */
                AD1CON3bits.GSWTRG = 1;
                /* Wait the conversions to complete */
                while (AD1DSTAT1bits.ARDY2 == 0);
                
            }
            retVal = AD1DATA2; // get data from encoder
        }
        case 3:{
        
            if (AD1TRG1bits.TRGSRC3) {// If The input is under software trigger, trigger it. 
                /* Trigger a conversion */
                AD1CON3bits.GSWTRG = 1;
                /* Wait the conversions to complete */
                while (AD1DSTAT1bits.ARDY3 == 0);
                
            }
            retVal = AD1DATA3; // get data from encoder
        }
        case 4:{
        
            if (AD1TRG2bits.TRGSRC4) {// If The input is under software trigger, trigger it. 
                /* Trigger a conversion */
                AD1CON3bits.GSWTRG = 1;
                /* Wait the conversions to complete */
                while (AD1DSTAT1bits.ARDY4 == 0);
                
            }
            retVal = AD1DATA4; // get data from encoder
        }
        case 5:{
        
            if (AD1TRG2bits.TRGSRC5) {// If The input is under software trigger, trigger it. 
                /* Trigger a conversion */
                AD1CON3bits.GSWTRG = 1;
                /* Wait the conversions to complete */
                while (AD1DSTAT1bits.ARDY5 == 0);
                
            }
            retVal = AD1DATA5; // get data from encoder
        }
    }
    
    return(retVal);
}