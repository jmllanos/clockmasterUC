#include<ClockMaster.h>

UserRequest str2request (String request)
{
  if (request == "reset")
  {
    return Reset;
  }
  else if (request == "start")
  {
    return Start;
  }
  else if (request == "stop")
  {
    return Stop;
  }
  else if (request == "read")
  {
    return Read;
  }
  else if (request == "write")
  {
    return Write;
  }
  else if (request == "changeip")
  {
    return ChangeIP;
  }
  else if (request == "status")
  {
    return Status;
  }
  else if(request== "setdate")
  {
      return Setdate;
  }
  else if (request=="setpps")
  {
      return Setpps;
  }
  else if (request=="setchannels")
  {
      return SetChannels;
  }
  else
  {
    return InvalidMethod;
  }

}

// CLOCK MASTER CLASS
void ClockMaster::init()
{
    byte response[0];
WRITE_REGISTER(CH_MUX_SELECTOR,0x0f,response);

WRITE_REGISTER(CH_MUX_ENABLE,0x0f,response);

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
  }
  
}

void ClockMaster::get_divider_parameters(int channel)
{
  DEBUG_CM_PRINTLN("***************************************************");
  switch(channel)
  {
   case 0: 
	DEBUG_CM_PRINTLN("Get pps divider 0 parameters");
   	divider_0.get_parameters();
    break;

   case 1: 
    	DEBUG_CM_PRINTLN("Get pps divider 1 parameters");
   	divider_1.get_parameters();
    break;

   case 2: 
   	DEBUG_CM_PRINTLN("Get pps divider 2 parameters");
   	divider_2.get_parameters();
    break;

   case 3: 
   	DEBUG_CM_PRINTLN("Get pps divider 3 parameters");
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

void ClockMaster::set_channels(char* data)
{
    
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




