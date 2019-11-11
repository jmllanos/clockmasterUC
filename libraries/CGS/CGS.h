#ifndef  _CGS_H_
#define  _CGS_H_

#include <Arduino.h>
#include <Si5351.h>
#include <ArduinoJson.h>
#include <string.h>
#include<TIVAConfiguration.h>

class CGS
{
private:
    Si5351 IC; //chip
    String string_reply;

public:

    void begin();
    void mask_irq(char* data);
    void read_irq_sticky(char* data);
    void get_status(char* data);
    void set_pll(char* data);
    void set_clk_frac(char* data);
    void clk_ena(char* data);
    
    String getReplyMessage();

    uint8_t CheckBus();
};

#endif