#include<PulseGenerator.h>


void PulseGenerator::get_user_parameters(char* data)
{  
  StaticJsonBuffer<800> jsonBuffer;
  JsonObject& pulsegen_data = jsonBuffer.parseObject(data);
  
  usr_year     = (int) pulsegen_data["year"][0];
  usr_month    = (byte) pulsegen_data["month"][0];
  usr_day      = (byte) pulsegen_data["day"][0];
  usr_hour     = (byte) pulsegen_data["hour24h"][0];
  usr_minutes  = (byte) pulsegen_data["minute"][0];
  usr_seconds  = (byte) pulsegen_data["second"][0];
  
  usr_width        =(long) pulsegen_data["widthPulse"][0];
  usr_width_period =(long) pulsegen_data["period"][0];
  
  channel   = (int)pulsegen_data["channel"][0];
 
  
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
 
   // Setting Channel to PULSE GENERATOR  mode
   selector=READ_REGISTER(CH_MUX_SELECTOR,tmp);
   SPI_ok=SPI_ok & tmp;
   
   selector=bitSet(selector,channel);
   WRITE_REGISTER(CH_MUX_SELECTOR,selector,tmp);
   SPI_ok=SPI_ok & tmp;
   

   if(SPI_ok==false)
   {
     DEBUG_CM_PRINTLN("WRITE FAULT");
     DEBUG_CM_PRINTLN("***********************************");
     ReplyMessage="{\"setdate\":\"SPI FAULT\"}";
     return;
   }
    
    ReplyMessage="{\"setdate\":\"ok\"}";

    DEBUG_CM_PRINTLN("WRITING DONE");
    DEBUG_CM_PRINT("Channel ");
    DEBUG_CM_PRINT(channel);
    DEBUG_CM_PRINTLN(": Output set as Pulse Generator");
    DEBUG_CM_PRINTLN("***********************************");
}


bool PulseGenerator::check_valid_config()
{
  bool valid_config=true;
  
  String tmp;
  ReplyMessage="{\"setdate\":\"Invalid\"";
  
  ReplyMessage+=",\"month\":";
  if (usr_month>=1  && usr_month<=12)
  {
    tmp=String(usr_month);
    ReplyMessage+=tmp;
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
    tmp=String(usr_day);
    ReplyMessage+=tmp; 
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
    tmp=String(usr_hour);
    ReplyMessage+=tmp; 
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
   tmp=String(usr_minutes);
    ReplyMessage+=tmp; 
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
   tmp=String(usr_seconds);
    ReplyMessage+=tmp; 
    valid_config=valid_config & true;
 }
  else
 {
    ReplyMessage+="invalid";
    valid_config=valid_config & false;
 }

  ReplyMessage+=",\"channel\":";
  if(channel>=0 && channel<=NumberOfChannels-1)
  {
    tmp=String(channel);
    ReplyMessage+=tmp; 
    valid_config=valid_config & true;
  }
  else
  {
    ReplyMessage+="invalid";
    valid_config=valid_config & false;
    DEBUG_CM_PRINTLN("INVALID CHANNEL !!!");
  }

  ReplyMessage+="}";
  return valid_config;
}


void PulseGenerator::set_parameters(char* data)
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

 set_registers();

 write_parameters();
 

}

String PulseGenerator::get_ReplyMessage()
{
    return ReplyMessage;
}

void PulseGenerator::get_parameters()
{
 /*  DEBUG_CM_PRINTLN("********************");
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
   
    READ_REGISTER(usr_width_high_0_addr,response);
    DEBUG_CM_PRINTLN("USER width: ");
    DEBUG_CM_PRINTLN(response[1]);
   
    READ_REGISTER(usr_width_period_0_addr,response);
    DEBUG_CM_PRINTLN("USER period: ");
    DEBUG_CM_PRINTLN(response[1]);

    READ_REGISTER(enable_addr,response);
    DEBUG_CM_PRINTLN("Enable status: ");
    DEBUG_CM_PRINTLN(response[1]);
*/
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
