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
  StaticJsonBuffer<800> jsonBuffer;
  JsonObject& pulsegen_data = jsonBuffer.parseObject(data);
  
  enable       = (byte) pulsegen_data["enable"][0];
  usr_year     = (int) pulsegen_data["year"][0];
  usr_month    = (byte) pulsegen_data["month"][0];
  usr_day      = (byte) pulsegen_data["day"][0];
  usr_hour     = (byte) pulsegen_data["hour24h"][0];
  usr_minutes  = (byte) pulsegen_data["minute"][0];
  usr_seconds  = (byte) pulsegen_data["second"][0];
  
  usr_width        =(long) pulsegen_data["widthPulse"][0];
  usr_width_period =(long) pulsegen_data["period"][0];
  
  channel   = (int)pulsegen_data["channel"][0];
 
  DEBUG_CM_PRINTLN("year");
  DEBUG_CM_PRINTLN(usr_year);
  DEBUG_CM_PRINTLN("month");
  DEBUG_CM_PRINTLN(usr_month);
  DEBUG_CM_PRINTLN("day");
  DEBUG_CM_PRINTLN(usr_day);
  DEBUG_CM_PRINTLN("hour");
  DEBUG_CM_PRINTLN(usr_hour);
  DEBUG_CM_PRINTLN("minute");
  DEBUG_CM_PRINTLN(usr_minutes);
  DEBUG_CM_PRINTLN("seconds");
  DEBUG_CM_PRINTLN(usr_seconds);
  DEBUG_CM_PRINTLN("width pulse");
  DEBUG_CM_PRINTLN(usr_width);
  DEBUG_CM_PRINTLN("period");
  DEBUG_CM_PRINTLN(usr_width_period);
  DEBUG_CM_PRINTLN("CHANNEL");
  DEBUG_CM_PRINTLN(channel);

  set_registers();
  
}

void PulseGenerator::set_parameters()
{    
    byte response[3];
    byte usr_year_h = usr_year>>8;
    byte usr_year_l = usr_year;
    bool spi_ok=true;
    DEBUG_CM_PRINTLN("***********************************");
    DEBUG_CM_PRINTLN("WRITING PULSE GENERATOR REGISTERS WITH USER PARAMETERS");
    
    WRITE_REGISTER(usr_year_h_addr,usr_year_h,response);
    spi_ok=CHECK_CORRECT_WRITING(response) & spi_ok ;
   
    WRITE_REGISTER(usr_year_l_addr,usr_year_l,response);
    spi_ok=CHECK_CORRECT_WRITING(response) & spi_ok ;

    WRITE_REGISTER(usr_month_addr,usr_month,response);
    spi_ok=CHECK_CORRECT_WRITING(response) & spi_ok ;

    WRITE_REGISTER(usr_day_addr,usr_day,response);		
    spi_ok=CHECK_CORRECT_WRITING(response) & spi_ok ;

    WRITE_REGISTER(usr_hour_addr,usr_hour,response);
    spi_ok=CHECK_CORRECT_WRITING(response) & spi_ok ;

    WRITE_REGISTER(usr_minutes_addr,usr_minutes,response);
    spi_ok=CHECK_CORRECT_WRITING(response) & spi_ok ;

    WRITE_REGISTER(usr_seconds_addr,usr_seconds,response);
    spi_ok=CHECK_CORRECT_WRITING(response) & spi_ok ;
   
    WRITE_REGISTER(enable_addr,enable,response);
    spi_ok=CHECK_CORRECT_WRITING(response) & spi_ok ;
    
    if(spi_ok==false)
    {
     DEBUG_CM_PRINTLN("SPI FAULT !!!!");
    }

    get_parameters();
 
}

void PulseGenerator::get_parameters()
{
   DEBUG_CM_PRINTLN("********************");
   DEBUG_CM_PRINTLN("READING PULSE GENERATOR REGISTERS");
    byte response[3];
    int _usr_year;

        
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
   
    READ_REGISTER(enable_addr,response);
     DEBUG_CM_PRINTLN("Enable status: ");
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

        DEBUG_CM_PRINTLN("Set to channel 0");
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
        
        DEBUG_CM_PRINTLN("Set to channel 1");
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
        
        DEBUG_CM_PRINTLN("Set to channel 2");
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
        
        DEBUG_CM_PRINTLN("Set to channel 3");
	   break;
	   
      default:
        DEBUG_CM_PRINTLN("Invalid channel");

	  }
  
} 
