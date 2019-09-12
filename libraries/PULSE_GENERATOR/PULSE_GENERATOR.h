#ifndef _PULSE_GENERATOR_H_
#define _PULSE_GENERATOR_H_


class pulse_gen
{
    private:
        int enable_addr;
        int year_h_addr;
        int year_l_addr;
        int usr_month_addr;
        int usr_day_addr;
        int usr_minutes_addr;
        int usr_seconds_addr;
        int usr_width_high_3_addr;
        int usr_width_high_2_addr;
        int usr_width_high_1_addr;
        int usr_width_high_0_addr;
        int usr_width_period_3_addr;
        int usr_width_period_2_addr;
        int usr_width_period_1_addr;
        int usr_width_period_0_addr;
    public:
        pulse_gen(int number);

};

#endif
