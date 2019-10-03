#include <Ethernet.h>
#include <Base64.h>
#include <ArduinoJson.h>
#include <Wire.h>
#include <SPI.h>
#include <string.h>
//#include "WatchdogMan.h"
#include "Energia.h"
#include "inc/hw_memmap.h"
#include "inc/hw_types.h"
#include "inc/hw_ints.h"
#include "driverlib/debug.h"
#include "driverlib/interrupt.h"
#include "driverlib/sysctl.h"
#include "driverlib/timer.h"

#include <ArduinoHttpServer.h>
#include <EEPROM.h>

#include <TIVAConfiguration.h>
#include <ClockMaster.h>
#include <Nokia_5110_AC2.h>


//###################################################
uint32_t invalid = 0;//bool
uint32_t gps_disciplined;
uint32_t ref;

const int buttonPin = PUSH2;//forced freeze

uint8_t freeze_counter = 0;

//#######################################################
int int_delay = 40;
boolean gear = false;
bool change_ip_flag = false;

EthernetServer server(SERVER_PORT);
EthernetClient client;
byte mac[] = {0x08, 0x00,0x28,0x5A,0x83,0xFE};
byte response[] = {0x0, 0x0, 0x0};

volatile uint8_t state = 0;

ClockMaster clock_master;
//***********************************************

void setup()
{
 // ConfigWatchDog(ncycles_WDT);
  DEBUG_CM_BEGIN(BAUD_RATE);
  DEBUG_CM_PRINTLN("Serial started.");
  pinMode(PL_2,OUTPUT);
  digitalWrite(PL_2,HIGH);
  delay(1500);
  digitalWrite(PL_2,LOW);
//Reset TINY FPGA
  clock_master.NetworkInitConfig();
//INIT_I2C();
  INIT_SPI();
  clock_master.startEth(mac, server);
  initTimer(1); // timer a 0.5 hz..................
  pinMode(buttonPin, INPUT_PULLUP);
  //ResetWatchDogTimer(ncycles_WDT);
 clock_master.init();
}


void loop()
{
  
   //ResetWatchDogTimer(ncycles_WDT);

  //TEST_WATCHDOG();

  if(change_ip_flag)
  {
    clock_master.updateEthConfig();
    change_ip_flag=false;
  }

  client = server.available();
   
  if (client.connected())
  { 
    // Connected to client. Allocate and initialize StreamHttpRequest object.
    ArduinoHttpServer::StreamHttpRequest<80000> httpRequest(client);
    ArduinoHttpServer::StreamHttpReply httpReply(client, "application/json");
     
    String error_message;
    // Parse the request
    if (httpRequest.readRequest())
    {
      
      // Retrieve 2nd part of HTTP resource.
      // E.g.: "on" from "/api/sensors/on"
      char* data = (char*) httpRequest.getBody();
      long data_length = (long) httpRequest.getContentLength();
      DEBUG_CM_PRINTLN();
      DEBUG_CM_PRINTLN("We have a new request!!!!");
      DEBUG_CM_PRINT("Request length: ");
      DEBUG_CM_PRINTLN(data_length);
      DEBUG_CM_PRINT("Request type: ");
      DEBUG_CM_PRINTLN( httpRequest.getResource()[0] );
      DEBUG_CM_PRINTLN("Data received: ");
      DEBUG_CM_PRINTLN(data);
      DEBUG_CM_PRINTLN();

     
      // Retrieve HTTP method.
      // E.g.: GET / PUT / HEAD / DELETE /ip[3]=ip_data["ip"][3];
      ArduinoHttpServer::MethodEnum method( ArduinoHttpServer::MethodInvalid);
      method = httpRequest.getMethod();
      
      if ( method == ArduinoHttpServer::MethodGet)
      {
        digitalWrite(REST_LED, HIGH);
        switch (str2request(httpRequest.getResource()[0]))
        {
          case Status:
            clock_master.getStatus();
            httpReply.send(clock_master.getReplyMessage()); 
            break;
          
          case InvalidMethod:
            DEBUG_CM_PRINTLN("********************************************");
            ArduinoHttpServer::StreamHttpErrorReply httpReply(client, httpRequest.getContentType());
            httpReply.send(httpRequest.getErrorDescrition());
            DEBUG_CM_PRINTLN("WRONG REST REQUEST RECEIVED!!!");
            DEBUG_CM_PRINTLN("********************************************");
            break;
        }
        digitalWrite(REST_LED, LOW);
      }
      else if ( method == ArduinoHttpServer::MethodPost)
      {
        
        digitalWrite(REST_LED, HIGH);
        switch (str2request(httpRequest.getResource()[0]))
        {      
          case Reset:
          
            break;
            
          case Start:
            clock_master.start();
            httpReply.send(clock_master.getReplyMessage());
            break;
            
          case Stop:
            clock_master.stop();
            httpReply.send(clock_master.getReplyMessage());
            break;
                            
          case Setdate:
            clock_master.setPulsegen(data); 
            httpReply.send(clock_master.getReplyMessage());
            break;
                               
          case Setpps:
           clock_master.setDivider(data); 
            httpReply.send(clock_master.getReplyMessage());
           break;
          
          case ChangeIP:
          
            change_ip_flag=clock_master.changeIP(data);
            if(change_ip_flag)
            {
              httpReply.send("{\"changeip\":\"ok\"}"); 
            }
            else
            {
              DEBUG_CM_PRINTLN("********************************************");
              ArduinoHttpServer::StreamHttpErrorReply httpReply(client, httpRequest.getContentType());
              httpReply.send(httpRequest.getErrorDescrition());
              DEBUG_CM_PRINTLN("WRONG IP DATA!!");
              DEBUG_CM_PRINTLN("********************************************");
            }           
            break;
          
          case InvalidMethod:
            DEBUG_CM_PRINTLN("********************************************");
            ArduinoHttpServer::StreamHttpErrorReply httpReply(client, httpRequest.getContentType());
            httpReply.send(httpRequest.getErrorDescrition());
            DEBUG_CM_PRINTLN("WRONG REST REQUEST RECEIVED!!!");
            DEBUG_CM_PRINTLN("********************************************");
            break;
        }
        digitalWrite(REST_LED, LOW);
      }
      else
      {
        DEBUG_CM_PRINTLN("METHOD NOT VALID");
        ArduinoHttpServer::StreamHttpErrorReply httpReply(client, httpRequest.getContentType());
        httpReply.send(httpRequest.getErrorDescrition());
      }
    }
    else
    {
      ArduinoHttpServer::StreamHttpErrorReply httpReply(client, httpRequest.getContentType());
      httpReply.send(httpRequest.getErrorDescrition());
    }
  }

  client.stop();

 delay(1000);

}

