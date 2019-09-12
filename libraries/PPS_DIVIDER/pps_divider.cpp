#include<pps_divider.h>

pps_divider::pps_divider(int number)
{
  switch(number)
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

void pps_divider::set_per_true(bool per_true)
{   
  byte response[3];
  
  if(per_true)
  { 
    WRITE_CONTROLLER_REGISTER(per_true_addr,0x01,response);
  }
  else
  {
    WRITE_CONTROLLER_REGISTER(per_true_addr,0x00,response);
  }
}


bool pps_divider::get_per_true()
{
  bool per_true=false;
  byte response[3];
  READ_CONTROLLER_REGISTER(per_true_addr,response);
  
  if(response[1]==0x01)
  {
      per_true=true;
  }

  return per_true;
}


void pps_divider::set_divider(byte divider)
{
  byte response[3];
  WRITE_CONTROLLER_REGISTER(divider_addr,divider,response);
}


byte pps_divider::get_divider()
{
  byte response[3];
  READ_CONTROLLER_REGISTER(divider_addr,response);
  return response[1];
}

void pps_divider::set_phase(int phase)
{
  byte response[3]; 
  byte phase_0=phase;
  byte phase_1=(phase>>4);
  WRITE_CONTROLLER_REGISTER(phase_0_addr,phase_0,response);
}


byte pps_divider::get_phase()
{
  byte response[3];
  READ_CONTROLLER_REGISTER(phase_0_addr,response);
  return response[1];
}


void pps_divider::set_width(byte width)
{
  byte response[3];
  WRITE_CONTROLLER_REGISTER(width_addr,width,response);
}


byte pps_divider::get_width()
{
  byte response[3];
  READ_CONTROLLER_REGISTER(width_addr,response);
  return response[1];
}


void pps_divider::set_start(byte start)
{
  byte response[3];
  WRITE_CONTROLLER_REGISTER(start_addr,start,response);
}


byte pps_divider::get_start()
{
  byte response[3];
  READ_CONTROLLER_REGISTER(start_addr,response);
  return response[1];
}
