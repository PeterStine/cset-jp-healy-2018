
#ifndef _ADC_H    /* Guard against multiple inclusion */
#define _ADC_H

typedef struct {
    
    uint8_t on : 1;
    uint8_t numInput : 3;
    uint8_t reserved : 4;
    
}ADC_STATUS;

// numInput: number of ADC inputs to initialize
void ADC_Init(void);
uint16_t ADC_READ(uint8_t inputSel);
//uint8_t ADC_GET_STATUS(void);

// The ADC encodes in 12 bits, so 16 bit ints are used within the data array
// There are 6 dedicated S&H, and encoders, so the array holds 6 values.
uint16_t ADC_DATA[6] = { 0 }; // Global ADC data array

ADC_STATUS ADC_STATUS_BYTE = 0; // Stores ADC status information


#endif /* _EXAMPLE_FILE_NAME_H */
