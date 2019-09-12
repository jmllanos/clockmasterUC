#include "read_write_registers.h"


void SendPacketSPI(byte address, byte buf_data, byte *resp)
{
  resp[0] = SPI.transfer(address);
  delayMicroseconds(SPI_DELAY);

  resp[1] = SPI.transfer(buf_data);
  delayMicroseconds(SPI_DELAY);

  bitClear(address, 7);
  SPI.transfer(address);
  delayMicroseconds(SPI_DELAY);

  resp[2] = SPI.transfer(0);
}

void READ_CONTROLLER_REGISTER(byte address, byte *resp)
{
  bitClear(address,7);//MSB define R/W, Preventing to write a register.
  SendPacketSPI(address,0x00,resp);
}

void WRITE_CONTROLLER_REGISTER(byte address, byte buf_data, byte *resp)
{
  bitSet(address,7);// MSB define R/W, set write
  SendPacketSPI(address,buf_data,resp);
}

bool CHECK_CORRECT_READING(byte *resp)
{
  bool correct_read=false;
  correct_read=(resp[0] == ACK_KEY);
  return correct_read;
}

bool CHECK_CORRECT_SEND_DATA(byte *resp)
{
  bool correct_write=false;
  correct_write= resp[0] == ACK_KEY &&
                 resp[1] == ACK_KEY;
  return correct_write;
}


