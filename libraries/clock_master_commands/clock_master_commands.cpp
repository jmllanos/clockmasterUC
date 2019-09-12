#include<clock_master_commands.h>

user_request str2request (String request)
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

/*void  clock_master_get_status(ArduinoHttpServer::StreamHttpReply& httpReply, long& rc_ram_usage)
{
  byte response[]={0x00, 0x00, 0x00};
  DEBUG_RC_PRINTLN("***************************************************");
  DEBUG_RC_PRINTLN("Radar Controller Status method.");
  READ_CONTROLLER_REGISTER(ENABLE, response);
  String status_response = "{\"status\":\"";

 if (CHECK_CORRECT_READING(response))
 {
   DEBUG_RC_PRINT("Status is: ");
   if (response[1] & R_EN == R_EN)
   {
     status_response += "enable\",\"ram_usage\":";
     DEBUG_RC_PRINTLN("Enable");
   }
   else
   {
     status_response += "disable\",\"ram_usage\":";
     DEBUG_RC_PRINTLN("Disable");
   }
 }
 else
 {
   status_response += "spi fault\",\"ram_usage\":";
   DEBUG_RC_PRINTLN("SPI FAULT!!!");
 }
 status_response += "}";
 httpReply.send(status_response);
 DEBUG_RC_PRINTLN("***************************************************");
}
*/
void clock_master_reset (ArduinoHttpServer::StreamHttpReply& httpReply, long& rc_ram_usage, bool& free_running)
{
  byte response[] = {0x0, 0x0, 0x0};
  //noInterrupts();
  DEBUG_RC_PRINTLN("***************************************************");
  DEBUG_RC_PRINTLN("Radar controller reset method:");


  DEBUG_RC_PRINTLN("Writing RESET register.");
  WRITE_CONTROLLER_REGISTER(RESET,0x00,response); // Reset chip

  if (CHECK_CORRECT_SEND_DATA(response))
  {
   httpReply.send("{\"reset\":\"ok\"}");
  }
  else
  {
   httpReply.send("{\"reset\":\"spi fault\"}");
 }
}

void clock_master_stop (ArduinoHttpServer::StreamHttpReply& httpReply)
{

}

void clock_master_start(ArduinoHttpServer::StreamHttpReply& httpReply)
{

}
void clock_master_read (ArduinoHttpServer::StreamHttpReply& httpReply, char* data)
{
    byte response[3];
    StaticJsonBuffer<400> jsonBuffer;
    JsonObject& read_request = jsonBuffer.parseObject(data);

    DEBUG_RC_PRINTLN("***************************************************");
    DEBUG_RC_PRINTLN("Radar Controller read method.");
    byte read_address = (byte)read_request["address"];
    DEBUG_RC_PRINT("Address to read: ");
    DEBUG_RC_PRINTLN(read_address);
    DEBUG_RC_PRINTLN("Requesting data.");
    READ_CONTROLLER_REGISTER(read_address, response);
    if (CHECK_CORRECT_READING(response))
    {
      String read_response = "{\"data\":\"";
      if (response[1] > 0xF)
      {
        read_response += "0x";
      }
      else
      {
        read_response += "0x0";
      }
      String temp_string = String(response[1], HEX);
      temp_string.toUpperCase();
      read_response += temp_string;
      read_response += "\"}";
      httpReply.send(read_response);
      DEBUG_RC_PRINTLN("Data read:");
      DEBUG_RC_PRINTLN(read_response);
    }
    else
    {
      httpReply.send("{\"read\":\"spi fault\"}");
      DEBUG_RC_PRINTLN("FAILED!!");
    }
    DEBUG_RC_PRINTLN("***************************************************");
}

/*void controller_write (ArduinoHttpServer::StreamHttpReply& httpReply, char* data, long data_length, long& rc_ram_usage, bool& free_running)
{
   byte response[3]={0x00, 0x00, 0x00};

   DEBUG_RC_PRINTLN("***************************************************");
   DEBUG_RC_PRINTLN("Radar Controller write method.");
   int decodedLength = Base64.decodedLength(data, data_length);
   char decodedString[decodedLength];

   DisableWatchDog(ncycles_WDT);
   Base64.decode(decodedString, data, data_length);
   EnableWatchDog(ncycles_WDT);

   DEBUG_RC_PRINT("Decoded string size: ");
   DEBUG_RC_PRINTLN(sizeof(decodedString));
   DEBUG_RC_PRINTLN("Transmitting SPI stream...");

   STREAMING_DATA(decodedString, rc_ram_usage, free_running, response);

   DEBUG_RC_PRINTLN("Transmission ended.");

   if (CHECK_CORRECT_SEND_DATA(response))
   {
     httpReply.send("{\"write\":\"ok\"}");
     LCD.position(1, 0);
     LCD.text("     WRITE DONE     ");
   }
   else
   {
     httpReply.send("{\"write\":\"spi fault\"}");
     LCD.position(1, 0);
     LCD.text("    WRITE FAILED    ");
   }
   DEBUG_RC_PRINTLN("***************************************************");
}*/

bool clock_master_changeip(ArduinoHttpServer::StreamHttpReply& httpReply, char* data)
{
  bool change_ip_flag;
  DEBUG_RC_PRINTLN("***************************************************");
  DEBUG_RC_PRINTLN("Changing IP data...");

  Network new_Net;
  new_Net=GET_NEW_NETWORK(data);

  if(CHECK_VALID_IP(new_Net))
  {
    STORE_NETWORK(new_Net);
    change_ip_flag = true;

    DEBUG_RC_PRINTLN("New Ethernet configuration received.");
    httpReply.send("{\"changeip\":\"ok\"}");
  }
  else
  {
    DEBUG_RC_PRINTLN("Wrong IP data.");
  //  ArduinoHttpServer::StreamHttpErrorReply httpReply(client, httpRequest.getContentType());
  //  httpReply.send(httpRequest.getErrorDescrition());
  }
  DEBUG_RC_PRINTLN("***************************************************");
  return change_ip_flag;
}


