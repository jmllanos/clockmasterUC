//*****************************************************************************
// Si5351.cpp
// Library to program the Si5351 clock generator.
//
// Driver for Si5351. This library allows the user to configure the clock
// channels of the device in 3 steps: initialization, multiplier stage (PLL
// configuration), divider stage (multisynth divider). Although both stages can
// be fractionals, the library only accepts valid integer values to avoid
// jitter. Clock references have to be 25MHz or 27MHz (XTAL) or any frequency
// between 10MHz and 40MHz(CLKIN), and the output of the PLLs has to be in the
// range of 600MHz to 900MHz. Divider in the second stage has to be greater
// than 6.
//
// version 1.0   August 2019 by Victor Vasquez. First release.
//*****************************************************************************

#include <Arduino.h>
#include <Wire.h>
#include <Si5351.h>

Si5351::Si5351(void)
{
}

uint8_t Si5351::slave_addr = 0x60;

//*****************************************************************************
// Writes an address of the register map.
//
// \param reg_addr    address to write.
// \param data        what else could it be?
//
// \return error in i2c communication
//*****************************************************************************
uint8_t Si5351::write_register(uint8_t reg_addr, uint8_t data)
{
  Wire.beginTransmission(slave_addr);
  Wire.write(reg_addr);
  Wire.write(data);
  return Wire.endTransmission(true);
}

//*****************************************************************************
// Reads an address of the register map.
//
// \param reg_addr    address to read.
//
// \return address' data
//*****************************************************************************
uint8_t Si5351::read_register(uint8_t reg_addr)
{
  Wire.beginTransmission(slave_addr);
  Wire.write(reg_addr);
  Wire.endTransmission(true);

  Wire.requestFrom(slave_addr, 1);
  return Wire.read();
}