void TEST_WATCHDOG()
{
  int reading = digitalRead(buttonPin);
  if (reading != 1)
  {
    DEBUG_CM_PRINTLN("*******");
    DEBUG_CM_PRINTLN("FORCED SYSTEM FREEZE");
    DEBUG_CM_PRINTLN("*******");
    while(1);
  }
}

void initTimer(unsigned Hz)
{
  SysCtlPeripheralEnable(SYSCTL_PERIPH_TIMER1);
  IntMasterEnable();
  TimerConfigure(TIMER1_BASE, TIMER_CFG_PERIODIC);
  unsigned long ulPeriod = (120000000 / Hz) * 2;//4
  TimerLoadSet(TIMER1_BASE, TIMER_A, ulPeriod);
  IntEnable(INT_TIMER1A);
  TimerIntEnable(TIMER1_BASE, TIMER_TIMA_TIMEOUT);
  TimerIntRegister(TIMER1_BASE, TIMER_A, Timer1IntHandler);
  TimerEnable(TIMER1_BASE, TIMER_A);
}

void Timer1IntHandler()
{
  digitalWrite(INT_LED, HIGH);
  TimerIntClear(TIMER1_BASE, TIMER_TIMA_TIMEOUT);
  gear = true;
}

void INIT_SPI()
{
  SPI.setModule(4);
  SPI.setBitOrder(MSBFIRST);
  SPI.setClockDivider(30);
  SPI.begin();
}

void INIT_I2C()
{
  Wire.setModule(0);
  Wire.begin();
  delay(1000);//----------------------????????????????????????????????
  //el delay se ejecuta antes de q acabe wire begin por eso es q se 
  //imprime la siguiente linea....
  
  DEBUG_CM_PRINTLN("I2C initialized");

  Wire.beginTransmission(2);
  Wire.write(0x00);//Comsend = 0x00
  Wire.write(0x38);
  uint8_t err = Wire.endTransmission();
  DEBUG_CM_PRINTLN(err);

  DEBUG_CM_PRINTLN("pase i2c sin conexion");
  //----------------###################################revisar colgado por pull ups
}
