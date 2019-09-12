#include<network_commands.h>

bool CHECK_VALID_IP(Network& net)
{
  bool network_10_x_x_x     =false;
  bool network_172_16_x_x   =false;
  bool network_192_168_x_x  =false;
  bool ip_valid=false;

  network_10_x_x_x= net.ip[0]      == 10  &&
                    net.dns[0]     == 10  &&
                    net.gateway[0] == 10;

  network_172_16_x_x= net.ip[0]      == 172 &&
                      net.ip[1]      == 16  &&
                      net.dns[0]     == 172 &&
                      net.dns[1]     == 16  &&
                      net.gateway[0] == 172 &&
                      net.gateway[1] == 16 ;

  network_192_168_x_x = net.ip[0]       == 192 &&
                        net.ip[1]       == 168 &&
                        net.dns[0]      == 192 &&
                        net.dns[1]      == 168 &&
                        net.gateway[0]  == 192 &&
                        net.gateway[1]  == 168 ;

  ip_valid= network_10_x_x_x    ||
            network_172_16_x_x  ||
            network_192_168_x_x;

  return ip_valid;
}

void STORE_NETWORK(Network& net)
{
  EEPROM.write(IP_0_ADD, net.ip[0]);
  EEPROM.write(IP_1_ADD, net.ip[1]);
  EEPROM.write(IP_2_ADD, net.ip[2]);
  EEPROM.write(IP_3_ADD, net.ip[3]);

  EEPROM.write(DNS_0_ADD, net.dns[0]);
  EEPROM.write(DNS_1_ADD, net.dns[1]);
  EEPROM.write(DNS_2_ADD, net.dns[2]);
  EEPROM.write(DNS_3_ADD, net.dns[3]);

  EEPROM.write(GATEWAY_0_ADD, net.gateway[0]);
  EEPROM.write(GATEWAY_1_ADD, net.gateway[1]);
  EEPROM.write(GATEWAY_2_ADD, net.gateway[2]);
  EEPROM.write(GATEWAY_3_ADD, net.gateway[3]);

  EEPROM.write(SUBNET_0_ADD, net.subnet[0]);
  EEPROM.write(SUBNET_1_ADD, net.subnet[1]);
  EEPROM.write(SUBNET_2_ADD, net.subnet[2]);
  EEPROM.write(SUBNET_3_ADD, net.subnet[3]);
}

void LOAD_NETWORK(Network& net)
{
  net.ip[0]=EEPROM.read(IP_0_ADD),
  net.ip[1]=EEPROM.read(IP_1_ADD),
  net.ip[2]=EEPROM.read(IP_2_ADD),
  net.ip[3]=EEPROM.read(IP_3_ADD);

  net.dns[0]=EEPROM.read(IP_0_ADD),
  net.dns[1]=EEPROM.read(IP_1_ADD),
  net.dns[2]=EEPROM.read(IP_2_ADD),
  net.dns[3]=EEPROM.read(IP_3_ADD);

  net.gateway[0]=EEPROM.read(GATEWAY_0_ADD),
  net.gateway[1]=EEPROM.read(GATEWAY_1_ADD),
  net.gateway[2]=EEPROM.read(GATEWAY_2_ADD),
  net.gateway[3]=EEPROM.read(GATEWAY_3_ADD);

  net.subnet[0]=EEPROM.read(SUBNET_0_ADD),
  net.subnet[1]=EEPROM.read(SUBNET_1_ADD),
  net.subnet[2]=EEPROM.read(SUBNET_2_ADD),
  net.subnet[3]=EEPROM.read(SUBNET_3_ADD);
}

void NETWORK_INIT_CONFIG(Network& net)
{

  Network new_network;

  LOAD_NETWORK(new_network);

  if (CHECK_VALID_IP(new_network))
    {
      net=new_network;
      DEBUG_RC_PRINTLN("Stored network configuration verified.");
    }
    else
    {
      DEBUG_RC_PRINTLN("Wrong stored network configuration");
    }
      delay(100);
}

Network GET_NEW_NETWORK(char* data)
{
  Network net;
  StaticJsonBuffer<400> jsonBuffer;
  JsonObject& network_data = jsonBuffer.parseObject(data);

  net.ip[0]=network_data["ip"][0];
  net.ip[1]=network_data["ip"][1];
  net.ip[2]=network_data["ip"][2];
  net.ip[3]=network_data["ip"][3];

  net.dns[0]=network_data["dns"][0];
  net.dns[1]=network_data["dns"][1];
  net.dns[2]=network_data["dns"][2];
  net.dns[3]=network_data["dns"][3];

  net.gateway[1]=network_data["gateway"][0];
  net.gateway[2]=network_data["gateway"][1];
  net.gateway[3]=network_data["gateway"][2];
  net.gateway[4]=network_data["gateway"][3];

  net.subnet[0]=network_data["subnet"][0];
  net.subnet[1]=network_data["subnet"][1];
  net.subnet[2]=network_data["subnet"][2];
  net.subnet[3]=network_data["subnet"][3];

  return net;
}

void START_ETH(byte* mac, Network& net, EthernetServer& server)
{
  DEBUG_RC_PRINTLN("Starting Ethernet Connection...");
  Ethernet.begin(mac, net.ip, net.dns, net.gateway, net.subnet);

  delay(1000);//#################################################

  server.begin();
  DEBUG_RC_PRINTLN("Ethernet connection ready.");
  DEBUG_RC_PRINT("Server is at ");
  DEBUG_RC_PRINTLN(Ethernet.localIP());
}

void UPDATE_ETH_CONFIG(Network& net)
{
  LOAD_NETWORK(net);

  DEBUG_RC_PRINTLN("Changing Ethernet configuration.");
  Ethernet.setStaticIP(net.ip, net.gateway, net.subnet);
  DEBUG_RC_PRINTLN("Ethernet connection ready.");
  DEBUG_RC_PRINT("Server is at ");
  DEBUG_RC_PRINTLN(Ethernet.localIP());
}


