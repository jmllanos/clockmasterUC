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
  byte selector;
  SPIOKFlag=true;
  String tmp_mode = channel_data["mode"];
  
 
  if(tmp_mode=="pulsegen")
  {
     mode =tmp_mode;
     
     DEBUG_CM_PRINT("MODE: ");
     DEBUG_CM_PRINTLN(mode);
     
     PulseGen.set_parameters(channel_data);        
  // Setting Channel to PULSE GENERATOR  mode
     selector=READ_REGISTER(CH_MUX_SELECTOR,tmp);
     SPIOKFlag=SPIOKFlag & tmp;
    
     selector=bitSet(selector,channelNumber);
     WRITE_REGISTER(CH_MUX_SELECTOR,selector,tmp);
     SPIOKFlag=SPIOKFlag & tmp;
    
    ReplyMessage=",\"mode\":\"pulsegen\"";
    ReplyMessage+=PulseGen.get_ReplyMessage();
   
    SPIOKFlag=SPIOKFlag & PulseGen.get_spi_status();
  }    

  else if(tmp_mode=="divider" )
  {
     mode =tmp_mode;
    
    
     DEBUG_CM_PRINT("MODE: ");
     DEBUG_CM_PRINTLN(mode);
      
     PPSdiv.set_parameters(channel_data);
   // Setting Channel to DIVIDER mode
     selector=READ_REGISTER(CH_MUX_SELECTOR,tmp);
     SPIOKFlag=SPIOKFlag & tmp;
   
      selector=bitClear(selector,channelNumber);
      WRITE_REGISTER(CH_MUX_SELECTOR,selector,tmp);
      SPIOKFlag=SPIOKFlag & tmp;
   
       ReplyMessage=",\"mode\": \"divider\"";
       ReplyMessage+=PPSdiv.get_ReplyMessage();
 
      SPIOKFlag=SPIOKFlag & PPSdiv.get_spi_status();

  }

  else
  {
   DEBUG_CM_PRINTLN("MODE: invalid mode");

   ReplyMessage=",\"mode\":\"Invalid\"";
  }
}

bool Channel::getSPIStatus()
{
    return SPIOKFlag;
}

String Channel::getMode()
{
    return mode;
}

void Channel::getParameters()
{

    if(mode=="pulsegen")
    {
        PrintStr(0,1,"MODE:PULSEGEN");
        DEBUG_CM_PRINTLN("MODE:PULSEGEN");
        PulseGen.get_parameters();
    }
    else if(mode=="divider")
    {
        PrintStr(0,1,"MODE:PPSDIV");
        DEBUG_CM_PRINTLN("MODE:PPSDIV");
        PPSdiv.get_parameters();
    }
    else
    {
        DEBUG_CM_PRINTLN("MODE:XX");
        PrintStr(0,1,"MODE:XX");
    }


 
}

String Channel::getReplyMessage()
{
    return ReplyMessage;

}
