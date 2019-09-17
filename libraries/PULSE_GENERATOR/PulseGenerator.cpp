#include<PulseGenerator.h>

void PulseGenerator::set_channel(int _channel)
{
 channel= _channel;

 set_registers();
}

int PulseGenerator::get_channel()
{
 return channel;
}


void PulseGenerator::get_user_parameters(char* data)
{
  StaticJsonBuffer<400> jsonBuffer;
  JsonObject& pulsegen_data = jsonBuffer.parseObject(data);
  
  enable       = pulsegen_data["enable"];
  usr_year     = pulsegen_data["year"];
  usr_month    = pulsegen_data["month"];
  usr_day      = pulsegen_data["day"];
  usr_hour     = pulsegen_data["hour24"];
  usr_minutes  = pulsegen_data["minute"];
  usr_seconds  = pulsegen_data["second"];
  
  usr_width        = pulsegen_data["widthPulse"];
  usr_width_period = pulsegen_data["period"];
  
  channel   = pulsegen_data["channel"];
  
  set_registers();
  
}

void PulseGenerator::set_parameters()
{    
    byte response[3];
    byte usr_year_h = usr_year>>8;
    byte usr_year_l = usr_year;
    
   
    WRITE_REGISTER(usr_year_h_addr,usr_year_h,response);

    WRITE_REGISTER(usr_year_l_addr,usr_year_l,response);

    WRITE_REGISTER(usr_month_addr,usr_month,response);

    WRITE_REGISTER(usr_day_addr,usr_day,response);		

    WRITE_REGISTER(usr_hour_addr,usr_hour,response);

    WRITE_REGISTER(usr_minutes_addr,usr_minutes,response);

    WRITE_REGISTER(usr_seconds_addr,usr_seconds,response);
   
    WRITE_REGISTER(enable_addr,enable,response);

    get_parameters();
 
}

void PulseGenerator::get_parameters()
{
    
    byte response[3];
    int _usr_year;

    READ_REGISTER(enable_addr,response);
    
    READ_REGISTER(usr_year_l_addr,response);
    _usr_year=response[1];

    READ_REGISTER(usr_year_h_addr,response);
    _usr_year=(response[1]<<8) | _usr_year;    
    
    DEBUG_CM_PRINTLN("USER YEAR: ");
    DEBUG_CM_PRINTLN(_usr_year);
    
    READ_REGISTER(usr_month_addr,response);
    DEBUG_CM_PRINTLN("USER MONTH: ");
    DEBUG_CM_PRINTLN(response[1]);

    READ_REGISTER(usr_day_addr,response);		
    DEBUG_CM_PRINTLN("USER DAY: ");
    DEBUG_CM_PRINTLN(response[1]); 
   
    READ_REGISTER(usr_hour_addr,response);
    DEBUG_CM_PRINTLN("USER HOUR: ");
    DEBUG_CM_PRINTLN(response[1]);
    
    READ_REGISTER(usr_minutes_addr,response);
    DEBUG_CM_PRINTLN("USER MINUTE: ");
    DEBUG_CM_PRINTLN(response[1]);
    
    READ_REGISTER(usr_seconds_addr,response);
    DEBUG_CM_PRINTLN("USER SECOND: ");
    DEBUG_CM_PRINTLN(response[1]);

}

