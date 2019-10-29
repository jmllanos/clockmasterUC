#ifndef  _CHANNEL_H_
#define  _CHANNEL_H_

#include<Arduino.h>
#include<PulseGenerator.h>
#include<PPSDivider.h>

#include<TIVAConfiguration.h>
#include<ArduinoJson.h>
#include<string.h>

#include "Adafruit_GFX.h"
#include "Adafruit_ILI9341.h"

class Channel
{
    private:
        PPSDivider PPSdiv;
        PulseGenerator PulseGen;
        
        String mode="XX";
        int channelNumber;
 
        String ReplyMessage;

        bool SPIOKFlag;
    public:
        void setParameters(JsonObject& channel_data);
        void setNumber(int _channelNumber);

        String getReplyMessage();

        bool getSPIStatus();

        String getParameters();
};


#endif



