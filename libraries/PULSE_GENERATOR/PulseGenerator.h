
#ifndef _PULSE_GENERATOR_H_
#define _PULSE_GENERATOR_H_

#include<Arduino.h>
#include<ClockMasterRegisters.h>
#include<read_write_registers.h>
#include<ArduinoJson.h>

class PulseGenerator
{
    private:
        byte enable_addr;
        byte usr_year_h_addr;
        byte usr_year_l_addr;
        byte usr_month_addr;
        byte usr_day_addr;
        byte usr_hour_addr;
        byte usr_minutes_addr;
        byte usr_seconds_addr;
        byte usr_width_high_3_addr;
        byte usr_width_high_2_addr;
        byte usr_width_high_1_addr;
        byte usr_width_high_0_addr;
        byte usr_width_period_3_addr;
        byte usr_width_period_2_addr;
        byte usr_width_period_1_addr;
        byte usr_width_period_0_addr;
        
        byte enable;
        int usr_year;
        byte usr_month;
        byte usr_day;
        byte usr_hour;
        byte usr_minutes;
        byte usr_seconds;
        long usr_width;
        long usr_width_period;
        
        int channel;

        void set_registers();
     public:
       void set_parameters();
       void get_user_parameters(char* data);
       void set_channel(int _channel);
       int get_channel();
       void get_parameters();
        
};


#endif
