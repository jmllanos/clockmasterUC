#fndef  _PPS_DIVIDER_H_
#define  _PPS_DIVIDER_H_

#include<Arduino.h>
#include<clock_master_registers.h>
#include<read_write_registers.h>

class pps_divider
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

public:
  
  pps_divider(int number);
  void set_per_true(bool per_true);
  bool get_per_true();
  void set_divider(byte divider);
  byte get_divider();
  void set_phase(int phase);
  byte get_phase();
  void set_width(byte width);
  byte get_width();
  void set_start(byte start);
  byte get_start();  
  void set_stop(byte stop);
  byte get_stop();  
  
  
};




#endif
