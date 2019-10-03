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

enum UserRequest
{
  Status,
  Reset,
  Start,
  Stop,
  Setdate,
  Setpps,
  SetChannels,
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
          
         PPSDivider PPSdiv;
          
         PulseGenerator PulseGen;

         byte channels_mux_enable;

         String ReplyMessage;
    public:
  	  
      thunderbolt thunder;
      void init();
      void getStatus();
      void start();
      void stop();
      void reset();
      void setDivider(char* data);
      void setPulsegen(char* data);
            
      String getReplyMessage();
};



#endif