//*****************************************************************************
// Default initialization.
//
// Default settings are detailed in comments below.
//
// \return 0
//*****************************************************************************
uint8_t Si5351::begin()
{
  // disable Outputs
  write_register(SI5351_REG_3_OUTPUT_ENABLE_CONTROL, 0xFF);
  // powedown all output drivers and set default channel configuration
  write_register(SI5351_REG_16_CLK0_CONTROL, 0xAF);//PLLB source. MS0 fractional. source 0.
  write_register(SI5351_REG_17_CLK1_CONTROL, 0xAF);//PLLB source. MS1 fractional. source 1.
  write_register(SI5351_REG_18_CLK2_CONTROL, 0xAF);//PLLB source. MS2 fractional. source 2.
  write_register(SI5351_REG_19_CLK3_CONTROL, 0xAF);//PLLB source. MS3 fractional. source 3.
  write_register(SI5351_REG_20_CLK4_CONTROL, 0xAF);//PLLB source. MS4 fractional. source 4.
  write_register(SI5351_REG_21_CLK5_CONTROL, 0xAF);//PLLB source. MS5 fractional. source 5.
  write_register(SI5351_REG_22_CLK6_CONTROL, 0xAF);//PLLB source. MSNA fractional. source 6.
  write_register(SI5351_REG_23_CLK7_CONTROL, 0xAF);//PLLB source. MSNB fractional. source 7.
  // IQR mask
  write_register(SI5351_REG_2_INTERRUPT_STATUS_MASK, 0x00);//no masks
  // OEB mask
  write_register(SI5351_REG_9_OEB_PIN_ENABLE_CONTROL, 0xFF);//OEB useless
  // input and output default configuration
  write_register(SI5351_REG_15_PLL_INPUT_SOURCE, 0x00);//XTAL as source for PLLs
  write_register(SI5351_REG_24_CLK3_0_DISABLE_STATE, 0x00);//outputs low when disable
  write_register(SI5351_REG_25_CLK7_4_DISABLE_STATE, 0x00);//outputs low when disable
  // multisynth NA: 24 + 0/1
  write_register(SI5351_REG_26_MSNA_PARAMETERS_1, 0x00);
  write_register(SI5351_REG_27_MSNA_PARAMETERS_2, 0x01);
  write_register(SI5351_REG_28_MSNA_PARAMETERS_3, 0x00);
  write_register(SI5351_REG_29_MSNA_PARAMETERS_4, 0x0A);
  write_register(SI5351_REG_30_MSNA_PARAMETERS_5, 0x00);
  write_register(SI5351_REG_31_MSNA_PARAMETERS_6, 0x00);
  write_register(SI5351_REG_32_MSNA_PARAMETERS_7, 0x00);
  write_register(SI5351_REG_33_MSNA_PARAMETERS_8, 0x00);
  // multisynth NB: 24 + 0/1
  write_register(SI5351_REG_34_MSNB_PARAMETERS_1, 0x00);
  write_register(SI5351_REG_35_MSNB_PARAMETERS_2, 0x01);
  write_register(SI5351_REG_36_MSNB_PARAMETERS_3, 0x00);
  write_register(SI5351_REG_37_MSNB_PARAMETERS_4, 0x0A);
  write_register(SI5351_REG_38_MSNB_PARAMETERS_5, 0x00);
  write_register(SI5351_REG_39_MSNB_PARAMETERS_6, 0x00);
  write_register(SI5351_REG_40_MSNB_PARAMETERS_7, 0x00);
  write_register(SI5351_REG_41_MSNB_PARAMETERS_8, 0x00);
// multisynth0: 6 + 0/1
  write_register(SI5351_REG_42_MS0_PARAMETERS_1, 0x00);
  write_register(SI5351_REG_43_MS0_PARAMETERS_2, 0x01);
  write_register(SI5351_REG_44_MS0_PARAMETERS_3, 0x00);
  write_register(SI5351_REG_45_MS0_PARAMETERS_4, 0x01);
  write_register(SI5351_REG_46_MS0_PARAMETERS_5, 0x00);
  write_register(SI5351_REG_47_MS0_PARAMETERS_6, 0x00);
  write_register(SI5351_REG_48_MS0_PARAMETERS_7, 0x00);
  write_register(SI5351_REG_49_MS0_PARAMETERS_8, 0x00);
  // multisynth1: 6 + 0/1
  write_register(SI5351_REG_50_MS1_PARAMETERS_1, 0x00);
  write_register(SI5351_REG_51_MS1_PARAMETERS_2, 0x01);
  write_register(SI5351_REG_52_MS1_PARAMETERS_3, 0x00);
  write_register(SI5351_REG_53_MS1_PARAMETERS_4, 0x01);
  write_register(SI5351_REG_54_MS1_PARAMETERS_5, 0x00);
  write_register(SI5351_REG_55_MS1_PARAMETERS_6, 0x00);
  write_register(SI5351_REG_56_MS1_PARAMETERS_7, 0x00);
  write_register(SI5351_REG_57_MS1_PARAMETERS_8, 0x00);
  // multisynth2: 6 + 0/1
  write_register(SI5351_REG_58_MS2_PARAMETERS_1, 0x00);
  write_register(SI5351_REG_59_MS2_PARAMETERS_2, 0x01);
  write_register(SI5351_REG_60_MS2_PARAMETERS_3, 0x00);
  write_register(SI5351_REG_61_MS2_PARAMETERS_4, 0x01);
  write_register(SI5351_REG_62_MS2_PARAMETERS_5, 0x00);
  write_register(SI5351_REG_63_MS2_PARAMETERS_6, 0x00);
  write_register(SI5351_REG_64_MS2_PARAMETERS_7, 0x00);
  write_register(SI5351_REG_65_MS2_PARAMETERS_8, 0x00);
  // multisynth3: 6 + 0/1
  write_register(SI5351_REG_66_MS3_PARAMETERS_1, 0x00);
  write_register(SI5351_REG_67_MS3_PARAMETERS_2, 0x01);
  write_register(SI5351_REG_68_MS3_PARAMETERS_3, 0x00);
  write_register(SI5351_REG_69_MS3_PARAMETERS_4, 0x01);
  write_register(SI5351_REG_70_MS3_PARAMETERS_5, 0x00);
  write_register(SI5351_REG_71_MS3_PARAMETERS_6, 0x00);
  write_register(SI5351_REG_72_MS3_PARAMETERS_7, 0x00);
  write_register(SI5351_REG_73_MS3_PARAMETERS_8, 0x00);
  // multisynth4: 6 + 0/1
  write_register(SI5351_REG_74_MS4_PARAMETERS_1, 0x00);
  write_register(SI5351_REG_75_MS4_PARAMETERS_2, 0x01);
  write_register(SI5351_REG_76_MS4_PARAMETERS_3, 0x00);
  write_register(SI5351_REG_77_MS4_PARAMETERS_4, 0x01);
  write_register(SI5351_REG_78_MS4_PARAMETERS_5, 0x00);
  write_register(SI5351_REG_79_MS4_PARAMETERS_6, 0x00);
  write_register(SI5351_REG_80_MS4_PARAMETERS_7, 0x00);
  write_register(SI5351_REG_81_MS4_PARAMETERS_8, 0x00);
  // multisynth5: 6 + 0/1
  write_register(SI5351_REG_82_MS5_PARAMETERS_1, 0x00);
  write_register(SI5351_REG_83_MS5_PARAMETERS_2, 0x01);
  write_register(SI5351_REG_84_MS5_PARAMETERS_3, 0x00);
  write_register(SI5351_REG_85_MS5_PARAMETERS_4, 0x01);
  write_register(SI5351_REG_86_MS5_PARAMETERS_5, 0x00);
  write_register(SI5351_REG_87_MS5_PARAMETERS_6, 0x00);
  write_register(SI5351_REG_88_MS5_PARAMETERS_7, 0x00);
  write_register(SI5351_REG_89_MS5_PARAMETERS_8, 0x00);
  // multisynth6: 6
  write_register(SI5351_REG_90_MS6_PARAMETERS, 0x06);
  // multisynth7: 6
  write_register(SI5351_REG_91_MS7_PARAMETERS, 0x06);
  // post divider 7 & 6: 1
  write_register(SI5351_REG_92_CLOCK_6_7_OUT_DIV, 0x00);
  // offsets to zero
  write_register(SI5351_REG_165_CLK0_INITIAL_OFFSET, 0x00);
  write_register(SI5351_REG_166_CLK1_INITIAL_OFFSET, 0x00);
  write_register(SI5351_REG_167_CLK2_INITIAL_OFFSET, 0x00);
  write_register(SI5351_REG_168_CLK3_INITIAL_OFFSET, 0x00);
  write_register(SI5351_REG_169_CLK4_INITIAL_OFFSET, 0x00);
  write_register(SI5351_REG_170_CLK5_INITIAL_OFFSET, 0x00);
  // XTAL internal load capacitance 10pF
  write_register(SI5351_REG_183_XTAL_INTERNAL_CAP, 0xD2);
  // fanout disable
  write_register(SI5351_REG_187_FANOUT_ENABLE, 0x00);
  // PLL reset
  write_register(SI5351_REG_177_PLL_RESET, 0xA0);
return 0;
}

