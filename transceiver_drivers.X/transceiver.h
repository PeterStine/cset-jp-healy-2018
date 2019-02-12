#pragma once

void transceiver_spi_init(void);
void rfm_spiwrite16_raw(uint16_t c);
void rfm_spiwrite_single_access(uint8_t mode, uint8_t addr, uint8_t data);
void tft_spiwrite16(uint32_t c);
uint32_t receiver_buffer(void);
void transmit_buffer(uint32_t data);