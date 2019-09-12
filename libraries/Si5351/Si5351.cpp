/*
 * Si5351.cpp
 * Simple function to program the Si5351 clock generator
 */

#include <Arduino.h>
#include <Wire.h>
#include <Si5351.h>

// Constructors ////////////////////////////////////////////////////////////////
Si5351::Si5351(void)
{
}

// Private Methods //////////////////////////////////////////////////////////////
uint8_t Si5351::write_address(uint8_t slave_address, uint8_t data_0, uint8_t data_1)
{
  Wire.beginTransmission(slave_address);
  Wire.write(data_0);
  Wire.write(data_1);
  return Wire.endTransmission(true);
}

// Public Methods //////////////////////////////////////////////////////////////
uint8_t Si5351::set_freq(uint8_t multiplier, uint8_t divider, uint8_t gps_disciplined)
{
  uint16_t PLL = multiplier*128 - 512;
//  uint16_t MS = divider*128 - 512;
  
  uint8_t PLL_1 = PLL >> 8;
  uint8_t PLL_0 = PLL;
//  uint8_t MS_1 = MS >> 8;
//  uint8_t MS_0 = MS;
  uint8_t reg_15 = (B00000000 | ((gps_disciplined & 0x01) << 3));

  uint8_t reg_map[][2] = {
    // 600-900 Freq PLL, 6-254 even divider in feedbackloop
    //  Disable Outputs
    {3, 0xFF},
    //  Powedown all output drivers
    {16, 0x80},
    {17, 0x80},
    {18, 0x80},
    {19, 0x80},
    {20, 0x80},
    {21, 0x80},
    {22, 0x80},
    {23, 0x80},
    //  Set interrupt mask
    {2, B00000000}, //Interrupt Status Mask - check time of interruption?
    //  Write new configuration
    {3, B01111111}, //  Output Enable Control, CLK7
    {9, B11111111}, //  OEB Pin Enable Control Mask
    {15, reg_15}, //  PLL Input Source
    {16, B11101111}, //  CLK0 Control. bit 6 integer mode MS0
    {23, B01101111}, //  CLK7 Control. bit 6 integer mode FBB
    {34, 0x00}, //  Multisynth NB Parameters, P3[15:8]
    {35, 0x01}, //  Multisynth NB Parameters, P3[7:0] ... 1 => no zero division
    {36, 0x00}, //  Multisynth NB Parameters, P1[17:16]
    {37, PLL_1}, //  Multisynth NB Parameters, P1[15:8]
    {38, PLL_0}, //  Multisynth NB Parameters, P1[7:0]
    {39, 0x00}, //  Multisynth NB Parameters, P3[19:16]P2[19:16]
    {40, 0x00}, //  Multisynth NB Parameters, P2[15:8]
    {41, 0x00}, //  Multisynth NB Parameters, P2[7:0]
//    {42, 0x00}, //  Multisynth0 Parameters, P3[15:8]
//    {43, 0x01}, //  Multisynth0 Parameters, P3[7:0] ... 1 => no zero division
//    {44, 0x00}, //  Multisynth0 Parameters, misc + P1[17:16]
//    {45, MS_1}, //  Multisynth0 Parameters, P1[15:8]
//    {46, MS_0}, //  Multisynth0 Parameters, P1[7:0]
//    {47, 0x00}, //  Multisynth0 Parameters, P3[19:16]P2[19:16]
//    {48, 0x00}, //  Multisynth0 Parameters, P2[15:8]
//    {49, 0x00}, //  Multisynth0 Parameters, P2[7:0]
    {91, divider}, //  Multisynth7 Parameters
    {92, 0x00},//  Clock 6 and 7 Output Divider
    {162, 0x00},  //  VCXO Parameter
    {163, 0x00},  //  VCXO Parameter
    {164, 0x00},  //  VCXO Parameter
    {183, B11010010},//  Crystal Internal Load Capacitance
    //  Apply PLLA and PLLB soft reset
    {177, 0xA0},  
    };
  uint8_t array_size = sizeof(reg_map) / 2;
  uint8_t aux = 0;

  for (int i = 0; i < array_size; i++)
  {
    aux = write_address(0x60, reg_map[i][0], reg_map[i][1]);
    if (aux != 0) {return aux;}
  }
  return aux;
}