//*****************************************************************************
// Sets the mask of of one of the following fields:
// SYS_INIT: System initialization
// LOL_B: PLLB loss of lock
// LOL_A: PLLA loss of lock
// LOS: CLKIN loss of signal
//
// \param field       field of register to mask.
// \param mask        don't mask 'field' (false) or mask 'field' (true).
//
// 'field' has to be between 4 to 7.
//
// \return 1: 'field' invalid
// \return 0: ok
//*****************************************************************************
uint8_t Si5351::mask_irq(uint8_t field, bool mask)
{
  if ( (field < 4) || (field > 7) ) {
    return 1;
  }
  uint8_t aux = read_register(SI5351_REG_2_INTERRUPT_STATUS_MASK);
  if (mask) {
    write_register(SI5351_REG_2_INTERRUPT_STATUS_MASK, aux | (0x01<<field) );
  }
  else {
    write_register(SI5351_REG_2_INTERRUPT_STATUS_MASK, aux & ~(0x01<<field) );
  }
return 0;
}

//*****************************************************************************
// Reads and clears sticky bit of one of the following fields:
// SYS_INIT: System initialization
// LOL_B: PLLB loss of lock
// LOL_A: PLLA loss of lock
// LOS: CLKIN loss of signal
//
// \param field       field of register to read.
//
// 'field' has to be between 4 to 7.
//
// \return 2: 'field' invalid
// \return 1: an interrupt occurred since it was last clear
// \return 0: no interrupt has occurred since it was last clear
//*****************************************************************************
uint8_t Si5351::read_irq_sticky(uint8_t field)
{
  if ( (field < 4) || (field > 7) ) {
    return 2;
  }
  uint8_t aux = read_register(SI5351_REG_1_INTERRUPT_STATUS_STICKY);
  write_register(SI5351_REG_1_INTERRUPT_STATUS_STICKY, aux & ~(0x01<<field) );
return (aux>>field) & 0x01;
}

