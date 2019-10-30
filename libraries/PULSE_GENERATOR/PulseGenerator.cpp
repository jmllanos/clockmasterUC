#include<PulseGenerator.h>


void PulseGenerator::get_user_parameters(JsonObject& pulsegen_data)
{  
  
  usr_year     = (int) pulsegen_data["year"];
  usr_month    = (byte) pulsegen_data["month"];
  usr_day      = (byte) pulsegen_data["day"];
  usr_hour     = (byte) pulsegen_data["hour24h"];
  usr_minutes  = (byte) pulsegen_data["minute"];
  usr_seconds  = (byte) pulsegen_data["second"];
  
  width        =(long) pulsegen_data["widthPulse"];
  period       =(long) pulsegen_data["period"];
  
}

void  PulseGenerator::write_parameters()
{  
   bool tmp;
   byte selector;

    byte usr_year_h = usr_year>>8;
    byte usr_year_l = usr_year;
    
    byte usr_width_0=width;
    byte usr_width_1=width>>8;
    byte usr_width_2=width>>16;
    byte usr_width_3=width>>24;

    byte usr_width_period_0=period;
    byte usr_width_period_1=period>>8;
    byte usr_width_period_2=period>>16;
    byte usr_width_period_3=period>>24;

    DEBUG_CM_PRINTLN("***********************************");
    DEBUG_CM_PRINTLN("WRITING PULSE GENERATOR REGISTERS WITH USER PARAMETERS");
   
   WRITE_REGISTER(enable_addr,DISABLE_PULSEGEN,tmp);
   SPI_ok=SPI_ok & tmp;
   // DATE 
    WRITE_REGISTER(usr_year_h_addr,usr_year_h,tmp);
    SPI_ok=SPI_ok & tmp;
    WRITE_REGISTER(usr_year_l_addr,usr_year_l,tmp);
    SPI_ok=SPI_ok & tmp;
    WRITE_REGISTER(usr_month_addr,usr_month,tmp);
    SPI_ok=SPI_ok & tmp;
    WRITE_REGISTER(usr_day_addr,usr_day,tmp);		
    SPI_ok=SPI_ok & tmp;
    // TIME
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
     return;
   }
    

   DEBUG_CM_PRINTLN("WRITING DONE");
   DEBUG_CM_PRINTLN("***********************************");
}


void PulseGenerator::set_channel(int _channel)
{
    if(_channel>NumberOfChannels-1)
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
    ReplyMessage+="\"Invalid\"";
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
    ReplyMessage+="\"Invalid\"";
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
    ReplyMessage+="\"Invalid\"";
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
    ReplyMessage+="\"Invalid\"";
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
    ReplyMessage+="\"Invalid\"";
    valid_config=valid_config & false;
 }

 ReplyMessage+=",\"widthPulse\":";
 
 if(width>0)
  {
    ReplyMessage+=String(width);
    valid_config=valid_config & true;
  }
  else
  {
    ReplyMessage+="\"Invalid\"";
    valid_config=valid_config & false;
  }

 ReplyMessage+=",\"period\":";
 
 if(period>0)
  {
    ReplyMessage+=String(period);
    valid_config=valid_config & true;
  }
  else
  {
    ReplyMessage+="\"invalid\"";
    valid_config=valid_config & false;
  }

  return valid_config;
}

