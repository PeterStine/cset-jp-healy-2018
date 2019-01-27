#include <xc.h>
#include <sys/attribs.h>

#include <stdint.h>

#define u32 uint32_t
#define u8 uint8_t

// PIC32MZ2048ECG144 Configuration Bit Settings
// DEVCFG2
#pragma config FPLLIDIV = DIV_2         // System PLL Input Divider (2x Divider) 12MHz/2 = 6MHz
#pragma config FPLLRNG = RANGE_5_10_MHZ // System PLL Input Range (5-10 MHz Input)
#pragma config FPLLICLK = PLL_POSC      // System PLL Input Clock Selection (POSC is input to the System PLL)
#pragma config FPLLMULT = MUL_112       // System PLL Multiplier (PLL Multiply by 112) 6MHz * 112 = 672MHz
#pragma config FPLLODIV = DIV_8         // System PLL Output Clock Divider (8x Divider) 672MHz / 8 = 84MHz
#pragma config UPLLFSEL = FREQ_12MHZ    // USB PLL Input Frequency Selection (USB PLL input is 12 MHz)
#pragma config UPLLEN = OFF             // USB PLL Enable (USB PLL is disabled)

// DEVCFG1
#pragma config FNOSC = SPLL             // Oscillator Selection Bits (Primary Osc (HS,EC))
#pragma config FSOSCEN = OFF            // Secondary Oscillator Enable (Disable SOSC)
#pragma config POSCMOD = HS             // Primary Oscillator Configuration (HS osc mode)
#pragma config FCKSM = CSDCMD           // Clock Switching and Monitor Selection (Clock Switch Disabled, FSCM Disabled)
#pragma config FWDTEN = OFF             // Watchdog Timer Enable (WDT Disabled)
#pragma config FDMTEN = OFF             // Deadman Timer Enable (Deadman Timer is disabled)

// DEVCFG0
#pragma config JTAGEN = OFF             // JTAG Enable (JTAG Disabled)
#pragma config ICESEL = ICS_PGx2        // ICE/ICD Comm Channel Select (Communicate on PGEC2/PGED2)


int main(int argc, char** argv) {
    int result[3];
     /* Set up the CAL registers */
     AD1CAL1 = DEVADC1; // Copy the configuration data to the AD1CAL2 = DEVADC2;
    // AD1CALx special function registers.
     AD1CAL3 = DEVADC3;
     AD1CAL4 = DEVADC4;
     AD1CAL5 = DEVADC5;
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
     
    while (1) {
    /* Trigger a conversion */
    AD1CON3bits.GSWTRG = 1;
    /* Wait the conversions to complete */
    while (AD1DSTAT1bits.ARDY0 == 0);
    /* fetch the result */
    result[0] = AD1DATA0;
  
    int i = 0;
    while (i < 90000) { i++; asm("nop"); }
    /*
   * Process results here
   *
   * Note 1: Loop time determines the sampling time since all inputs are Class 1.
   * A delay may be needed to meet sample time requirements.
   * Note 2: The first 5 samples may have reduced accuracy.
   *
   */
    }
   return (1);
   }