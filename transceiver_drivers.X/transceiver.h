#pragma once

void transceiver_spi_init(void);
void rfm_spiwrite(uint32_t c);
void tft_spiwrite16(uint32_t c);
uint32_t receiver_buffer(void);
void transmit_buffer(uint32_t data);
