#include<PPSDivider.h>

void PPSDivider::set_channel(int _channel)
{
  channel=_channel;
  set_registers();
}

byte PPSDivider::get_channel()
{
  return channel;
}

void PPSDivider::set_parameters()
{
    byte phase_0=phase;
    byte phase_1=phase>>8;
    byte phase_2=phase>>12;
    
    byte response[3];
    WRITE_REGISTER(per_true_addr,per_true,response);
           
    WRITE_REGISTER(divider_addr,divider,response);
   
    WRITE_REGISTER(phase_0_addr,phase_0,response);
    
    WRITE_REGISTER(phase_1_addr,phase_1,response);
    
    WRITE_REGISTER(phase_2_addr,phase_2,response);
    
    WRITE_REGISTER(width_addr,width,response);
    
    WRITE_REGISTER(start_addr,start,response);
    
    WRITE_REGISTER(stop_addr,stop,response);

}

void PPSDivider::get_parameters()
{    
    byte response[3];
    READ_REGISTER(per_true_addr,response);
           
    READ_REGISTER(divider_addr,response);
   
    READ_REGISTER(phase_0_addr,response);
    
    READ_REGISTER(phase_1_addr,response);
    
    READ_REGISTER(phase_2_addr,response);
    
    READ_REGISTER(width_addr,response);
    
    READ_REGISTER(start_addr,response);
    
    READ_REGISTER(stop_addr,response);

}


void PPSDivider::get_user_parameters(char* data)
{
  StaticJsonBuffer<400> jsonBuffer;
  JsonObject& divider_data = jsonBuffer.parseObject(data);
  
  per_true = divider_data["per_true"];
  divider  = divider_data["divider"];
  phase    = divider_data["phase"];
  width    = divider_data["width"];
  start    = divider_data["star"];
  stop     = divider_data["stop"];
  channel  = divider_data["channel"];
  
  set_registers();

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
	  case 1:
		per_true_addr=PPS_DIV_1_PER_TRUE; 
		divider_addr =PPS_DIV_1_DIV_NUM ;
		phase_0_addr =PPS_DIV_1_PHASE_0 ; 
		phase_1_addr =PPS_DIV_1_PHASE_1 ;
		phase_2_addr =PPS_DIV_1_PHASE_2 ; 
                width_addr   =PPS_DIV_1_WIDTH;    
		start_addr   =PPS_DIV_1_START;   
		stop_addr    =PPS_DIV_1_STOP ;    
	  case 2:
		per_true_addr=PPS_DIV_2_PER_TRUE; 
		divider_addr =PPS_DIV_2_DIV_NUM ;
		phase_0_addr =PPS_DIV_2_PHASE_0 ; 
		phase_1_addr =PPS_DIV_2_PHASE_1 ;
		phase_2_addr =PPS_DIV_2_PHASE_2 ; 
                width_addr   =PPS_DIV_2_WIDTH;    
		start_addr   =PPS_DIV_2_START;   
		stop_addr    =PPS_DIV_2_STOP ;    
	  case 3:
		per_true_addr=PPS_DIV_3_PER_TRUE; 
		divider_addr =PPS_DIV_3_DIV_NUM ;
		phase_0_addr =PPS_DIV_3_PHASE_0 ; 
		phase_1_addr =PPS_DIV_3_PHASE_1 ;
		phase_2_addr =PPS_DIV_3_PHASE_2 ; 
	        width_addr   =PPS_DIV_3_WIDTH;    
		start_addr   =PPS_DIV_3_START;   
		stop_addr    =PPS_DIV_3_STOP ;    

	} 

}

