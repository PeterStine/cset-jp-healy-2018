#ifndef _UART_H    /* Guard against multiple inclusion */
#define _UART_H

#define BUFFER_SIZE 40

typedef struct{
    uint8_t DATA[40]; // Stores 40 characters from UART
}UART_BUFFER_T;

char __attribute__((coherent)) UART_PUBLIC_BUFFER[BUFFER_SIZE] = { 0 };
char __attribute__((coherent)) UART_BUF[BUFFER_SIZE] = { 0 };

// Configures the UART and DMA module for character storage
void UART_CONFIG(void);
// Copies the current contents of the UART buffer into the public 40 Byte array,
// then returns the pointer to the beginning of this array.
uint8_t * UART_GET_BUFFER(void);


#endif 
