/* 
 * File:   Main.cpp
 * Author: Shaun Carter
 *
 * Created on January 25, 2019, 1:35 PM
 */

#include <cstdlib>
#include <stdio.h>
#include <xc.h>
using namespace std;

/*
 * 
 */
int main(int argc, char** argv) 
{
    int result[3];
    /* Set up the CAL registers */
    AD1CAL1 = DEVADC1; // Copy the configuration data to the AD1CAL2 = DEVADC2;
    // AD1CALx special function registers.
    AD1CAL3 = DEVADC3;
    AD1CAL4 = DEVADC4;
    //AD1CAL5 = DEVADC5; does not exist in efg144
    /* Configure AD1CON1 */
    AD1CON1 = 0; // No AD1CON1 features are enabled including: Stop-in-Idle, early
    // interrupt, filter delay Fractional mode and scan trigger source.

    /* Configure AD1CON2 */
    AD1CON2 = 0; // Boost, Low-power mode off, SAMC set to min, set up the ADC Clock
    AD1CON2bits.ADCSEL = 1; // 1 = SYSCLK, 2 REFCLK03, 3 FRC
    AD1CON2bits.ADCDIV = 4; // TQ = 1/200 MHz; Tad = 4* (TQ * 2) = 40 ns; 25 MHz ADC clock
    /* Configure AD1CON3 */
    AD1CON3 = 0; // ADINSEL is not configured for this example. VREFSEL of ?0?
    // selects AVDD and AVSS as the voltage reference.
    /* Configure AD1MOD */
    AD1MOD = 0; // All channels configured for default input and single-ended
    // with unsigned output results.
    /* Configure AD1GIRGENx */
    AD1GIRQEN1 = 0; // No global interrupts are used.
    AD1GIRQEN2 = 0;
    /* Configure AD1CSSx */
    AD1CSS1 = 0; // No channel scanning is used.
    AD1CSS2 = 0;
    /* Configure AD1CMPCONx */
    AD1CMPCON1 = 0; // No digital comparators are used. Setting the AD1CMPCONx
    AD1CMPCON2 = 0; // register to ?0? ensures that the comparator is disabled. Other
    AD1CMPCON3 = 0; // registers are ?don?t care?.
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
    /* Turn the ADC on, start calibration */
    AD1CON1bits.ADCEN = 1;
    /* Wait for calibration to complete */
    while (AD1CON2bits.ADCRDY == 0);
   
    while(1)
    {
        /* Trigger a conversion */
        AD1CON3bits.GSWTRG = 1;
        /* Wait the conversions to complete */
        while (AD1DSTAT1bits.ARDY0 == 0);
        /* fetch the result */
        result[0] = AD1DATA0;
        while (AD1DSTAT1bits.ARDY1 == 0);
        /* fetch the result */
        result[1] = AD1DATA1;
        while (AD1DSTAT1bits.ARDY2 == 0);
        /* fetch the result */
        result[2] = AD1DATA2;
    /*
    * Process results here
    *
    * Note 1: Loop time determines the sampling time since all inputs are Class 1.
    * A delay may be needed to meet sample time requirements.
    * Note 2: The first 5 samples may have reduced accuracy.
    *
    */
    }
    return 1;
}

