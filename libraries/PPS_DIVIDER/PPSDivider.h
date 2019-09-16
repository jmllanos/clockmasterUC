#ifndef  _PPS_DIVIDER_H_
#define  _PPS_DIVIDER_H_

#include<Arduino.h>
#include<ClockMasterRegisters.h>
#include<read_write_registers.h>
#include<ArduinoJson.h>

class PPSDivider
{
private:
   int per_true_addr;
   int divider_addr;
   int phase_0_addr;
   int phase_1_addr;
   int phase_2_addr;
   int width_addr;
   int start_addr;
   int stop_addr;
   
   int per_true;
   int divider;
   int phase;
   int width;
   int start;
   int stop;
   int channel;

public:
  void set_parameters();
  void set_channel(int _channel); 
  void get_user_parameters(char* data);
  int get_channel();
  void set_registers();
  
};



#endif
