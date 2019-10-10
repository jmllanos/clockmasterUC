#ifndef _read_write_registers_h_included
#define _read_write_registers_h_included

#include <Arduino.h>
#include <SPI.h>
#include "TIVAConfiguration.h"
#include "ClockMasterRegisters.h"

void SendPacketSPI(byte address, byte buf_data, byte *resp);

byte READ_REGISTER(byte address, bool& SPI_OK);

void WRITE_REGISTER(byte address, byte buf_data, bool& SPI_OK);

#endif
