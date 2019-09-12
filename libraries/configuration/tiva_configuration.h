#ifndef _TIVA_CONFIGURATION_H_INCLUDED
#define _TIVA_CONFIGURATION_H_INCLUDED

#define DEBUG_RC

#ifdef DEBUG_RC
#define DEBUG_RC_BEGIN(x) Serial.begin(x)
#define DEBUG_RC_PRINT(x) Serial.print(x)
#define DEBUG_RC_PRINT2(x,y) Serial.print(x,y)
#define DEBUG_RC_PRINTLN(x) Serial.println(x)
#define DEBUG_RC_PRINTLN2(x,y) Serial.println(x,y)
#else
#define DEBUG_RC_BEGIN(x)
#define DEBUG_RC_PRINT(x)
#define DEBUG_RC_PRINT2(x,y)
#define DEBUG_RC_PRINTLN(x)
#define DEBUG_RC_PRINTLN2(x,y)
#endif

#define BAUD_RATE 1000000

#define SPI_DELAY 1// us

#define LCD_ADDR 0x3C

#define REST_LED RED_LED
#define INT_LED D4_LED
#define GEAR_LED GREEN_LED

#define WRITE_ENABLE (1<<7)

#define ncycles_WDT F_CPU*8 //

//***********************
//NETWROK DEFAULT VALUES
#define IP_0_DEFAULT 10
#define IP_1_DEFAULT 10
#define IP_2_DEFAULT 10
#define IP_3_DEFAULT 100

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

//************************
// CGS configuration
#define FREQ_INT_DEFAULT 60
#define FREQ_DECIMAL_DEFAULT 0

#define DIVIDER_DEFAULT 59
#define MULT 72
#define DIV  12
#define SOURCE 1  // 1 - 10MHz, 0 - 25Mhz

//**********************
// LCD
#define CLEAR_LCD 0

// MONITOR
#define MONITOR_SELECTOR 6
#define MONITOR_ENABLE 1
#define MONITOR_SETUP (MONITOR_SELECTOR << 4) + (MONITOR_ENABLE<<3)

#endif
