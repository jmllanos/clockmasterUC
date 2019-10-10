#include<PPSDivider.h>


void PPSDivider::write_parameters()
{
    bool tmp;
    byte selector;
    byte phase_0=phase;
    byte phase_1=phase>>8;
    byte phase_2=phase>>12;
       
    DEBUG_CM_PRINTLN("**************************************************");
    DEBUG_CM_PRINTLN("WRITING PPS DIVIDER REGISTERS WITH USER PARAMETERS");
    
   WRITE_REGISTER(per_true_addr,per_true,tmp);
   SPI_OK=SPI_OK & tmp;
   
   WRITE_REGISTER(divider_addr,divider,tmp);
   SPI_OK=SPI_OK & tmp;
   
   WRITE_REGISTER(phase_0_addr,phase_0,tmp);
   SPI_OK=SPI_OK & tmp;
  
   WRITE_REGISTER(phase_1_addr,phase_1,tmp);
   SPI_OK=SPI_OK & tmp;
  
   WRITE_REGISTER(phase_2_addr,phase_2,tmp);
   SPI_OK=SPI_OK & tmp;
    
   WRITE_REGISTER(width_addr,width,tmp);
   SPI_OK=SPI_OK & tmp;
    
   WRITE_REGISTER(start_addr,start,tmp);
   SPI_OK=SPI_OK & tmp;
    
   WRITE_REGISTER(stop_addr,stop,tmp);
   SPI_OK=SPI_OK & tmp;
   
   
   if(SPI_OK==false)
   {
       DEBUG_CM_PRINTLN("WRITE FAULT");
       DEBUG_CM_PRINTLN("****************");
       return;
   }
   
   DEBUG_CM_PRINTLN("WRITE DONE");
   DEBUG_CM_PRINTLN("**************************************************");

}

void PPSDivider::read_registers()
{
    byte phase_0;
    byte phase_1;
    byte phase_2;
    byte phase_3;

  bool tmp;
  
   //READ_REGISTER(per_true_addr,tmp);
   //SPI_OK=SPI_OK & tmp;
   
   divider=READ_REGISTER(divider_addr,tmp);
   SPI_OK=SPI_OK & tmp;
      
   phase_0=READ_REGISTER(phase_0_addr,tmp);
   SPI_OK=SPI_OK & tmp;

   phase_1=READ_REGISTER(phase_1_addr,tmp);
   SPI_OK=SPI_OK & tmp;
  
   phase_3= READ_REGISTER(phase_2_addr,tmp);
   SPI_OK=SPI_OK & tmp;
   
   //width= READ_REGISTER(width_addr,tmp);
   //SPI_OK=SPI_OK & tmp;
  
   phase=(phase_2<<16)|(phase_1<<8)|phase_0;
   
}

void PPSDivider::get_parameters()
{
  char charmessage[20];
  String s;
  String message;
  
   read_registers();
   message="DIVIDER:";
   s=String(divider);
   
   message+=s;
   strcpy(charmessage,message.c_str());
   PrintStr(0,2,charmessage);

   DEBUG_CM_PRINTLN(message);
  
   message="PHASE:";
   s=String(phase);
   
   message+=s;
   strcpy(charmessage,message.c_str());
   PrintStr(0,3,charmessage);

   DEBUG_CM_PRINTLN(message);
   
   message="WIDTH:";
   s=String(width);
   message+=s;
   strcpy(charmessage,message.c_str());
   PrintStr(0,4,charmessage);

   DEBUG_CM_PRINTLN(message);
}


String PPSDivider::get_ReplyMessage()
{
    return ReplyMessage;
}


bool PPSDivider::check_valid_parameters()
{
    bool valid_parameters=true;
    String tmp_str;

    ReplyMessage=",\"periodicTrue\":";
    ReplyMessage+=String(per_true);

    ReplyMessage+=",\"phase\":";
    ReplyMessage+=String(phase);

    ReplyMessage+=",\"divider\":";

    if(divider>0)
    {
     valid_parameters=valid_parameters & true;
     tmp_str=String(divider);
     ReplyMessage+=tmp_str;
    }
    else
    {
     valid_parameters=valid_parameters & false;
     ReplyMessage+="\"Invalid\"";
    }

    ReplyMessage+=",\"width\":";
    if(width>0)
    {
     valid_parameters=valid_parameters & true;
     tmp_str=String(width);
     ReplyMessage+=tmp_str;
    }
    else
    {
     valid_parameters=valid_parameters & false;
     ReplyMessage+="\"Invalid\"";
    }


  return valid_parameters;
}

