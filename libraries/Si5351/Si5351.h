/*
 * Si5351.h
 * Simple function to program the Si5351 clock generator
 */
#ifndef Si5351_h
#define Si5351_h

#include <Arduino.h>
#include <Wire.h>


class Si5351
{

  public:

    Si5351();
    uint8_t set_freq(uint8_t multiplier, uint8_t divider, uint8_t gps_disciplined);

  private:

    uint8_t write_address(uint8_t slave_address, uint8_t data_0, uint8_t data_1);

};

#endif