//*****************************************************************************
// Gets current status of one of the following fields:
// SYS_INIT: System initialization
// LOL_B: PLLB loss of lock
// LOL_A: PLLA loss of lock
// LOS: CLKIN loss of signal
//
// \param field       field of register to read.
//
// 'field' has to be between 4 to 7.
//
// \return 2: 'field' invalid
// \return 1: anormal operation
// \return 0: ok
//*****************************************************************************
uint8_t Si5351::get_status(uint8_t field)
{
  if ( (field < 4) || (field > 7) ) {
    return 2;
  }
  uint8_t aux = read_register(SI5351_REG_0_DEVICE_STATUS);
return (aux>>field) & 0x01;
}

//*****************************************************************************
// Modifies the reference clock and feedback divider of a PLL.
//
// \param pll         pll selector. PLL_A (true) or PLL_B (false).
// \param ref         reference clock for PLLB. CLKIN (true) or XTAL (false).
// \param multiplier  feedback divider of PLLB.
//
// Changes the reference clock for the PLL.
// Changes the feedback divider of the PLL: 'multiplier' + 0/1.
// Resets the PLL.
//
// 'multiplier' has to be between 15 to 90 inclusive.
//
// \return 0
//*****************************************************************************
uint8_t Si5351::set_pll(bool pll, bool ref, uint8_t multiplier)
{
  uint16_t m = multiplier*128 - 512;
  uint8_t m_1 = m >> 8;
  uint8_t m_0 = m;
  uint8_t source = 0x00;
  uint8_t pos = 0;
  if (pll) {//PLL_A
    pos = 2;
  }
  else {
    pos = 3;
  }

  // source for PLLs
  uint8_t aux_src = read_register(SI5351_REG_15_PLL_INPUT_SOURCE);
  if (ref) {
    write_register(SI5351_REG_15_PLL_INPUT_SOURCE, aux_src | (0x01<<pos) );
  }
  else {
    write_register(SI5351_REG_15_PLL_INPUT_SOURCE, aux_src & ~(0x01<<pos) );
  }
  // multisynth Nx: multiplier + 0/1
  write_register(SI5351_REG_26_MSNA_PARAMETERS_1 + 8*(pos-2), 0x00);
  write_register(SI5351_REG_27_MSNA_PARAMETERS_2 + 8*(pos-2), 0x01);
  write_register(SI5351_REG_28_MSNA_PARAMETERS_3 + 8*(pos-2), 0x00);
  write_register(SI5351_REG_29_MSNA_PARAMETERS_4 + 8*(pos-2), m_1);
  write_register(SI5351_REG_30_MSNA_PARAMETERS_5 + 8*(pos-2), m_0);
  write_register(SI5351_REG_31_MSNA_PARAMETERS_6 + 8*(pos-2), 0x00);
  write_register(SI5351_REG_32_MSNA_PARAMETERS_7 + 8*(pos-2), 0x00);
  write_register(SI5351_REG_33_MSNA_PARAMETERS_8 + 8*(pos-2), 0x00);
  // PLL reset
  uint8_t aux_rst = read_register(SI5351_REG_177_PLL_RESET);
  write_register(SI5351_REG_177_PLL_RESET, aux_rst | (0x01<<((pos*2)+1)) );
return 0;
}

//*****************************************************************************
// Enables or disables a clock channel.
//
// \param clk         channel selector.
// \param condition   enable (true) or disable (false).
//
// First reads registers, so it can mask the new commands.
// If command is enable, it turns on channel 'clk' and then enables it. If
// command is disable, it disables channel 'clk' and then turns it off.
//
// \return 0
//*****************************************************************************
uint8_t Si5351::clk_ena(uint8_t clk, bool condition)
{
  uint8_t aux_pow = read_register(SI5351_REG_16_CLK0_CONTROL + clk);
  uint8_t aux_ena = read_register(SI5351_REG_3_OUTPUT_ENABLE_CONTROL);
  if (condition) {
    write_register(SI5351_REG_16_CLK0_CONTROL + clk, aux_pow & 0x7F );
    write_register(SI5351_REG_3_OUTPUT_ENABLE_CONTROL, aux_ena & ~(1<<clk) );
  }
  else{
    write_register(SI5351_REG_3_OUTPUT_ENABLE_CONTROL, aux_ena | (1<<clk) );
    write_register(SI5351_REG_16_CLK0_CONTROL + clk, aux_pow | 0x80 );
  }
return 0;
}

