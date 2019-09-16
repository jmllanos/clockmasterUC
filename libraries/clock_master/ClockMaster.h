#ifndef _cl_h_
#define _cl_h_
#include<Arduino.h>
#include<ClockMasterRegisters.h>
#include<TIVAConfiguration.h>
#include<PPSDivider.h>
#include<network.h>
#include<ArduinoHttpServer.h>
#include<string.h>


enum UserRequest
{
  Status,
  Reset,
  Start,
  Stop,
  Setdate,
  Setpps,
  Read,
  Write,
  ChangeIP,
  Error
};

UserRequest str2request (String request);



class ClockMaster : public network
{
    private:
          PPSDivider divider_0;
          PPSDivider divider_1;
          PPSDivider divider_2;
          PPSDivider divider_3;
             
    public:
  	  ClockMaster();
  	  void set_divider(char* data);
  	  void get_divider_parameters(int channel);
  	  String reset();
    

};


#endif

