#ifndef  _PPS_DIVIDER_H_
#define  _PPS_DIVIDER_H_

#include<Arduino.h>
#include<ClockMasterRegisters.h>
#include<read_write_registers.h>
#include<ArduinoJson.h>
#include<string.h>

class PPSDivider
{
private:
   byte per_true_addr;
   byte divider_addr;
   byte phase_0_addr;
   byte phase_1_addr;
   byte phase_2_addr;
   byte width_addr;
   byte start_addr;
   byte stop_addr;
   
   byte per_true;
   byte divider;
   long phase;
   byte width;
   byte start;
   byte stop;
   int channel;

   bool SPI_OK;

   String ReplyMessage;

  void get_user_parameters(char* data);
  void write_parameters(); 
  void set_registers();

public:
  void set_parameters(char* data);
  void get_parameters();
  
  String get_ReplyMessage();

};


#endif
