#include<ClockMaster.h>

void ClockMaster::displayInfo()
{
   
    
   tft.setCursor(0,0);
   tft.setTextColor(BACKGROUND); 
   tft.println(lcdmessage);
   
   tft.setCursor(0,0);
   tft.setTextColor(TEXTCOLOR);

 switch(LCDRowIndex)
 {  
     case 0:
        
         showStatus();
         showIP();
  
         tft.println(lcdmessage);
             
         LCDRowIndex++;
       break;

     case 1:
    
         showChannel(0);
         
         tft.println(lcdmessage);
         
         LCDRowIndex++;
         break;
     case 2:
         
  
         showChannel(1);
         
         tft.println(lcdmessage);
         
         LCDRowIndex++;
         break;
     case 3:
     
         showChannel(2);
 
         tft.println(lcdmessage);
         
         LCDRowIndex++;
         break;
         
     case 4:
         
         showChannel(3);
         
         tft.println(lcdmessage);
         
         LCDRowIndex++;
         break;
     
     case 5:
     	
     	 showCGS();
     	 tft.println(lcdmessage);
         
         LCDRowIndex=0;
     	break;

 } 
 

}


void ClockMaster::showStatus()
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
       
       lcdmessage="STATUS: ENABLE";
       DEBUG_CM_PRINTLN("STATUS:ENABLE");
   }
   else
   {
      lcdmessage="STATUS: DISABLE";
       DEBUG_CM_PRINTLN("STATUS:DISABLE");
   }

 }
 else
 {
     lcdmessage="STATUS: SPI FAULT";
     DEBUG_CM_PRINTLN("STATUS: SPI FAULT");
     
 }

 
 DEBUG_CM_PRINTLN("***********************");
}


void ClockMaster::showIP()
{
 
 IPAddress myip=getIP();
 
lcdmessage=lcdmessage+ "\n" + "IP:";
lcdmessage=lcdmessage+ "\n"; 
lcdmessage+= String(myip[0]) + ".";
lcdmessage+= String(myip[1]) + ".";
lcdmessage+= String(myip[2]) + ".";
lcdmessage+= String(myip[3]) ;
      
 IPAddress mygate=getGateway();

lcdmessage=lcdmessage+ "\n" + "GATEWAY:";
lcdmessage=lcdmessage+ "\n"; 
lcdmessage+= String(mygate[0]) + ".";
lcdmessage+= String(mygate[1]) + ".";
lcdmessage+= String(mygate[2]) + ".";
lcdmessage+= String(mygate[3]) ;

 
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
           lcdmessage="CHANNEL: 0"; 
           DEBUG_CM_PRINTLN("CHANNEL: 0");
           lcdmessage=lcdmessage + "\n" + channel0.getParameters(); 
           break;
        case 1:
           lcdmessage="CHANNEL: 1"; 
           DEBUG_CM_PRINTLN("CHANNEL: 1");
           lcdmessage=lcdmessage + "\n" + channel1.getParameters(); 
           break;
        case 2:
           lcdmessage="CHANNEL: 2"; 
           DEBUG_CM_PRINTLN("CHANNEL: 2");
           lcdmessage=lcdmessage + "\n" + channel2.getParameters(); 
           break;
        case 3:
           lcdmessage="CHANNEL: 3"; 
           DEBUG_CM_PRINTLN("CHANNEL: 3");
           lcdmessage=lcdmessage + "\n" + channel3.getParameters();
            
        break;
    }

DEBUG_CM_PRINTLN("***********************");

}

void ClockMaster::showCGS()
{
   lcdmessage="CGS CHANNELS";
   lcdmessage+="\n";
   
   lcdmessage+="FREQ0: ";
   lcdmessage+="xx.xx MHz";//PUT YOUR FUNCTION HERE FOR FREQ0
   lcdmessage+= "\n";
   lcdmessage+="SOURCE0: ";
   lcdmessage+="GPS"; //PUT YOUR FUNCTION HERE FOR SOURCE0
   
   lcdmessage+="\n";
   lcdmessage+="\n";
   
   lcdmessage+="FREQ1: ";
   lcdmessage+="xx.xx MHz";//PUT YOUR FUNCTION HERE FOR FREQ1
   lcdmessage+="\n";
   lcdmessage+="SOURCE1: ";
   lcdmessage+="INTER"; //PUT YOUR FUNCTION HERE FOR SOURCE1 
   
   DEBUG_CM_PRINTLN("*******************");
   DEBUG_CM_PRINTLN(lcdmessage);
   DEBUG_CM_PRINTLN("*******************");
   
}
