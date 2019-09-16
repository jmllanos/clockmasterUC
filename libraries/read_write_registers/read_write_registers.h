#ifndef _read_write_registers_h_included
#define _read_write_registers_h_included

#include <Arduino.h>
#include <SPI.h>
#include "TIVAConfiguration.h"
#include "ClockMasterRegisters.h"

void SendPacketSPI(byte address, byte buf_data, byte *resp);

void READ_CONTROLLER_REGISTER(byte address, byte *resp);

void WRITE_CONTROLLER_REGISTER(byte address, byte buf_data, byte *resp);

bool CHECK_CORRECT_READING(byte *resp);

bool CHECK_CORRECT_SEND_DATA(byte *resp);

#endif
