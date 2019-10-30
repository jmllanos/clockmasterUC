#ifndef _CLOCK_MASTER_H_
#define _CLOCK_MASTER_H_

#include<Arduino.h>
#include<ClockMasterRegisters.h>
#include<TIVAConfiguration.h>
#include<ArduinoHttpServer.h>
#include<string.h>

#include<network.h>
#include<PulseGenerator.h>
#include<PPSDivider.h>
#include<read_write_registers.h>
#include<string.h>
#include<Channel.h>
#include "Adafruit_GFX.h"
#include "Adafruit_ILI9341.h"

enum UserRequest
{
  Status,
  Reset,
  Start,
  Stop,
  Setdate,
  Setpps,
  SetChannel,
  Read,
  Write,
  ChangeIP,
  InvalidMethod
};

UserRequest str2request (String request);

class thunderbolt
{
    private:

    public:
    void readTime();
};


class ClockMaster : public network
{
    private:
          
         byte channels_mux_enable;

         String ReplyMessage;
         
         Channel channel0;
         Channel channel1;
         Channel channel2;
         Channel channel3;
         
         int LCDRowIndex=0;

         bool SPIStatus;
         
         String strStatus;
         String lcdmessage;

    public:
  	  
      thunderbolt thunder;
      void init();
      void getStatus();
      void start();
      void stop();
      void reset();
     
      void showIP();
      void displayInfo();
      void showChannel(int channel);
      void showStatus();

      void setChannel(char* data);
      String getReplyMessage();
      
      void showCGS();
     
};



#endif

