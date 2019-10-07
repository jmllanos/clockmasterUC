#ifndef _NETWORK_H_
#define _NETWORK_H_

#include<Arduino.h>
#include<TIVAConfiguration.h>
#include<EEPROM.h>
#include<IPAddress.h>
#include<ArduinoJson.h>
#include<Ethernet.h>
#include <string.h>


class network
{
  private:
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
                    
   IPAddress new_ip;
   IPAddress new_dns;
   IPAddress new_gateway;
   IPAddress new_subnet;
   
   bool checkValidIP();	
   void storeIP();
   void loadIP();
   void getUserIP(char* data);
  
  public:
  
	bool changeIP(char* data);
	void NetworkInitConfig();
	void startEth(byte* mac, EthernetServer& server);
	void updateEthConfig();
	
	IPAddress getIP();
	IPAddress getGateway();
};



#endif
