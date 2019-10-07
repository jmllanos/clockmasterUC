#include<ClockMaster.h>

// CLOCK MASTER CLASS
void ClockMaster::init()
{
   bool spi_ok;
   byte status;
   

   channel0.setNumber(0);
   channel1.setNumber(1);
   channel2.setNumber(2);
   channel3.setNumber(3);

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
 

   LCDRow1Index=0;
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


void ClockMaster::setChannel(char* data)
{   
    StaticJsonBuffer<400> jsonBuffer;
    JsonObject& _data = jsonBuffer.parseObject(data);
        
    int channel_number = (int) _data["channel"];
   

    ReplyMessage="{\"channel\":";

    DEBUG_CM_PRINTLN("**************");
   
    String tmp_str;
    tmp_str=String(channel_number);
    ReplyMessage+=tmp_str;
    
    switch(channel_number)
    {
        case 0:
            DEBUG_CM_PRINTLN("Setting channel 0");
            channel0.setParameters(_data);
           
            ReplyMessage+=channel0.getReplyMessage();
            break;
        case 1:
            DEBUG_CM_PRINTLN("Setting channel 1");
            channel1.setParameters(_data);
            
            ReplyMessage+=channel1.getReplyMessage();
            break;
        case 2:
            DEBUG_CM_PRINTLN("Setting channel 2");
            channel2.setParameters(_data);
            
            ReplyMessage+=channel2.getReplyMessage();
            break;
        case 3:
            DEBUG_CM_PRINTLN("Setting channel 3");
            channel3.setParameters(_data);
            
            ReplyMessage+=channel3.getReplyMessage();
            break;
        default:
          
            DEBUG_CM_PRINTLN("INVALID CHANNEL");
            ReplyMessage="{\"channel\":\"Invalid\"";
            break;

    }
    
    ReplyMessage+="}";
    
    DEBUG_CM_PRINTLN("**************");
}


String ClockMaster::getReplyMessage()
{
  return ReplyMessage;
}

void ClockMaster::reset()
{
}


