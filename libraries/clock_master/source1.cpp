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
    strStatus="DISABLE";
   }
   else
   {
    DEBUG_CM_PRINTLN("SPI FAULT: ");
    strStatus="SPI FAIL";
   }
 

   LCDRowIndex=0;
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
   
   strStatus="ENABLE";
  }
  else
  {
   ReplyMessage="{\"status\":\"Disable\"}";
   strStatus="DISABLE";
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
   DEBUG_CM_PRINTLN("CLOCK MASTER CHANNELS ENABLE");
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

void ClockMaster::reset()
{
  DEBUG_CM_PRINTLN("***************************************************");
  DEBUG_CM_PRINTLN("RESET METHOD");
  digitalWrite(PL_2,HIGH);
  digitalWrite(PL_2,LOW);
  DEBUG_CM_PRINTLN("...");//corroborar reset......................................................
  ReplyMessage="{\"reset\":\"ok\"}";
  DEBUG_CM_PRINTLN("***************************************************");
}

void ClockMaster::setChannel(char* data)
{  
    bool invalidflag=false;
    
    SPIStatus=true;

    StaticJsonBuffer<800> jsonBuffer;
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
            SPIStatus=channel0.getSPIStatus();
            ReplyMessage+=channel0.getReplyMessage();

            break;
        case 1:
            DEBUG_CM_PRINTLN("Setting channel 1");
            channel1.setParameters(_data);
            
            SPIStatus=channel1.getSPIStatus();
            ReplyMessage+=channel1.getReplyMessage();
            break;
        case 2:
            DEBUG_CM_PRINTLN("Setting channel 2");
            channel2.setParameters(_data);
            
            SPIStatus=channel2.getSPIStatus();
            ReplyMessage+=channel2.getReplyMessage();
            break;
        case 3:
            DEBUG_CM_PRINTLN("Setting channel 3");
            channel3.setParameters(_data);
            
            SPIStatus=channel3.getSPIStatus();
            ReplyMessage+=channel3.getReplyMessage();
            break;
        default:

            invalidflag=true;      
            DEBUG_CM_PRINTLN("INVALID CHANNEL");
            ReplyMessage="{\"channel\":\"Invalid\"";
            break;

    }
   
     tft.setTextColor(BACKGROUND); 
     tft.setCursor(0,0);
     tft.println(lcdmessage);
     
        
    if(SPIStatus==false & invalidflag==false)
    {
     ReplyMessage+=",\"SPI\":\"Fault\"";
     lcdmessage="WRITE FAuLT";
    }
    else
    {
      lcdmessage="WRITE DONE";
    }
     
    ReplyMessage+="}";
    
       
    tft.setTextColor(TEXTCOLOR);
    tft.setCursor(50,80);
    tft.println(lcdmessage);
    
    DEBUG_CM_PRINTLN("**************");
    delay(500);
    
    tft.setTextColor(ILI9341_BLACK);
    tft.setCursor(50,80);
    tft.println(lcdmessage);
    
}


String ClockMaster::getReplyMessage()
{
  return ReplyMessage;
}