void PulseGenerator::set_registers()
{
   switch(channel)
	  { 
	  case 0:
		enable_addr             =PG0_PULSE_ENA;
		usr_year_h_addr         =PG0_USR_YEAR_H;
		usr_year_l_addr         =PG0_USR_YEAR_L;
		usr_month_addr          =PG0_USR_MONTH;
		usr_day_addr            =PG0_USR_DAY;
		usr_hour_addr           =PG0_USR_HOUR;
		usr_minutes_addr        =PG0_USR_MINUTES;
		usr_seconds_addr        =PG0_USR_SECONDS;
		usr_width_high_3_addr   =PG0_WIDTH_HIGH_3;
		usr_width_high_2_addr   =PG0_WIDTH_HIGH_2;
		usr_width_high_1_addr   =PG0_WIDTH_HIGH_1;
		usr_width_high_0_addr   =PG0_WIDTH_HIGH_0;
		usr_width_period_3_addr =PG0_WIDTH_PERIOD_3;
		usr_width_period_2_addr =PG0_WIDTH_PERIOD_2;
		usr_width_period_1_addr =PG0_WIDTH_PERIOD_1;
		usr_width_period_0_addr =PG0_WIDTH_PERIOD_0;
	   break;
	         
	  case 1:
		enable_addr             =PG1_PULSE_ENA;
		usr_year_h_addr         =PG1_USR_YEAR_H;
		usr_year_l_addr         =PG1_USR_YEAR_L;
		usr_month_addr          =PG1_USR_MONTH;
		usr_day_addr            =PG1_USR_DAY;
		usr_hour_addr           =PG1_USR_HOUR;
		usr_minutes_addr        =PG1_USR_MINUTES;
		usr_seconds_addr        =PG1_USR_SECONDS;
		usr_width_high_3_addr   =PG1_WIDTH_HIGH_3;
		usr_width_high_2_addr   =PG1_WIDTH_HIGH_2;
		usr_width_high_1_addr   =PG1_WIDTH_HIGH_1;
		usr_width_high_0_addr   =PG1_WIDTH_HIGH_0;
		usr_width_period_3_addr =PG1_WIDTH_PERIOD_3;
		usr_width_period_2_addr =PG1_WIDTH_PERIOD_2;
		usr_width_period_1_addr =PG1_WIDTH_PERIOD_1;
		usr_width_period_0_addr =PG1_WIDTH_PERIOD_0;
	   break;

	  case 2:
		enable_addr             =PG2_PULSE_ENA;
		usr_year_h_addr         =PG2_USR_YEAR_H;
		usr_year_l_addr         =PG2_USR_YEAR_L;
		usr_month_addr          =PG2_USR_MONTH;
		usr_day_addr            =PG2_USR_DAY;
		usr_hour_addr           =PG2_USR_HOUR;
		usr_minutes_addr        =PG2_USR_MINUTES;
		usr_seconds_addr        =PG2_USR_SECONDS;
		usr_width_high_3_addr   =PG2_WIDTH_HIGH_3;
		usr_width_high_2_addr   =PG2_WIDTH_HIGH_2;
		usr_width_high_1_addr   =PG2_WIDTH_HIGH_1;
		usr_width_high_0_addr   =PG2_WIDTH_HIGH_0;
		usr_width_period_3_addr =PG2_WIDTH_PERIOD_3;
		usr_width_period_2_addr =PG2_WIDTH_PERIOD_2;
		usr_width_period_1_addr =PG2_WIDTH_PERIOD_1;
		usr_width_period_0_addr =PG2_WIDTH_PERIOD_0;
	   break;
	  
	  case 3:
		enable_addr             =PG3_PULSE_ENA;
		usr_year_h_addr         =PG3_USR_YEAR_H;
		usr_year_l_addr         =PG3_USR_YEAR_L;
		usr_month_addr          =PG3_USR_MONTH;
		usr_day_addr            =PG3_USR_DAY;
		usr_hour_addr           =PG3_USR_HOUR;
		usr_minutes_addr        =PG3_USR_MINUTES;
		usr_seconds_addr        =PG3_USR_SECONDS;
		usr_width_high_3_addr   =PG3_WIDTH_HIGH_3;
		usr_width_high_2_addr   =PG3_WIDTH_HIGH_2;
		usr_width_high_1_addr   =PG3_WIDTH_HIGH_1;
		usr_width_high_0_addr   =PG3_WIDTH_HIGH_0;
		usr_width_period_3_addr =PG3_WIDTH_PERIOD_3;
		usr_width_period_2_addr =PG3_WIDTH_PERIOD_2;
		usr_width_period_1_addr =PG3_WIDTH_PERIOD_1;
		usr_width_period_0_addr =PG3_WIDTH_PERIOD_0;
	   break;
	    
	  }
  
} 
