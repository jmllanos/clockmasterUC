#include<ClockMaster.h>

void ClockMaster::displayInfo()
{
    ClearLCD();

 switch(LCDRowIndex)
 {
     
     case 0:
         showStatus(0);
         showIP(1);
         LCDRowIndex++;
       break;

     case 1: 
         showChannel(0);
         LCDRowIndex++;
         break;
     case 2:
          showChannel(1);
         LCDRowIndex++;
         break;
     case 3:
          showChannel(2);
         LCDRowIndex++;
         break;
     case 4:
         showChannel(3);
         LCDRowIndex=0;
         break;

 } 

}


void ClockMaster::showStatus(int row)
{
 String message;
 bool spi_ok;
 byte tmp_status;
 tmp_status=READ_REGISTER(CH_MUX_ENABLE,spi_ok);
 

 DEBUG_CM_PRINTLN("***********************");
 if(spi_ok==true)
 {
   if(tmp_status==0x0F)
   {
 //      PrintStr(0,row,"STATUS:ENABLE");
       DEBUG_CM_PRINTLN("STATUS:ENABLE");
   }
   else
   {
  //     PrintStr(0,row,"STATUS:DISABLE");
       DEBUG_CM_PRINTLN("STATUS:DISABLE");
   }

 }
 else
 {
     PrintStr(0,row,"STATUS:SPI XX");
     DEBUG_CM_PRINTLN("STATUS:SPI XX");
 }

 DEBUG_CM_PRINTLN("***********************");
}


void ClockMaster::showIP(int row)
{
 String s;
 IPAddress myip=getIP();
 char ip_0[20];
 s=String(myip[0]);
 s+=".";
 s+=String(myip[1]);
 s+=".";
 s+=String(myip[2]);
 s+=".";
 s+=String(myip[3]);
 
 strcpy(ip_0,s.c_str());
 
// PrintStr(0,row,"IP:"); 
// PrintStr(0,row+1,ip_0);  
      
 IPAddress mygate=getGateway();

 char gate[20];
 s=String(mygate[0]);
 s+=".";
 s+=String(mygate[1]);
 s+=".";
 s+=String(mygate[2]);
 s+=".";
 s+=String(mygate[3]);
 
 strcpy(gate,s.c_str());

 //PrintStr(0,row+2,"GATEWAY:"); 
 //PrintStr(0,row+3,gate);  
 
 DEBUG_CM_PRINTLN("***********************");
 DEBUG_CM_PRINTLN("IP:");
 DEBUG_CM_PRINTLN(myip);
 DEBUG_CM_PRINTLN("GATEWAY:");
 DEBUG_CM_PRINTLN(mygate);
 DEBUG_CM_PRINTLN("***********************");

}

void ClockMaster::showChannel(int channel)
{
DEBUG_CM_PRINTLN("***********************");
    switch(channel)
    {
        case 0:
           PrintStr(4,0,"CHANNEL:0"); 
           DEBUG_CM_PRINTLN("CHANNEL:0");
           channel0.getParameters(); 
           break;
        case 1:
           PrintStr(4,0,"CHANNEL:1"); 
           DEBUG_CM_PRINTLN("CHANNEL:1");
           channel1.getParameters(); 
           break;
        case 2:
           PrintStr(4,0,"CHANNEL:2"); 
           DEBUG_CM_PRINTLN("CHANNEL:2");
           channel2.getParameters(); 
           break;
        case 3:
           PrintStr(4,0,"CHANNEL:3"); 
           DEBUG_CM_PRINTLN("CHANNEL:3");
           channel3.getParameters(); 
        break;
    }

DEBUG_CM_PRINTLN("***********************");

}
