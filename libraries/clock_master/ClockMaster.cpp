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
  else
  {
    return Error;
  }

}

// CLOCK MASTER CLASS
ClockMaster::ClockMaster()
{
  divider_0.set_channel(0);
  divider_1.set_channel(1);
  divider_2.set_channel(2);
  divider_3.set_channel(3);
}


void ClockMaster::set_divider(char* data)
{
  PPSDivider tmp;    
  tmp.get_user_parameters(data);
  DEBUG_CM_PRINTLN("***************************************************");
  switch(tmp.get_channel())
  {
     case 0:
     	divider_0=tmp;
     	divider_0.set_parameters();
   	DEBUG_CM_PRINTLN("Set pps divider 0 parameters");
   	break;
     case 1:
     	divider_1=tmp;
     	divider_1.set_parameters();
   	DEBUG_CM_PRINTLN("Set pps divider 1 parameters");
   	break;    
     case 2:
     	divider_2=tmp;
     	divider_2.set_parameters();
   	DEBUG_CM_PRINTLN("Set pps divider 2 parameters");
     	break;
     case 3:
     	divider_3=tmp;
     	divider_3.set_parameters();
   	DEBUG_CM_PRINTLN("Set pps divider 3 parameters");
     	break;
  }
  
}

void ClockMaster::get_divider_parameters(int channel)
{
  DEBUG_CM_PRINTLN("***************************************************");
  switch(channel)
  {
   case 0: 
   	divider_0.get_channel();
   	DEBUG_CM_PRINTLN("Get pps divider 0 parameters");
    break;

   case 1: 
   	divider_1.get_channel();
    	DEBUG_CM_PRINTLN("Get pps divider 1 parameters");
    break;

   case 2: 
   	divider_2.get_channel();
   	DEBUG_CM_PRINTLN("Get pps divider 2 parameters");
    break;

   case 3: 
   	divider_3.get_channel();
   	DEBUG_CM_PRINTLN("Get pps divider 3 parameters");
    break;
  }
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




