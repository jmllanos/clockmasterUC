#include<ClockMaster.h>

// CLOCK MASTER CLASS
void ClockMaster::init()
{
    byte response[3];
   WRITE_REGISTER(CH_MUX_SELECTOR,0x00,response);
   READ_REGISTER(CH_MUX_SELECTOR,response);
   DEBUG_CM_PRINTLN("MUX SELECTOR");
   DEBUG_CM_PRINTLN2(response[1],HEX);

   WRITE_REGISTER(CH_MUX_ENABLE,0x00,response);
   READ_REGISTER(CH_MUX_ENABLE,response);
   DEBUG_CM_PRINTLN("MUX ENABLE");
   DEBUG_CM_PRINTLN2(response[1],HEX);

  divider_0.set_channel(0);
  divider_1.set_channel(1);
  divider_2.set_channel(2);
  divider_3.set_channel(3);
  
  PulseGen_0.set_channel(0);
  PulseGen_1.set_channel(1);
  PulseGen_2.set_channel(2);
  PulseGen_3.set_channel(3);
}

void ClockMaster::set_divider(char* data)
{
  PPSDivider tmp;    
  tmp.get_user_parameters(data);
  DEBUG_CM_PRINTLN("***************************************************");
  switch(tmp.get_channel())
  {
     case 0:
   	DEBUG_CM_PRINTLN("Setting pps divider Nº0 parameters");
     	divider_0=tmp;     	
     	divider_0.set_parameters();
   	break;
     case 1:
   	DEBUG_CM_PRINTLN("Setting pps divider Nº1 parameters");
     	divider_1=tmp;
     	divider_1.set_parameters();
   	break;    
     case 2:
   	DEBUG_CM_PRINTLN("Setting pps divider Nº2 parameters");
     	divider_2=tmp;
     	divider_2.set_parameters();
     	break;
     case 3:
   	DEBUG_CM_PRINTLN("Setting pps divider Nº3 parameters");
     	divider_3=tmp;
     	divider_3.set_parameters();
     	break;
  DEBUG_CM_PRINTLN("***************************************************");
  }
  
}

void ClockMaster::get_divider_parameters(int channel)
{
  DEBUG_CM_PRINTLN("***************************************************");
  switch(channel)
  {
   case 0: 
	DEBUG_CM_PRINTLN("PPS divider Nº0 parameters :");
   	divider_0.get_parameters();
    break;

   case 1: 
    DEBUG_CM_PRINTLN("PPS divider Nº1 parameters :");
   	divider_1.get_parameters();
    break;

   case 2: 
   	DEBUG_CM_PRINTLN("PPS divider Nº2 parameters :");
   	divider_2.get_parameters();
    break;

   case 3: 
   	DEBUG_CM_PRINTLN("PPS divider Nº3 parameters :");
   	divider_3.get_parameters();
    break;
  }
}



void ClockMaster::get_pulsegen_parameters(int channel)
{
  DEBUG_CM_PRINTLN("***************************************************");
  switch(channel)
  {
   case 0: 
	DEBUG_CM_PRINTLN("Pulse Generator Nº0 parameters: ");
   	PulseGen_0.get_parameters();
    break;

   case 1: 
   	DEBUG_CM_PRINTLN("Pulse Generator Nº1 parameters: ");
   	PulseGen_1.get_parameters();
    break;

   case 2: 
   	DEBUG_CM_PRINTLN("Pulse Generator Nº2 parameters: ");
   	PulseGen_2.get_parameters();
    break;

   case 3: 
   	DEBUG_CM_PRINTLN("Pulse Generator Nº3 parameters: ");
   	PulseGen_3.get_parameters();
    break;
  }
  DEBUG_CM_PRINTLN("***************************************************");
}


void ClockMaster::set_pulsegen(char* data)
{
  PulseGenerator tmp;    
  tmp.get_user_parameters(data);
  
  DEBUG_CM_PRINTLN("***************************************************");
  switch(tmp.get_channel())
  {
     case 0:
         DEBUG_CM_PRINTLN("Setting pulse generator Nº0 parameters");
         PulseGen_0=tmp;     	
         PulseGen_0.set_parameters();
   	
   	break;
     case 1:
    	DEBUG_CM_PRINTLN("Setting pulse generator Nº1 parameters");
     	PulseGen_1=tmp;
     	PulseGen_1.set_parameters();
   
   	break;    
     case 2:
       	DEBUG_CM_PRINTLN("Setting pulse generator Nº2 parameters");
     	PulseGen_2=tmp;
     	PulseGen_2.set_parameters();
     	break;
     case 3:
    	DEBUG_CM_PRINTLN("Setting pulse generator Nº3 parameters");
     	PulseGen_3=tmp;
     	PulseGen_3.set_parameters();
     	break;
  }
  
  DEBUG_CM_PRINTLN("***************************************************");
}


String ClockMaster::reset()
{
  String reply;
  byte response[] = {0x0, 0x0, 0x0};
  //noInterrupts();
  DEBUG_CM_PRINTLN("***************************************************");
  DEBUG_CM_PRINTLN("Clock Master reset method:");


  DEBUG_CM_PRINTLN("Writing RESET register.");
  WRITE_REGISTER(RESET,0x00,response); // Reset chip

  if (CHECK_CORRECT_WRITING(response))
  {
   reply="{\"reset\":\"ok\"}";
  }
  else
  {
   reply="{\"reset\":\"spi fault\"}";
 }

return reply;
}


void ClockMaster::set_channels_muxes(char* data)
{
  StaticJsonBuffer<400> jsonBuffer;
  JsonObject& channels_muxes_data = jsonBuffer.parseObject(data);
  
channels_mux_enable = (byte)channels_muxes_data["channelEnable"][0];
channels_mux_selector  = (byte)channels_muxes_data["muxSelector"][0];
byte response[3];
WRITE_REGISTER(CH_MUX_SELECTOR,channels_mux_selector,response);
READ_REGISTER(CH_MUX_SELECTOR,response);
DEBUG_CM_PRINTLN("CHANNEL MUX SELECTOR");
DEBUG_CM_PRINTLN(response[1]);


WRITE_REGISTER(CH_MUX_ENABLE,channels_mux_enable,response);
READ_REGISTER(CH_MUX_ENABLE,response);
DEBUG_CM_PRINTLN("CHANNEL MUX ENABLE");
DEBUG_CM_PRINTLN(response[1]);

}


