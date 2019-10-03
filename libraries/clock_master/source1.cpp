#include<ClockMaster.h>

// CLOCK MASTER CLASS
void ClockMaster::init()
{
   bool spi_ok;
   byte status;
   
   WRITE_REGISTER(CH_MUX_ENABLE,DISABLE_CHANNELS,spi_ok);
   
   DEBUG_CM_PRINTLN("*************************");
  
   if (spi_ok==true)
   {
    DEBUG_CM_PRINTLN("CLOCK MASTER DISABLE: "); 
   }
   else
   {
    DEBUG_CM_PRINTLN("SPI FAULT: ");
   }
  
   DEBUG_CM_PRINTLN("*************************");
}

void ClockMaster::getStatus()
{
 bool spi_ok;
 byte status;
 
 status=READ_REGISTER(CH_MUX_ENABLE,spi_ok);
 
 if(spi_ok==true)
 {
  if(status==ENABLE_CHANNElS)
  {
   ReplyMessage="{\"status\":\"Enable\"}";
  }
  else
  {
   ReplyMessage="{\"status\":\"Disable\"}";
  } 
 }

 else
 {
   ReplyMessage="{\"status\":\"SPI FAULT\"}";
 }
}

void ClockMaster::start()
{
  bool spi_ok;
  DEBUG_CM_PRINTLN("***************************************************");
  DEBUG_CM_PRINTLN("START METHOD");
  WRITE_REGISTER(CH_MUX_ENABLE,ENABLE_CHANNElS,spi_ok);
   
  if(spi_ok)
  {
   DEBUG_CM_PRINTLN("CLOCK MASTER CHANNELS DISABLE");
   ReplyMessage="{\"start\":\"ok\"}";
  }
  else
  {
   DEBUG_CM_PRINTLN("CLOCK MASTER SPI FAIL!!!!");
   ReplyMessage="{\"start\":\"SPI FAULT\"}";
  }
  
  DEBUG_CM_PRINTLN("***************************************************");
}

void ClockMaster::stop()
{
  bool spi_ok;
  DEBUG_CM_PRINTLN("***************************************************");
  DEBUG_CM_PRINTLN("START METHOD");
  WRITE_REGISTER(CH_MUX_ENABLE,DISABLE_CHANNELS,spi_ok);
  
  if(spi_ok)
  {
   DEBUG_CM_PRINTLN("CLOCK MASTER CHANNELS ENABLE");
   ReplyMessage="{\"stop\":\"ok\"}";
  }
  else
  {
   DEBUG_CM_PRINTLN("CLOCK MASTER SPI FAIL");
   ReplyMessage="{\"stop\":\"Fault\"}";
  }
  DEBUG_CM_PRINTLN("***************************************************");
}


void ClockMaster::setDivider(char* data)
{
  DEBUG_CM_PRINTLN("***********************");
  DEBUG_CM_PRINTLN("Setting Divider METHOD");
  PPSdiv.set_parameters(data);
  ReplyMessage=PPSdiv.get_ReplyMessage();

}


void ClockMaster::setPulsegen(char* data)
{
  DEBUG_CM_PRINTLN("***********************");
  DEBUG_CM_PRINTLN("Setting Pulse Generator METHOD");
  PulseGen.set_parameters(data);
  ReplyMessage= PulseGen.get_ReplyMessage();
}


String ClockMaster::getReplyMessage()
{
  return ReplyMessage;
}

void ClockMaster::reset()
{
/*  String reply;
  byte response[] = {0x0, 0x0, 0x0};
  //noInterrupts();
  DEBUG_CM_PRINTLN("***************************************************");
  DEBUG_CM_PRINTLN("Clock Master reset method:");


  DEBUG_CM_PRINTLN("Writing RESET register.");
  WRITE_REGISTER(RESET,0x00,response); // Reset chip

  if (CHECK_CORRECT_WRITING(response))
  {
   reply="{\"reset\":\"ok\"}";
  }
  else
  {
   reply="{\"reset\":\"spi fault\"}";
 }

return reply;
*/
}


