#include<ClockMaster.h>

void ClockMaster::displayInfo()
{
 //row1
     ClearLCD();
 switch(LCDRow1Index)
 {
     case 0:
         showIP(1);
         showGateway(3);
         LCDRow1Index++;
         break;

     case 1: 
         showChannel(0);
         LCDRow1Index++;
         break;
     case 2:
          showChannel(1);
         LCDRow1Index++;
         break;
     case 3:
          showChannel(2);
         LCDRow1Index++;
         break;
     case 4:
         showChannel(3);
         LCDRow1Index=0;
         break;

 } 

}

void ClockMaster::showIP(int row)
{
 IPAddress myip=getIP();
 char ip_0[10];
 String s=String(myip[0]);
 s+=" ";
 s+=String(myip[1]);
 s+=" ";
 s+=String(myip[2]);
 s+=" ";
 s+=String(myip[3]);
 
 strcpy(ip_0,s.c_str());
 
 PrintStr(0,row,"IP :"); 
 PrintStr(0,row+1,ip_0);  
 
 DEBUG_CM_PRINTLN("IP:");
 DEBUG_CM_PRINTLN(myip);
     
}


void ClockMaster::showGateway(int row)
{
 IPAddress myip=getGateway();
 char ip_0[10];
 String s=String(myip[0]);
 s+=" ";
 s+=String(myip[1]);
 s+=" ";
 s+=String(myip[2]);
 s+=" ";
 s+=String(myip[3]);
 
 strcpy(ip_0,s.c_str());
 
 PrintStr(0,row,"Gateway :"); 
 PrintStr(0,row+1,ip_0);  
 
 DEBUG_CM_PRINTLN("GATEWAY:");
 DEBUG_CM_PRINTLN(myip);

}

void ClockMaster::showChannel(int channel)
{
    char message[20];

    String ch="MODE: ";
    switch(channel)
    {
        case 0:
           PrintStr(4,0,"Channel 0"); 
           ch+=channel0.getMode();
            
           break;
        case 1:
           PrintStr(4,0,"Channel 1"); 
           ch+=channel1.getMode();
    
           break;
        case 2:
           PrintStr(4,0,"Channel 2"); 
           ch+=channel2.getMode();
    
           break;
        case 3:
           PrintStr(4,0,"Channel 3"); 
           ch+=channel3.getMode();

        break;
    }

   strcpy(message,ch.c_str());
   PrintStr(0,1,message);
   
   DEBUG_CM_PRINT("CHANNEL ");
   DEBUG_CM_PRINTLN(channel);
   DEBUG_CM_PRINTLN(ch);

}
