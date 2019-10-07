#include<PulseGenerator.h>


void PulseGenerator::get_user_parameters(JsonObject& pulsegen_data)
{  
  
  usr_year     = (int) pulsegen_data["year"];
  usr_month    = (byte) pulsegen_data["month"];
  usr_day      = (byte) pulsegen_data["day"];
  usr_hour     = (byte) pulsegen_data["hour24h"];
  usr_minutes  = (byte) pulsegen_data["minute"];
  usr_seconds  = (byte) pulsegen_data["second"];
  
  usr_width        =(long) pulsegen_data["widthPulse"];
  usr_width_period =(long) pulsegen_data["period"];
  
}

void  PulseGenerator::write_parameters()
{  
   bool tmp;
   byte selector;

    byte usr_year_h = usr_year>>8;
    byte usr_year_l = usr_year;
    
    byte usr_width_0=usr_width;
    byte usr_width_1=usr_width>>8;
    byte usr_width_2=usr_width>>16;
    byte usr_width_3=usr_width>>24;

    byte usr_width_period_0=usr_width_period;
    byte usr_width_period_1=usr_width_period>>8;
    byte usr_width_period_2=usr_width_period>>16;
    byte usr_width_period_3=usr_width_period>>24;

    DEBUG_CM_PRINTLN("***********************************");
    DEBUG_CM_PRINTLN("WRITING PULSE GENERATOR REGISTERS WITH USER PARAMETERS");
   
   WRITE_REGISTER(enable_addr,DISABLE_PULSEGEN,tmp);
   SPI_ok=SPI_ok & tmp;
   // date 
    WRITE_REGISTER(usr_year_h_addr,usr_year_h,tmp);
    SPI_ok=SPI_ok & tmp;
    WRITE_REGISTER(usr_year_l_addr,usr_year_l,tmp);
    SPI_ok=SPI_ok & tmp;
    WRITE_REGISTER(usr_month_addr,usr_month,tmp);
    SPI_ok=SPI_ok & tmp;
    WRITE_REGISTER(usr_day_addr,usr_day,tmp);		
    SPI_ok=SPI_ok & tmp;
    WRITE_REGISTER(usr_hour_addr,usr_hour,tmp);
    SPI_ok=SPI_ok & tmp;
    WRITE_REGISTER(usr_minutes_addr,usr_minutes,tmp);
    SPI_ok=SPI_ok & tmp;
    WRITE_REGISTER(usr_seconds_addr,usr_seconds,tmp);
    SPI_ok=SPI_ok & tmp;

    // width high
   WRITE_REGISTER(usr_width_high_3_addr,usr_width_3,tmp);
   SPI_ok=SPI_ok & tmp;
   WRITE_REGISTER(usr_width_high_2_addr,usr_width_2,tmp);
   SPI_ok=SPI_ok & tmp;
   WRITE_REGISTER(usr_width_high_1_addr,usr_width_1,tmp);
   SPI_ok=SPI_ok & tmp;
   WRITE_REGISTER(usr_width_high_0_addr,usr_width_0,tmp);
   SPI_ok=SPI_ok & tmp;
    
    // width period
   WRITE_REGISTER(usr_width_period_3_addr,usr_width_period_3,tmp);
   SPI_ok=SPI_ok & tmp;
   WRITE_REGISTER(usr_width_period_2_addr,usr_width_period_2,tmp);
   SPI_ok=SPI_ok & tmp;
   WRITE_REGISTER(usr_width_period_1_addr,usr_width_period_1,tmp);
   SPI_ok=SPI_ok & tmp;
   WRITE_REGISTER(usr_width_period_0_addr,usr_width_period_0,tmp);
   SPI_ok=SPI_ok & tmp;

    //enable
   WRITE_REGISTER(enable_addr,ENABLE_PULSEGEN,tmp);
   SPI_ok=SPI_ok & tmp;
 
     

   if(SPI_ok==false)
   {
     DEBUG_CM_PRINTLN("WRITE FAULT");
     DEBUG_CM_PRINTLN("***********************************");
     ReplyMessage="{\"setdate\":\"SPI FAULT\"}";
     return;
   }
    

   DEBUG_CM_PRINTLN("WRITING DONE");
   DEBUG_CM_PRINTLN("***********************************");
}


