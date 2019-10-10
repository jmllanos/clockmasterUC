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
  byte resp[3];
  bitClear(address,7);//MSB define R/W, Preventing to write a register.
  SendPacketSPI(address,0x00,resp);

  SPI_OK= resp[0]==ACK_KEY;
  
  if(SPI_OK==false)
  {
     DEBUG_CM_PRINTLN("READING FAULT");
     DEBUG_CM_PRINTLN("SPI_FAULT");
  }
  
  return resp[1];
}

void WRITE_REGISTER(byte address, byte buf_data, bool& SPI_OK)
{
  byte res[3];
  bitSet(address,7);// MSB define R/W, set write
  SendPacketSPI(address,buf_data,res);

  SPI_OK= (res[0] == ACK_KEY &&
           res[1] == ACK_KEY);
  
  if(SPI_OK==false || res[2]!=buf_data)
  {
         SPI_OK=false;
         DEBUG_CM_PRINTLN("SPI FAULT");
         DEBUG_CM_PRINTLN("Fault WRITING");
         DEBUG_CM_PRINTLN("ADDRESS");
         DEBUG_CM_PRINTLN2(bitClear(address,7), HEX);
         DEBUG_CM_PRINTLN("data written");
         DEBUG_CM_PRINTLN2(buf_data,HEX);
         DEBUG_CM_PRINTLN("data readed");
         DEBUG_CM_PRINTLN2(res[2],HEX);
   }
}


