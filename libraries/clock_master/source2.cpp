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

void thunderbolt::read_time()
{ 
    bool spi_ok=true;
    int year;
    DEBUG_CM_PRINTLN("******************");
    DEBUG_CM_PRINTLN("THUNDERBOLT TIME RECEIVED");
    byte response[3];
    READ_REGISTER(THUNDER_YEAR_L,response);
    spi_ok = CHECK_CORRECT_READING(response) & spi_ok;
    year=response[1];

    READ_REGISTER(THUNDER_YEAR_H,response);
    spi_ok = CHECK_CORRECT_READING(response) & spi_ok;
    year=(response[1]<<8)|year;

    DEBUG_CM_PRINTLN("Year: ");
    DEBUG_CM_PRINTLN(year);
  
    READ_REGISTER(THUNDER_MONTH,response);
    DEBUG_CM_PRINTLN("Month: ");
    DEBUG_CM_PRINTLN(response[1]);
    spi_ok = CHECK_CORRECT_READING(response) & spi_ok;

    READ_REGISTER(THUNDER_DAY,response);
    DEBUG_CM_PRINTLN("Day: ");
    DEBUG_CM_PRINTLN(response[1]);
    spi_ok = CHECK_CORRECT_READING(response) & spi_ok;

    READ_REGISTER(THUNDER_HOUR,response);
    DEBUG_CM_PRINTLN("Hour: ");
    DEBUG_CM_PRINTLN(response[1]);
    spi_ok = CHECK_CORRECT_READING(response) & spi_ok;

    READ_REGISTER(THUNDER_MINUTES,response);
    DEBUG_CM_PRINTLN("Minute: ");
    DEBUG_CM_PRINTLN(response[1]);
    spi_ok = CHECK_CORRECT_READING(response) & spi_ok;
   
    READ_REGISTER(THUNDER_SECONDS,response);
    DEBUG_CM_PRINTLN("Seconds: ");
    DEBUG_CM_PRINTLN(response[1]);
    spi_ok = CHECK_CORRECT_READING(response) & spi_ok;

    if(spi_ok==false)
    {
        DEBUG_CM_PRINTLN("SPI FAULT !!!");
    }
    DEBUG_CM_PRINTLN("******************");

}


