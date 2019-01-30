#ifndef _ULTRASONIC_H
#define _ULTRASONIC_H

uint8_t UART_BUFFER[8];

// Initialized UART, and enables DMA transfers to the UART_BUFFER array.
int UART_INIT(void);



#endif