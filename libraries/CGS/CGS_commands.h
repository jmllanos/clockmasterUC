#ifndef _CGS_COMANDS_H_INCLUDED
#define _CGS_COMANDS_H_INCLUDED

#include <Arduino.h>
#include <controller_configuration.h>
#include <controller_registers.h>
#include <EEPROM.h>
#include <Si5351.h>
#include <read_write_registers.h>
#include <lcd_tivac.h>

struct frequency
{
  uint8_t integer=0;
  uint8_t fractional=0;
  char    frac_text[3]="00";
  char    ref_text[6]="ERROR";
};

struct CGS
{
  uint32_t multiplier;
  uint32_t divider;
  uint32_t gps_disciplined;
  uint32_t ref;
};
// Load CGS parameters in the EEPROM
void LOAD_CGS_CONFIG(frequency& CGS_freq);
// STORE CGS parameters in the EEPROM
void STORE_CGS_CONFIG(frequency& CGS_freq);

void CGS_DEFAULT_CONFIG(frequency& CGS_freq, Si5351& Si5351);

void SHOW_FREQUENCY_LCD();

#endif