//*****************************************************************************
// Modifies the divide ratio and the source of a fractional multisynth divider.
//
// \param clk         channel selector. 0 to 5.
// \param pll         source for multisynth. PLL_A (true) or PLL_B (false).
// \param divider     divider ratio of multisynth divider.
//
// Reads 'clk' control register and modifies the source bit (bit 5).
// Changes the multisynth divider ratio corresponding to channel 'clk'. Divider
// ratio is 'divider + 0/1'.
//
// 'divider' has to be greater or equal to 6.
//
// \return 2: 'divider' invalid
// \return 1: 'clk' invalid
// \return 0: correct
//*****************************************************************************
uint8_t Si5351::set_clk_frac(uint8_t clk, bool pll, uint8_t divider)
{
  if (clk > 5) {
    return 1;
  }

  if (divider < 6) {
    return 2;
  }

  uint16_t d = divider*128 - 512;
  uint8_t d_1 = d >> 8;
  uint8_t d_0 = d;
  uint8_t aux = read_register(SI5351_REG_16_CLK0_CONTROL + clk);

  if (pll) {//PLL_A
    write_register(SI5351_REG_16_CLK0_CONTROL + clk, aux & ~(0x01<<5));
  }
  else {
    write_register(SI5351_REG_16_CLK0_CONTROL + clk, aux | (0x01<<5));
  }

  write_register(SI5351_REG_42_MS0_PARAMETERS_1 + (8*clk), 0x00);
  write_register(SI5351_REG_43_MS0_PARAMETERS_2 + (8*clk), 0x01);
  write_register(SI5351_REG_44_MS0_PARAMETERS_3 + (8*clk), 0x00);
  write_register(SI5351_REG_45_MS0_PARAMETERS_4 + (8*clk), d_1);
  write_register(SI5351_REG_46_MS0_PARAMETERS_5 + (8*clk), d_0);
  write_register(SI5351_REG_47_MS0_PARAMETERS_6 + (8*clk), 0x00);
  write_register(SI5351_REG_48_MS0_PARAMETERS_7 + (8*clk), 0x00);
  write_register(SI5351_REG_49_MS0_PARAMETERS_8 + (8*clk), 0x00);
return 0;
}

//*****************************************************************************
// Modifies the divide ratio and the source of an integer multisynth divider.
//
// \param clk         channel selector. 6 or 7.
// \param pll         source for multisynth. PLL_A (true) or PLL_B (false).
// \param divider     divider ratio of multisynth divider.
//
// Reads 'clk' control register and modifies the source bit (bit 5).
// Changes the multisynth divider ratio corresponding to channel 'clk'.
//
// 'divider' can only be an even integer greater or equal to 6.
//
// \return 2: 'divider' invalid
// \return 1: 'clk' invalid
// \return 0: correct
//*****************************************************************************
uint8_t Si5351::set_clk_int(uint8_t clk, bool pll, uint8_t divider)
{
  if ( (clk < 6) || (clk > 7) ) {
    return 1;
  }

  if (divider < 6 || ((divider % 2) != 0) ) {
    return 2;
  }

  uint8_t aux = read_register(SI5351_REG_16_CLK0_CONTROL + clk);
  if (pll) {//PLL_A
    write_register(SI5351_REG_16_CLK0_CONTROL + clk, aux & ~(0x01<<5));
  }
  else {
    write_register(SI5351_REG_16_CLK0_CONTROL + clk, aux | (0x01<<5));
  }

  write_register(SI5351_REG_90_MS6_PARAMETERS + (clk-6), divider);
return 0;
}

//*****************************************************************************
// !!!!!!!!!Legacy function!!!!!!!!!
// - PLLB source for Multisynth 7.
// - CLK7 only output.
//
// \param multiplier  feedback divider of PLLB.
// \param divider     divider ratio of multisynth divider.
// \param gps_disc    reference clock for PLLB. CLKIN (true) or XTAL (false).
//
// \return error in i2c communication
//*****************************************************************************
uint8_t Si5351::set_freq(uint8_t multiplier, uint8_t divider, uint8_t gps_disciplined)
{
  uint16_t PLL = multiplier*128 - 512;
  uint8_t PLL_1 = PLL >> 8;
  uint8_t PLL_0 = PLL;
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
    {2, B00000000}, //Interrupt Status Mask
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
    aux = write_register(reg_map[i][0], reg_map[i][1]);
    if (aux != 0) {return aux;}
  }
return aux;
}
