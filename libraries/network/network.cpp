
#include<network.h>


void network::START_ETH(byte* mac, EthernetServer& server)
{
  DEBUG_CM_PRINTLN("Starting Ethernet Connection...");
  Ethernet.begin(mac, ip, dns, gateway, subnet);

  delay(1000);//#################################################

  server.begin();
  DEBUG_CM_PRINTLN("Ethernet connection ready.");
  DEBUG_CM_PRINT("Server is at ");
  DEBUG_CM_PRINTLN(Ethernet.localIP());
}


bool network::CHECK_VALID_IP()
{
  bool network_10_x_x_x     =false;
  bool network_172_16_x_x   =false;
  bool network_192_168_x_x  =false;

  bool gateway_valid=false;
  bool ip_valid     =false;
  bool valid_network=false;

  network_10_x_x_x= new_ip[0]      == 10  &&
                    new_dns[0]     == 10  &&
                    new_gateway[0] == 10;

  network_172_16_x_x= new_ip[0]      == 172 &&
                      new_ip[1]      == 16  &&
                      new_dns[0]     == 172 &&
                      new_dns[1]     == 16  &&
                      new_gateway[0] == 172 &&
                      new_gateway[1] == 16 ;

  network_192_168_x_x = new_ip[0]       == 192 &&
                        new_ip[1]       == 168 &&
                        new_dns[0]      == 192 &&
                        new_dns[1]      == 168 &&
                        new_gateway[0]  == 192 &&
                        new_gateway[1]  == 168 ;

 ip_valid = network_10_x_x_x    ||
            network_172_16_x_x  ||
            network_192_168_x_x;
  
  
 gateway_valid =(new_ip[0]&new_subnet[0])==(new_gateway[0] & new_subnet[0])&&
	        (new_ip[1]&new_subnet[1])==(new_gateway[1] & new_subnet[1])&&
                (new_ip[2]&new_subnet[2])==(new_gateway[2] & new_subnet[2])&&
                (new_ip[3]&new_subnet[3])==(new_gateway[3] & new_subnet[3]);

 valid_network= ip_valid && gateway_valid;

 DEBUG_CM_PRINTLN("Print gateway : ");
 DEBUG_CM_PRINTLN(new_gateway);  
 
 DEBUG_CM_PRINTLN("Print ip : ");
 DEBUG_CM_PRINTLN(new_ip);  

 DEBUG_CM_PRINTLN("Print valid network : ");
 DEBUG_CM_PRINTLN(valid_network);  

  return valid_network;
}

void network::STORE_IP()
{
  EEPROM.write(IP_0_ADD, ip[0]);
  EEPROM.write(IP_1_ADD, ip[1]);
  EEPROM.write(IP_2_ADD, ip[2]);
  EEPROM.write(IP_3_ADD, ip[3]);

  EEPROM.write(DNS_0_ADD, dns[0]);
  EEPROM.write(DNS_1_ADD, dns[1]);
  EEPROM.write(DNS_2_ADD, dns[2]);
  EEPROM.write(DNS_3_ADD, dns[3]);

  EEPROM.write(GATEWAY_0_ADD, gateway[0]);
  EEPROM.write(GATEWAY_1_ADD, gateway[1]);
  EEPROM.write(GATEWAY_2_ADD, gateway[2]);
  EEPROM.write(GATEWAY_3_ADD, gateway[3]);

  EEPROM.write(SUBNET_0_ADD, subnet[0]);
  EEPROM.write(SUBNET_1_ADD, subnet[1]);
  EEPROM.write(SUBNET_2_ADD, subnet[2]);
  EEPROM.write(SUBNET_3_ADD, subnet[3]);
}

void network::LOAD_IP()
{
  new_ip[0]=EEPROM.read(IP_0_ADD),
  new_ip[1]=EEPROM.read(IP_1_ADD),
  new_ip[2]=EEPROM.read(IP_2_ADD),
  new_ip[3]=EEPROM.read(IP_3_ADD);

  new_dns[0]=EEPROM.read(DNS_0_ADD),
  new_dns[1]=EEPROM.read(DNS_1_ADD),
  new_dns[2]=EEPROM.read(DNS_2_ADD),
  new_dns[3]=EEPROM.read(DNS_3_ADD);

  new_gateway[0]=EEPROM.read(GATEWAY_0_ADD),
  new_gateway[1]=EEPROM.read(GATEWAY_1_ADD),
  new_gateway[2]=EEPROM.read(GATEWAY_2_ADD),
  new_gateway[3]=EEPROM.read(GATEWAY_3_ADD);

  new_subnet[0]=EEPROM.read(SUBNET_0_ADD),
  new_subnet[1]=EEPROM.read(SUBNET_1_ADD),
  new_subnet[2]=EEPROM.read(SUBNET_2_ADD),
  new_subnet[3]=EEPROM.read(SUBNET_3_ADD);
}
	
void network::GET_USER_IP(char* data)
{
  StaticJsonBuffer<400> jsonBuffer;
  JsonObject& network_data = jsonBuffer.parseObject(data);

  new_ip[0]=network_data["ip"][0];
  new_ip[1]=network_data["ip"][1];
  new_ip[2]=network_data["ip"][2];
  new_ip[3]=network_data["ip"][3];

  new_dns[0]=network_data["dns"][0];
  new_dns[1]=network_data["dns"][1];
  new_dns[2]=network_data["dns"][2];
  new_dns[3]=network_data["dns"][3];

  new_gateway[0]=network_data["gateway"][0];
  new_gateway[1]=network_data["gateway"][1];
  new_gateway[2]=network_data["gateway"][2];
  new_gateway[3]=network_data["gateway"][3];

  new_subnet[0]=network_data["subnet"][0];
  new_subnet[1]=network_data["subnet"][1];
  new_subnet[2]=network_data["subnet"][2];
  new_subnet[3]=network_data["subnet"][3];
 }

void network::NETWORK_INIT_CONFIG()
{

  LOAD_IP();

  if (CHECK_VALID_IP())
    {
      ip=new_ip;
      dns=new_dns;
      gateway=new_gateway;
      subnet=new_subnet;
      
      DEBUG_CM_PRINTLN("Stored network configuration verified.");
    }
    else
    {
      DEBUG_CM_PRINTLN("Wrong stored network configuration");
    }
      delay(100);
}
	
bool network::CHANGE_IP(char* data)
{
 bool change_ip_flag=false;
 
 DEBUG_CM_PRINTLN("***************************************************");
 DEBUG_CM_PRINTLN("Changing IP data...");
 
 GET_USER_IP(data);
 
 if(CHECK_VALID_IP())
 {
  DEBUG_CM_PRINTLN("New Ethernet configuration received.");
  
  ip=new_ip;
  dns=new_dns;
  gateway=new_gateway;
  subnet=new_subnet;
  
  STORE_IP();
  change_ip_flag=true;
 }
 
 return change_ip_flag; 
}


void network::UPDATE_ETH_CONFIG()
{
  DEBUG_CM_PRINTLN("Changing Ethernet configuration.");
  Ethernet.setStaticIP(ip, gateway, subnet);
  DEBUG_CM_PRINTLN("Ethernet connection ready.");
  DEBUG_CM_PRINT("Server is at ");
  DEBUG_CM_PRINTLN(Ethernet.localIP());

  DEBUG_CM_PRINTLN("ip :");
  DEBUG_CM_PRINTLN(ip);    
  DEBUG_CM_PRINTLN("gateway :");
  DEBUG_CM_PRINTLN(gateway);
  DEBUG_CM_PRINTLN("subnet :");
  DEBUG_CM_PRINTLN(subnet);    

  
}

