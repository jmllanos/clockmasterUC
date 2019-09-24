#include<PPSDivider.h>

void PPSDivider::set_channel(int _channel)
{
  channel=_channel;
  set_registers();
}

int PPSDivider::get_channel()
{
  return channel;
}

void PPSDivider::set_parameters()
{
    byte phase_0=phase;
    byte phase_1=phase>>8;
    byte phase_2=phase>>12;
   
    bool spi_ok= true;
    byte response[3];

    DEBUG_CM_PRINTLN("**************************************************");
    DEBUG_CM_PRINTLN("WRITING PPS DIVIDER REGISTERS WITH USER PARAMETERS");
    
    WRITE_REGISTER(per_true_addr,per_true,response);
    spi_ok = CHECK_CORRECT_READING(response) & spi_ok;

    WRITE_REGISTER(divider_addr,divider,response);
    spi_ok = CHECK_CORRECT_READING(response) & spi_ok;
   
    WRITE_REGISTER(phase_0_addr,phase_0,response);
    spi_ok = CHECK_CORRECT_READING(response) & spi_ok;
    
    WRITE_REGISTER(phase_1_addr,phase_1,response);
    spi_ok = CHECK_CORRECT_READING(response) & spi_ok;
    
    WRITE_REGISTER(phase_2_addr,phase_2,response);
    spi_ok = CHECK_CORRECT_READING(response) & spi_ok;
    
    WRITE_REGISTER(width_addr,width,response);
    spi_ok = CHECK_CORRECT_READING(response) & spi_ok;
    
    WRITE_REGISTER(start_addr,start,response);
    spi_ok = CHECK_CORRECT_READING(response) & spi_ok;
    
    WRITE_REGISTER(stop_addr,stop,response);
    spi_ok = CHECK_CORRECT_READING(response) & spi_ok;

    if(spi_ok==false)
    {
      DEBUG_CM_PRINTLN("SPI FAULT !!!");
    }

    DEBUG_CM_PRINTLN("**************************************************");

    get_parameters();
}

void PPSDivider::get_parameters()
{
   
    long user_phase;

    bool spi_ok= true;
    byte response[3];

    DEBUG_CM_PRINTLN("**************************************************");
    DEBUG_CM_PRINTLN("READING PPS DIVIDER REGISTERS");
    
    WRITE_REGISTER(per_true_addr,per_true,response);
    spi_ok = CHECK_CORRECT_READING(response) & spi_ok;
    
    READ_REGISTER(per_true_addr,response);
    spi_ok = CHECK_CORRECT_READING(response) & spi_ok;
    DEBUG_CM_PRINTLN("Periodic True");
    DEBUG_CM_PRINTLN(response[1]);       
    DEBUG_CM_PRINTLN2(per_true_addr,HEX);

    READ_REGISTER(divider_addr,response);
    spi_ok = CHECK_CORRECT_READING(response) & spi_ok;
    DEBUG_CM_PRINTLN("Divider Number");
    DEBUG_CM_PRINTLN(response[1]);       
    DEBUG_CM_PRINTLN2(divider_addr,HEX);
    
    READ_REGISTER(phase_0_addr,response);
    spi_ok = CHECK_CORRECT_READING(response) & spi_ok;
    user_phase=response[1];
    DEBUG_CM_PRINTLN2(phase_0_addr,HEX);

    READ_REGISTER(phase_1_addr,response);
    spi_ok = CHECK_CORRECT_READING(response) & spi_ok;
    user_phase=(response[1]<<8)|user_phase;
    
    READ_REGISTER(phase_2_addr,response);
    spi_ok = CHECK_CORRECT_READING(response) & spi_ok;
    user_phase=(response[1]<<16)|user_phase;
   
    DEBUG_CM_PRINTLN("Phase");
    DEBUG_CM_PRINTLN(user_phase);
    
    READ_REGISTER(width_addr,response);
    spi_ok = CHECK_CORRECT_READING(response) & spi_ok;
    DEBUG_CM_PRINTLN("width ");
    DEBUG_CM_PRINTLN(response[1]);       
    DEBUG_CM_PRINTLN2(width_addr,HEX);
    
    READ_REGISTER(start_addr,response);
    spi_ok = CHECK_CORRECT_READING(response) & spi_ok;
    DEBUG_CM_PRINTLN("start ");
    DEBUG_CM_PRINTLN(response[1]);       
    DEBUG_CM_PRINTLN2(start_addr,HEX);
    
    READ_REGISTER(stop_addr,response);
    spi_ok = CHECK_CORRECT_READING(response) & spi_ok;
    DEBUG_CM_PRINTLN("stop");
    DEBUG_CM_PRINTLN(response[1]);       
    DEBUG_CM_PRINTLN2(stop_addr,HEX);
    
    if(spi_ok==false)
    {
      DEBUG_CM_PRINTLN("SPI FAULT !!!");
    }

    DEBUG_CM_PRINTLN("**************************************************");
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
        DEBUG_CM_PRINTLN("Set channel Nº0"); 
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
        DEBUG_CM_PRINTLN("Set channel Nº1"); 
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
        DEBUG_CM_PRINTLN("Set channel Nº2"); 
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
        DEBUG_CM_PRINTLN("Set channel Nº3"); 
        break;

      default:
        DEBUG_CM_PRINTLN("INVALID CHANNEL");

	} 

}

