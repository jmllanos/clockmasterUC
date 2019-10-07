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
#include<Nokia_5110_AC2.h>
#include<Channel.h>

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
         

         int LCDRow1Index;
         int LCDRow2Index;

    public:
  	  
      thunderbolt thunder;
      void init();
      void getStatus();
      void start();
      void stop();
      void reset();
     
      void showIP(int row);
      void showGateway(int row);
      void displayInfo();
      void showChannel(int channel);
      void setChannel(char* data);
      String getReplyMessage();

     
};



#endif

