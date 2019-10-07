#include <Channel.h>

void Channel::setNumber(int _channelNumber)
{
  if(_channelNumber<=NumberOfChannels-1)
  {
   channelNumber=_channelNumber;
   PPSdiv.set_channel(channelNumber);
   PulseGen.set_channel(channelNumber);
  }
}

void Channel::setParameters(JsonObject& channel_data)
{
  bool tmp;
  bool SPI_ok=true;
  byte selector;

  String tmp_mode = channel_data["mode"];
  
 
  if(tmp_mode=="pulsegen")
  {
     mode =tmp_mode;
     
     DEBUG_CM_PRINT("MODE: ");
     DEBUG_CM_PRINTLN(mode);
     
     PulseGen.set_parameters(channel_data);        
  // Setting Channel to PULSE GENERATOR  mode
     selector=READ_REGISTER(CH_MUX_SELECTOR,tmp);
     SPI_ok=SPI_ok & tmp;
    
     selector=bitSet(selector,channelNumber);
     WRITE_REGISTER(CH_MUX_SELECTOR,selector,tmp);
     SPI_ok=SPI_ok & tmp;
    
    ReplyMessage=",\"mode\":";
    ReplyMessage+=mode;
    ReplyMessage+=PulseGen.get_ReplyMessage();
    
  }    

  else if(tmp_mode =="divider" )
  {
     mode =tmp_mode;
    
     DEBUG_CM_PRINT("MODE: ");
     DEBUG_CM_PRINTLN(mode);
  
   PPSdiv.set_parameters(channel_data);
  
   // Setting Channel to DIVIDER mode
   selector=READ_REGISTER(CH_MUX_SELECTOR,tmp);
   SPI_ok=SPI_ok & tmp;
   
   selector=bitClear(selector,channelNumber);
   WRITE_REGISTER(CH_MUX_SELECTOR,selector,tmp);
   SPI_ok=SPI_ok & tmp;
   
   ReplyMessage=",\"mode\":";
   ReplyMessage+=mode;
   ReplyMessage+=PPSdiv.get_ReplyMessage();
  
  }
  else
  {
   DEBUG_CM_PRINTLN("MODE: invalid mode");

   ReplyMessage=",\"mode\":\"invalid\"";
  }
}

String Channel::getMode()
{
    return mode;
}

String Channel::getReplyMessage()
{
    return ReplyMessage;

}
