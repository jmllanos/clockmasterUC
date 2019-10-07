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
  else if (request=="setchannel")
  {
      return SetChannel;
  }
  else
  {
    return InvalidMethod;
  }

}

void thunderbolt::readTime()
{ 
    bool spi_ok=true;
    int year;
    byte tmp;
    
    DEBUG_CM_PRINTLN("******************");
    DEBUG_CM_PRINTLN("THUNDERBOLT TIME RECEIVED");
    
    year=READ_REGISTER(THUNDER_YEAR_L,spi_ok);
    
    tmp=READ_REGISTER(THUNDER_YEAR_H,spi_ok);
    year=(tmp<<8)|year;

    DEBUG_CM_PRINTLN("Year: ");
    DEBUG_CM_PRINTLN(year);
  
    tmp=READ_REGISTER(THUNDER_MONTH,spi_ok);
    DEBUG_CM_PRINTLN("Month: ");
    DEBUG_CM_PRINTLN(tmp);

    tmp=READ_REGISTER(THUNDER_DAY,spi_ok);
    DEBUG_CM_PRINTLN("Day: ");
    DEBUG_CM_PRINTLN(tmp);

    tmp=READ_REGISTER(THUNDER_HOUR,spi_ok);
    DEBUG_CM_PRINTLN("Hour: ");
    DEBUG_CM_PRINTLN(tmp);

    tmp=READ_REGISTER(THUNDER_MINUTES,spi_ok);
    DEBUG_CM_PRINTLN("Minute: ");
    DEBUG_CM_PRINTLN(tmp);
   
    tmp=READ_REGISTER(THUNDER_SECONDS,spi_ok);
    DEBUG_CM_PRINTLN("Seconds: ");
    DEBUG_CM_PRINTLN(tmp);

    DEBUG_CM_PRINTLN("******************");

}


