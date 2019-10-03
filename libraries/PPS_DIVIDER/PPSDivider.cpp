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
   
   // Setting Channel to DIVIDER mode
   selector=READ_REGISTER(CH_MUX_SELECTOR,tmp);
   SPI_OK=SPI_OK & tmp;
   
   selector=bitClear(selector,channel);
   WRITE_REGISTER(CH_MUX_SELECTOR,selector,tmp);
   SPI_OK=SPI_OK & tmp;

   if(SPI_OK==false)
   {
       DEBUG_CM_PRINTLN("WRITE FAULT");
       DEBUG_CM_PRINTLN("****************");
       ReplyMessage="{\"setpps\":\"SPI FAULT\"}";
       return;
   }
   
   ReplyMessage="{\"setpps\":\"ok\"}";
   DEBUG_CM_PRINTLN("WRITE DONE");
   DEBUG_CM_PRINT("Channel ");
   DEBUG_CM_PRINT(channel);
   DEBUG_CM_PRINTLN(": Output set as Pulse Generator");  
   
   DEBUG_CM_PRINTLN("**************************************************");

}

String PPSDivider::get_ReplyMessage()
{
    return ReplyMessage;
}

void PPSDivider::get_parameters()
{
   /*
    long user_phase;

    byte response[3];

    DEBUG_CM_PRINTLN("**************************************************");
    DEBUG_CM_PRINTLN("READING PPS DIVIDER REGISTERS");
    
    WRITE_REGISTER(per_true_addr,per_true);
    
    READ_REGISTER(per_true_addr,response);
    DEBUG_CM_PRINTLN("Periodic True");
    DEBUG_CM_PRINTLN(response[1]);       

    READ_REGISTER(divider_addr,response);
    DEBUG_CM_PRINTLN("Divider Number");
    DEBUG_CM_PRINTLN(response[1]);       
    
    READ_REGISTER(phase_0_addr,response);
    user_phase=response[1];

    READ_REGISTER(phase_1_addr,response);
    user_phase=(response[1]<<8)|user_phase;
    
    READ_REGISTER(phase_2_addr,response);
    user_phase=(response[1]<<16)|user_phase;
   
    DEBUG_CM_PRINTLN("Phase");
    DEBUG_CM_PRINTLN(user_phase);
    
    READ_REGISTER(width_addr,response);
    DEBUG_CM_PRINTLN("width ");
    DEBUG_CM_PRINTLN(response[1]);       
    
    READ_REGISTER(start_addr,response);
    DEBUG_CM_PRINTLN("start ");
    DEBUG_CM_PRINTLN(response[1]);       
    
    READ_REGISTER(stop_addr,response);
    DEBUG_CM_PRINTLN("stop");
    DEBUG_CM_PRINTLN(response[1]);       
    
    DEBUG_CM_PRINTLN("**************************************************");
*/
}


void PPSDivider::get_user_parameters(char* data)
{
  StaticJsonBuffer<400> jsonBuffer;
  JsonObject& divider_data = jsonBuffer.parseObject(data);
  
  per_true = (byte)divider_data["periodicTrue"][0];
  divider  = (byte)divider_data["divNumber"][0];
  phase    = (long)divider_data["phase"][0];
  width    = (byte)divider_data["width"][0];
  start    = (byte)divider_data["start"][0];
  stop     = (byte)divider_data["stop"][0];
  channel  = (int)divider_data["channel"][0];
 
}


void PPSDivider::set_parameters(char* data)
{
    SPI_OK=true;
    get_user_parameters(data);

    if(channel>NumberOfChannels-1)
    {
     DEBUG_CM_PRINTLN("INVALID CHANNEL !!!");
     DEBUG_CM_PRINTLN("ABORTING SETTING PARAMETERS IN PPS DIVIDER  REGISTERS");
   
     ReplyMessage="{\"setpps\":\"Fault\",\"channel\":\"Invalid\"}"; 
     return;
    }

    set_registers();
    write_parameters();

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
        DEBUG_CM_PRINTLN("Setting PPS Divider of channel 0"); 
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
        DEBUG_CM_PRINTLN("Setting PPS Divider of channel 1"); 
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
        DEBUG_CM_PRINTLN("Setting PPS Divider of channel 2"); 
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
        DEBUG_CM_PRINTLN("Setting PPS Divider of channel 3"); 
        break;

      default:
        DEBUG_CM_PRINTLN("INVALID CHANNEL");

	} 

}

