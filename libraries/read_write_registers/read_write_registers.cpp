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

byte READ_REGISTER(byte address, bool& SPI_OK)
{
  byte response[3];
  bitClear(address,7);//MSB define R/W, Preventing to write a register.
  SendPacketSPI(address,0x00,response);

  SPI_OK= response[0]==ACK_KEY;
 
  if(SPI_OK==false)
  {
      DEBUG_CM_PRINTLN("READING FAULT");
      DEBUG_CM_PRINTLN("SPI_FAULT");
  }
  
  return response[1];
}

void WRITE_REGISTER(byte address, byte buf_data, bool& SPI_OK)
{
  byte response[3];
  bitSet(address,7);// MSB define R/W, set write
  SendPacketSPI(address,buf_data,response);

  SPI_OK= response[0] == ACK_KEY &&
          response[1] == ACK_KEY;

  if(SPI_OK==false || response[2]!=buf_data)
  {
    SPI_OK=false;
    DEBUG_CM_PRINTLN("SPI FAULT");
    DEBUG_CM_PRINTLN("Fault WRITING");
    DEBUG_CM_PRINTLN("ADDRESS");
    DEBUG_CM_PRINTLN2(address, HEX);
  }

}


