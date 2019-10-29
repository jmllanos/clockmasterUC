#ifndef _TIVA_CONFIGURATION_H_INCLUDED
#define _TIVA_CONFIGURATION_H_INCLUDED

#define DEBUG_RC

#ifdef DEBUG_RC
#define DEBUG_CM_BEGIN(x) Serial.begin(x)
#define DEBUG_CM_PRINT(x) Serial.print(x)
#define DEBUG_CM_PRINT2(x,y) Serial.print(x,y)
#define DEBUG_CM_PRINTLN(x) Serial.println(x)
#define DEBUG_CM_PRINTLN2(x,y) Serial.println(x,y)
#else
#define DEBUG_CM_BEGIN(x)
#define DEBUG_CM_PRINT(x)
#define DEBUG_CM_PRINT2(x,y)
#define DEBUG_CM_PRINTLN(x)
#define DEBUG_CM_PRINTLN2(x,y)
#endif

#define BAUD_RATE 1000000

#define SPI_DELAY 1// us

#define LCD_ADDR 0x3C

#define REST_LED RED_LED
#define INT_LED D4_LED
#define GEAR_LED GREEN_LED

#define WRITE_ENABLE (1<<7)

#define ncycles_WDT F_CPU*8 //

//**********************
//** LCD ILI9341******* 
// SPI_SW PINS
#define TFT_DC   PC_5
#define TFT_CS   PE_5
#define TFT_MOSI PC_4
#define TFT_CLK  PE_4
#define TFT_RST  PC_6
#define TFT_MISO PD_3
//  TEXT SIZE;
#define TEXTWIDTH  3
#define TEXTHEIGHT 5
//  Colors
#define BACKGROUND  ILI9341_BLACK
#define TEXTCOLOR   ILI9341_WHITE       

//***********************
//NETWROK DEFAULT VALUES
#define IP_0_DEFAULT 10
#define IP_1_DEFAULT 10
#define IP_2_DEFAULT 10
#define IP_3_DEFAULT 119

#define DNS_0_DEFAULT 10
#define DNS_1_DEFAULT 10
#define DNS_2_DEFAULT 10
#define DNS_3_DEFAULT 1

#define GATEWAY_0_DEFAULT 10
#define GATEWAY_1_DEFAULT 10
#define GATEWAY_2_DEFAULT 10
#define GATEWAY_3_DEFAULT 1

#define SUBNET_0_DEFAULT 255
#define SUBNET_1_DEFAULT 255
#define SUBNET_2_DEFAULT 255
#define SUBNET_3_DEFAULT 0

// SERVER PORT
#define SERVER_PORT 80

//********************************
//EEPPROM ADDRESS
//Network config address
#define IP_0_ADD 0
#define IP_1_ADD 1
#define IP_2_ADD 2
#define IP_3_ADD 3

#define DNS_0_ADD 4
#define DNS_1_ADD 5
#define DNS_2_ADD 6
#define DNS_3_ADD 7

#define GATEWAY_0_ADD 8
#define GATEWAY_1_ADD 9
#define GATEWAY_2_ADD 10
#define GATEWAY_3_ADD 11

#define SUBNET_0_ADD 12
#define SUBNET_1_ADD 13
#define SUBNET_2_ADD 14
#define SUBNET_3_ADD 15

// CGS frequency config address
#define FREQ_INT_ADD         100
#define FREQ_FRAC_ADD        101
#define FREQ_FRAC_TEXT_0_ADD 110
#define FREQ_FRAC_TEXT_1_ADD 111
#define FREQ_FRAC_TEXT_2_ADD 112
#define REF_TEXT_0_ADDR      120
#define REF_TEXT_1_ADDR      121
#define REF_TEXT_2_ADDR      122
#define REF_TEXT_3_ADDR      123
#define REF_TEXT_4_ADDR      124
#define REF_TEXT_5_ADDR      125

// SYSTEM FREEZE COUNTER
#define FREEZE_COUNTER_ADDR     130

//********************************
//// CLOCK MASTER
// CHANNELS
#define ENABLE_CHANNElS  0x0F
#define DISABLE_CHANNELS 0x00
#define NumberOfChannels 4  

// PULSE GENERATOR
#define ENABLE_PULSEGEN 0x01
#define DISABLE_PULSEGEN 0x00


#endif
