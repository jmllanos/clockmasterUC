#ifndef _cl_h_
#define _cl_h_

#include<Arduino.h>
#include<ClockMasterRegisters.h>
#include<TIVAConfiguration.h>
#include<ArduinoHttpServer.h>
#include<string.h>

#include<network.h>
#include<PulseGenerator.h>
#include<PPSDivider.h>
#include<read_write_registers.h>


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
    void read_time();
};



class ClockMaster : public network
{
    private:
          PPSDivider divider_0;
          PPSDivider divider_1;
          PPSDivider divider_2;
          PPSDivider divider_3;

          PulseGenerator PulseGen_0;
          PulseGenerator PulseGen_1;
          PulseGenerator PulseGen_2;
          PulseGenerator PulseGen_3;

           byte channels_mux_enable;
           byte channels_mux_selector;
    public:
  	  
      thunderbolt thunder;
  	  void init();
      void set_divider(char* data);
  	  void get_divider_parameters(int channel);
  	  void set_pulsegen(char* data);
  	  void get_pulsegen_parameters(int channel);
      void set_channel_configuration();
      void set_channels_muxes(char* data);
      String reset();
};



#endif

