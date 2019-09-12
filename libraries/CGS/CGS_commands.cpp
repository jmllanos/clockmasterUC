#include<CGS_commands.h>

void LOAD_CGS_CONFIG(frequency& CGS_freq)
{
  CGS_freq.integer      = EEPROM.read(FREQ_INT_ADD);
  CGS_freq.fractional   = EEPROM.read(FREQ_FRAC_ADD);
  CGS_freq.frac_text[0] = EEPROM.read(FREQ_FRAC_TEXT_0_ADD);
  CGS_freq.frac_text[1] = EEPROM.read(FREQ_FRAC_TEXT_1_ADD);
  CGS_freq.frac_text[2] = EEPROM.read(FREQ_FRAC_TEXT_2_ADD);
  CGS_freq.ref_text[0]  = EEPROM.read(REF_TEXT_0_ADDR);
  CGS_freq.ref_text[1]  = EEPROM.read(REF_TEXT_1_ADDR);
  CGS_freq.ref_text[2]  = EEPROM.read(REF_TEXT_2_ADDR);
  CGS_freq.ref_text[3]  = EEPROM.read(REF_TEXT_3_ADDR);
  CGS_freq.ref_text[4]  = EEPROM.read(REF_TEXT_4_ADDR);
  CGS_freq.ref_text[5]  = EEPROM.read(REF_TEXT_5_ADDR);
}

void STORE_CGS_CONFIG(frequency& CGS_freq)
{
  EEPROM.write(FREQ_INT_ADD         , CGS_freq.integer);
  EEPROM.write(FREQ_FRAC_ADD        , CGS_freq.fractional);
  EEPROM.write(FREQ_FRAC_TEXT_0_ADD , CGS_freq.frac_text[0]);
  EEPROM.write(FREQ_FRAC_TEXT_1_ADD , CGS_freq.frac_text[1]);
  EEPROM.write(FREQ_FRAC_TEXT_2_ADD , CGS_freq.frac_text[2]);
  EEPROM.write(REF_TEXT_0_ADDR      , CGS_freq.ref_text[0]);
  EEPROM.write(REF_TEXT_1_ADDR      , CGS_freq.ref_text[1]);
  EEPROM.write(REF_TEXT_2_ADDR      , CGS_freq.ref_text[2]);
  EEPROM.write(REF_TEXT_3_ADDR      , CGS_freq.ref_text[3]);
  EEPROM.write(REF_TEXT_4_ADDR      , CGS_freq.ref_text[4]);
  EEPROM.write(REF_TEXT_5_ADDR      , CGS_freq.ref_text[5]);
}

void CGS_DEFAULT_CONFIG(frequency& CGS_freq, Si5351& Si5351)
{
  uint8_t aux_si = Si5351.set_freq(MULT, DIV, SOURCE);
  if (aux_si == 0 )
  {
    DEBUG_RC_PRINTLN("PROGRAMMING CLOCK GENERATOR CORRECT");
    CGS_freq.integer    = FREQ_INT_DEFAULT;
    CGS_freq.fractional = FREQ_DECIMAL_DEFAULT;
    strcpy(CGS_freq.frac_text, "00");
    strcpy(CGS_freq.ref_text, "GPS");
    LCD.position(1, 0);
    LCD.text("  CLK GENERATOR OK  ");
  }
  else
  {
    DEBUG_RC_PRINTLN("Unable to connect to Si5351");
    DEBUG_RC_PRINT("I2C errolcd_tivacr type: ");
    DEBUG_RC_PRINTLN(aux_si);
    DEBUG_RC_PRINTLN("PROGRAMMING CLOCK GENERATOR FAILED!!!");
    LCD.position(1, 0);
    LCD.text("CLK GENERATOR FAILED");
  }

 }
