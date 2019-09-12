#ifndef _NETWROK_COMMANDS_H_
#define _NETWROK_COMMANDS_H_

#include<Arduino.h>
#include<tiva_configuration.h>
#include<EEPROM.h>
#include<IPAddress.h>
#include<ArduinoJson.h>
#include<Ethernet.h>

struct Network
{
  IPAddress ip ={IP_0_DEFAULT,
                 IP_1_DEFAULT,
                 IP_2_DEFAULT,
                 IP_3_DEFAULT};

  IPAddress dns={DNS_0_DEFAULT,
                 DNS_1_DEFAULT,
                 DNS_2_DEFAULT,
                 DNS_3_DEFAULT};

  IPAddress gateway={GATEWAY_0_DEFAULT,
                     GATEWAY_1_DEFAULT,
                     GATEWAY_2_DEFAULT,
                     GATEWAY_3_DEFAULT};

  IPAddress subnet={GATEWAY_0_DEFAULT,
                    GATEWAY_1_DEFAULT,
                    GATEWAY_2_DEFAULT,
                    GATEWAY_3_DEFAULT};
};

// Check if the network is (10.x.x.x or 192.168.x.x or 172.16.x.x)
bool CHECK_VALID_IP(Network& net);

// Save the network (ip,dns,subnet,mask) in the EEPROM
void STORE_NETWORK(Network& net);

// Load the network (ip,dns,subnet,mask) store in the EEPROM
void LOAD_NETWORK(Network& net);

void NETWORK_INIT_CONFIG(Network& net);

// GET the network values (ip,dns,subnet,mask) sent by the user
Network GET_NEW_NETWORK(char* data);

// Start ethernet connection
void START_ETH(byte* mac, Network& net, EthernetServer& server);

// Update ethernet configuration with the net values
void UPDATE_ETH_CONFIG(Network& net);


#endif