void PulseGenerator::set_channel(int _channel)
{
    if(channel>=NumberOfChannels-1)
    {
     DEBUG_CM_PRINTLN("INVALID CHANNEL !!!");
     return;
    }

 channel = _channel;
 set_registers();

}



bool PulseGenerator::check_valid_config()
{
  bool valid_config=true;
  
  String tmp;

  ReplyMessage=",\"year\":";
  ReplyMessage+=String(usr_year);

  ReplyMessage+=",\"month\":";
  if (usr_month>=1  && usr_month<=12)
  {
    ReplyMessage+=String(usr_month);
    valid_config=valid_config & true;
  }
  else
  {
    ReplyMessage+="invalid";
    valid_config=valid_config & false;
  }

  ReplyMessage+=",\"day\":";
  if (usr_day>=1    && usr_day<=31)
 {
    ReplyMessage+=String(usr_day);
    valid_config=valid_config & true;
 } 
 else
 {
    ReplyMessage+="invalid";
    valid_config=valid_config & false;
 }
 
  ReplyMessage+=",\"hour\":";
 if (usr_hour>=0   && usr_hour<=23)
 {
    ReplyMessage+=String(usr_hour);
    valid_config=valid_config & true;
 }
 else
 {
    ReplyMessage+="invalid";
    valid_config=valid_config & false;
 }

 ReplyMessage+=",\"minutes\":";
 if (usr_minutes>=0 && usr_minutes<=59)
 {
    ReplyMessage+=String(usr_minutes);
    valid_config=valid_config & true;
 }
  else
 {
    ReplyMessage+="invalid";
    valid_config=valid_config & false;
 }

  ReplyMessage+=",\"seconds\":";
  if (usr_seconds>=0 && usr_seconds<=59)
 {
   ReplyMessage+=String(usr_seconds);
   valid_config=valid_config & true;
 }
  else
 {
    ReplyMessage+="invalid";
    valid_config=valid_config & false;
 }

 ReplyMessage+=",\"widthPulse\":";
 
 if(usr_width>0)
  {
    ReplyMessage+=String(usr_width);
    valid_config=valid_config & true;
  }
  else
  {
    ReplyMessage+="invalid";
    valid_config=valid_config & false;
  }

 ReplyMessage+=",\"period\":";
 
 if(usr_width_period>0)
  {
    ReplyMessage+=String(usr_width_period);
    valid_config=valid_config & true;
  }
  else
  {
    ReplyMessage+="invalid";
    valid_config=valid_config & false;
  }

  return valid_config;
}


void PulseGenerator::set_parameters(JsonObject& data)
{

 ReplyMessage=""; 
 
  SPI_ok=true;

  get_user_parameters(data);

 if(check_valid_config()==false)
 {
   DEBUG_CM_PRINTLN("INVALID CONFIGURATION FOR PULSE GENERATOR !!!");
   DEBUG_CM_PRINTLN("ABORTING SETTING PARAMETERS IN PULSE REGISTERS");
   DEBUG_CM_PRINTLN("***********************************");
   return;
 }


 write_parameters();
 

}

String PulseGenerator::get_ReplyMessage()
{
    return ReplyMessage;
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

        DEBUG_CM_PRINTLN("Setting Pulse Generator of channel 0");
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
        
        DEBUG_CM_PRINTLN("Setting Pulse Generator of channel 1");
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
        
        DEBUG_CM_PRINTLN("Setting Pulse Generator of channel 2");
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
        
        DEBUG_CM_PRINTLN("Setting Pulse Generator of channel 3");
	   break;
	   
	  }
  
} 
