#include <Ethernet.h>
#include <Base64.h>
#include <ArduinoJson.h>
#include <Wire.h>
#include <SPI.h>
#include <string.h>
#include "WatchdogMan.h"
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

#include <tiva_configuration.h>
#include <clock_master_commands.h>
#include <read_write_registers.h>
#include <network_commands.h>
#include <pps_divider.h>

//###################################################
uint32_t invalid = 0;//bool
uint32_t multiplier;
uint32_t divider;
uint32_t gps_disciplined;
uint32_t ref;

uint32_t bauds = 1;
uint32_t ipp = 0;
uint32_t ntx = 0;
uint32_t n_samples = 0;

const int buttonPin = PUSH2;//forced freeze

uint8_t freeze_counter = 0;

//#######################################################
int int_delay = 40;
boolean gear = false;
bool change_ip_flag = false;

EthernetServer server(SERVER_PORT);
EthernetClient client;
byte mac[] = {0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED};
byte response[] = {0x0, 0x0, 0x0};

Network RC_Network;

volatile uint8_t state = 0;

//***********************************************
pps_divider pps_divider_0(0);
pps_divider pps_divider_1(1);
pps_divider pps_divider_2(2);
pps_divider pps_divier_3(3);

void setup()
{
  ConfigWatchDog(ncycles_WDT);

  DEBUG_RC_BEGIN(BAUD_RATE);
  DEBUG_RC_PRINTLN("Serial started.");
  pinMode(REST_LED, OUTPUT);
  pinMode(GEAR_LED, OUTPUT);
  pinMode(INT_LED, OUTPUT);
  DEBUG_RC_PRINTLN("Leds configured.");
  //revisar!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

  NETWORK_INIT_CONFIG(RC_Network);

  INIT_I2C();

  INIT_SPI();
  
  //Reset chip
  WRITE_CONTROLLER_REGISTER(RESET,0x00,response);

  START_ETH(mac, RC_Network, server);

  initTimer(1); // timer a 0.5 hz..................

  pinMode(buttonPin, INPUT_PULLUP);

  ResetWatchDogTimer(ncycles_WDT);

}


void loop()
{

}

void TEST_WATCHDOG()
{
  int reading = digitalRead(buttonPin);
  if (reading != 1)
  {
    DEBUG_RC_PRINTLN("*******");
    DEBUG_RC_PRINTLN("FORCED SYSTEM FREEZE");
    DEBUG_RC_PRINTLN("*******");
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
  SPI.begin();
  SPI.setClockDivider(30);
}

void INIT_I2C()
{
  Wire.setModule(0);
  Wire.begin();
  delay(1000);//----------------------????????????????????????????????
  //el delay se ejecuta antes de q acabe wire begin por eso es q se 
  //imprime la siguiente linea....
  
  DEBUG_RC_PRINTLN("I2C initialized");

  DEBUG_RC_PRINTLN("duuuuuuuuuuuuuh");

  Wire.beginTransmission(2);
  Wire.write(0x00);//Comsend = 0x00
  Wire.write(0x38);
  uint8_t err = Wire.endTransmission();
  DEBUG_RC_PRINTLN(err);

  DEBUG_RC_PRINTLN("pase i2c sin conexion");
  //----------------###################################revisar colgado por pull ups
}