void PulseGenerator::read_registers()
{
   bool tmp;
   byte selector;

    byte usr_year_h;
    byte usr_year_l;
    
    byte width_0;
    byte width_1;
    byte width_2;
    byte width_3;

    byte period_0;
    byte period_1;
    byte period_2;
    byte period_3;
   
   // date 
    usr_year_h= READ_REGISTER(usr_year_h_addr,tmp);
    SPI_ok=SPI_ok & tmp;
    usr_year_l= READ_REGISTER(usr_year_l_addr,tmp);
    SPI_ok=SPI_ok & tmp;
   
    usr_year=(usr_year_h<<8)| usr_year_l;

    usr_month=READ_REGISTER(usr_month_addr,tmp);
    SPI_ok=SPI_ok & tmp;
    usr_day=READ_REGISTER(usr_day_addr,tmp);		
    SPI_ok=SPI_ok & tmp;
    usr_hour=READ_REGISTER(usr_hour_addr,tmp);
    SPI_ok=SPI_ok & tmp;
    usr_minutes=READ_REGISTER(usr_minutes_addr,tmp);
    SPI_ok=SPI_ok & tmp;
    usr_seconds=READ_REGISTER(usr_seconds_addr,tmp);
    SPI_ok=SPI_ok & tmp;

    // width high
   width_3=READ_REGISTER(usr_width_high_3_addr,tmp);
   SPI_ok=SPI_ok & tmp;
   width_2=READ_REGISTER(usr_width_high_2_addr,tmp);
   SPI_ok=SPI_ok & tmp;
   width_1=READ_REGISTER(usr_width_high_1_addr,tmp);
   SPI_ok=SPI_ok & tmp;
   width_0=READ_REGISTER(usr_width_high_0_addr,tmp);
   SPI_ok=SPI_ok & tmp;
   
   width=(width_3<<24)|(width_3<<16)|(width_1<<8)|width_0;
    
    // width period
   period_3=READ_REGISTER(usr_width_period_3_addr,tmp);
   SPI_ok=SPI_ok & tmp;
   period_2=READ_REGISTER(usr_width_period_2_addr,tmp);
   SPI_ok=SPI_ok & tmp;
   period_1=READ_REGISTER(usr_width_period_1_addr,tmp);
   SPI_ok=SPI_ok & tmp;
   period_0=READ_REGISTER(usr_width_period_0_addr,tmp);
   SPI_ok=SPI_ok & tmp;
   
   period=(period_3<<24)|(period_2<<16)|(period_1<<8)|period_0;
   
}

String PulseGenerator::get_parameters()
{
    
   String LCDMessage;
 
   read_registers();
  
   LCDMessage="DATE: ";
   if(usr_month<10)
   {
    LCDMessage+="0";
   }
   LCDMessage+=String(usr_month);
      
   LCDMessage+="/";
   if(usr_day<10)
   {
    LCDMessage+="0";
   }
   LCDMessage+=String(usr_day);

   LCDMessage+="/";
   LCDMessage+=String(usr_year-2000);
   LCDMessage=LCDMessage +"\n" +"TIME: ";
   if(usr_hour<10)
   {
    LCDMessage+="0";
   }

   LCDMessage+=String(usr_hour);   

   LCDMessage+=":";
   if(usr_minutes<10)
   {
    LCDMessage+="0";
   }
  
   LCDMessage+=String(usr_minutes);
   
   LCDMessage+=":";
   if(usr_seconds<10)
   {
    LCDMessage+="0";
   }
   LCDMessage+=String(usr_seconds);
   
      
   LCDMessage=LCDMessage +"\n"+"WIDTH: ";
   LCDMessage+=String(width);
  
   
   LCDMessage=LCDMessage + "\n"+"PERIOD: ";
   LCDMessage+=String(period);
   
   DEBUG_CM_PRINTLN(LCDMessage);
   
   return LCDMessage;
   
}

void PulseGenerator::set_parameters(JsonObject& data)
{

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

bool PulseGenerator::get_spi_status()
{
    return SPI_ok;
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

        DEBUG_CM_PRINTLN("Setting registers address of Pulse Generator of channel 0");
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
        
        DEBUG_CM_PRINTLN("Setting registers address of Pulse Generator of channel 1");
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
        
        DEBUG_CM_PRINTLN("Setting registers address of Pulse Generator of channel 2");
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
        
        DEBUG_CM_PRINTLN("Setting registers address of Pulse Generator of channel 3");
	   break;
	   
	  }
  
} 