void PPSDivider::get_user_parameters(JsonObject& divider_data)
{
  per_true = (byte)divider_data["periodicTrue"];
  divider  = (byte)divider_data["divNumber"];
  phase    = (uint32_t)divider_data["phase"];
  width    = (byte)divider_data["width"];
  start    = (byte)divider_data["start"];
  stop     = (byte)divider_data["stop"];

}


void PPSDivider::set_parameters(JsonObject& divider_data) 
{
    SPI_OK=true;
    get_user_parameters(divider_data);
    
    if(check_valid_parameters())
    {
       write_parameters();
    }
    else
    {
       DEBUG_CM_PRINTLN("Invalid PPS divider parameters, ABORTING WRITE PROCESS !!!");
    }

}


void PPSDivider::set_channel(int _channel)
{
    if(_channel>NumberOfChannels-1)
    {
     DEBUG_CM_PRINTLN("INVALID CHANNEL !!!");
     return;
    }

 channel = _channel;
 set_registers();

}

bool PPSDivider::get_spi_status()
{
    return SPI_OK;
}

void PPSDivider::set_registers()
{
switch(channel)
	{
	  case 0:
		per_true_addr=PPS_DIV_0_PER_TRUE; 
		divider_addr =PPS_DIV_0_DIV_NUM ;
		phase_0_addr =PPS_DIV_0_PHASE_0 ; 
		phase_1_addr =PPS_DIV_0_PHASE_1 ;
		phase_2_addr =PPS_DIV_0_PHASE_2 ; 
		width_addr   =PPS_DIV_0_WIDTH;    
		start_addr   =PPS_DIV_0_START;   
		stop_addr    =PPS_DIV_0_STOP ;
        DEBUG_CM_PRINTLN("Setting registers address of PPS Divider of channel 0"); 
        break;

	  case 1:
		per_true_addr=PPS_DIV_1_PER_TRUE; 
		divider_addr =PPS_DIV_1_DIV_NUM ;
		phase_0_addr =PPS_DIV_1_PHASE_0 ; 
		phase_1_addr =PPS_DIV_1_PHASE_1 ;
		phase_2_addr =PPS_DIV_1_PHASE_2 ; 
                width_addr   =PPS_DIV_1_WIDTH;    
		start_addr   =PPS_DIV_1_START;   
		stop_addr    =PPS_DIV_1_STOP ;
        DEBUG_CM_PRINTLN("Setting registers address of PPS Divider of channel 1"); 
        break;

	  case 2:
		per_true_addr=PPS_DIV_2_PER_TRUE; 
		divider_addr =PPS_DIV_2_DIV_NUM ;
		phase_0_addr =PPS_DIV_2_PHASE_0 ; 
		phase_1_addr =PPS_DIV_2_PHASE_1 ;
		phase_2_addr =PPS_DIV_2_PHASE_2 ; 
                width_addr   =PPS_DIV_2_WIDTH;    
		start_addr   =PPS_DIV_2_START;   
		stop_addr    =PPS_DIV_2_STOP ;
        DEBUG_CM_PRINTLN("Setting registers address of PPS Divider of channel 2"); 
        break;   

	  case 3:
		per_true_addr=PPS_DIV_3_PER_TRUE; 
		divider_addr =PPS_DIV_3_DIV_NUM ;
		phase_0_addr =PPS_DIV_3_PHASE_0 ; 
		phase_1_addr =PPS_DIV_3_PHASE_1 ;
		phase_2_addr =PPS_DIV_3_PHASE_2 ; 
                width_addr   =PPS_DIV_3_WIDTH;    
		start_addr   =PPS_DIV_3_START;   
		stop_addr    =PPS_DIV_3_STOP ;   
        DEBUG_CM_PRINTLN("Setting registers address of PPS Divider of channel 3"); 
        break;

      default:
        DEBUG_CM_PRINTLN(channel);
        DEBUG_CM_PRINTLN("PPS INVALID CHANNEL");

	} 

}

