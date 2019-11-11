//*****************************************************************************
// Si5351.h
// Library to program the Si5351 clock generator.
//*****************************************************************************

#ifndef Si5351_h
#define Si5351_h

#include <Arduino.h>
#include <Wire.h>

#define SI5351_REG_0_DEVICE_STATUS               0
#define SI5351_REG_1_INTERRUPT_STATUS_STICKY     1
#define SI5351_REG_2_INTERRUPT_STATUS_MASK       2
#define SI5351_REG_3_OUTPUT_ENABLE_CONTROL       3
#define SI5351_REG_9_OEB_PIN_ENABLE_CONTROL      9
#define SI5351_REG_15_PLL_INPUT_SOURCE           15
#define SI5351_REG_16_CLK0_CONTROL               16
#define SI5351_REG_17_CLK1_CONTROL               17
#define SI5351_REG_18_CLK2_CONTROL               18
#define SI5351_REG_19_CLK3_CONTROL               19
#define SI5351_REG_20_CLK4_CONTROL               20
#define SI5351_REG_21_CLK5_CONTROL               21
#define SI5351_REG_22_CLK6_CONTROL               22
#define SI5351_REG_23_CLK7_CONTROL               23
#define SI5351_REG_24_CLK3_0_DISABLE_STATE       24
#define SI5351_REG_25_CLK7_4_DISABLE_STATE       25
#define SI5351_REG_26_MSNA_PARAMETERS_1          26
#define SI5351_REG_27_MSNA_PARAMETERS_2          27
#define SI5351_REG_28_MSNA_PARAMETERS_3          28
#define SI5351_REG_29_MSNA_PARAMETERS_4          29
#define SI5351_REG_30_MSNA_PARAMETERS_5          30
#define SI5351_REG_31_MSNA_PARAMETERS_6          31
#define SI5351_REG_32_MSNA_PARAMETERS_7          32
#define SI5351_REG_33_MSNA_PARAMETERS_8          33
#define SI5351_REG_34_MSNB_PARAMETERS_1          34
#define SI5351_REG_35_MSNB_PARAMETERS_2          35
#define SI5351_REG_36_MSNB_PARAMETERS_3          36
#define SI5351_REG_37_MSNB_PARAMETERS_4          37
#define SI5351_REG_38_MSNB_PARAMETERS_5          38
#define SI5351_REG_39_MSNB_PARAMETERS_6          39
#define SI5351_REG_40_MSNB_PARAMETERS_7          40
#define SI5351_REG_41_MSNB_PARAMETERS_8          41
#define SI5351_REG_42_MS0_PARAMETERS_1           42
#define SI5351_REG_43_MS0_PARAMETERS_2           43
#define SI5351_REG_44_MS0_PARAMETERS_3           44
#define SI5351_REG_45_MS0_PARAMETERS_4           45
#define SI5351_REG_46_MS0_PARAMETERS_5           46
#define SI5351_REG_47_MS0_PARAMETERS_6           47
#define SI5351_REG_48_MS0_PARAMETERS_7           48
#define SI5351_REG_49_MS0_PARAMETERS_8           49
#define SI5351_REG_50_MS1_PARAMETERS_1           50
#define SI5351_REG_51_MS1_PARAMETERS_2           51
#define SI5351_REG_52_MS1_PARAMETERS_3           52
#define SI5351_REG_53_MS1_PARAMETERS_4           53
#define SI5351_REG_54_MS1_PARAMETERS_5           54
#define SI5351_REG_55_MS1_PARAMETERS_6           55
#define SI5351_REG_56_MS1_PARAMETERS_7           56
#define SI5351_REG_57_MS1_PARAMETERS_8           57
#define SI5351_REG_58_MS2_PARAMETERS_1           58
#define SI5351_REG_59_MS2_PARAMETERS_2           59
#define SI5351_REG_60_MS2_PARAMETERS_3           60
#define SI5351_REG_61_MS2_PARAMETERS_4           61
#define SI5351_REG_62_MS2_PARAMETERS_5           62
#define SI5351_REG_63_MS2_PARAMETERS_6           63
#define SI5351_REG_64_MS2_PARAMETERS_7           64
#define SI5351_REG_65_MS2_PARAMETERS_8           65
#define SI5351_REG_66_MS3_PARAMETERS_1           66
#define SI5351_REG_67_MS3_PARAMETERS_2           67
#define SI5351_REG_68_MS3_PARAMETERS_3           68
#define SI5351_REG_69_MS3_PARAMETERS_4           69
#define SI5351_REG_70_MS3_PARAMETERS_5           70
#define SI5351_REG_71_MS3_PARAMETERS_6           71
#define SI5351_REG_72_MS3_PARAMETERS_7           72
#define SI5351_REG_73_MS3_PARAMETERS_8           73
#define SI5351_REG_74_MS4_PARAMETERS_1           74
#define SI5351_REG_75_MS4_PARAMETERS_2           75
#define SI5351_REG_76_MS4_PARAMETERS_3           76
#define SI5351_REG_77_MS4_PARAMETERS_4           77
#define SI5351_REG_78_MS4_PARAMETERS_5           78
#define SI5351_REG_79_MS4_PARAMETERS_6           79
#define SI5351_REG_80_MS4_PARAMETERS_7           80
#define SI5351_REG_81_MS4_PARAMETERS_8           81
#define SI5351_REG_82_MS5_PARAMETERS_1           82
#define SI5351_REG_83_MS5_PARAMETERS_2           83
#define SI5351_REG_84_MS5_PARAMETERS_3           84
#define SI5351_REG_85_MS5_PARAMETERS_4           85
#define SI5351_REG_86_MS5_PARAMETERS_5           86
#define SI5351_REG_87_MS5_PARAMETERS_6           87
#define SI5351_REG_88_MS5_PARAMETERS_7           88
#define SI5351_REG_89_MS5_PARAMETERS_8           89
#define SI5351_REG_90_MS6_PARAMETERS             90
#define SI5351_REG_91_MS7_PARAMETERS             91
#define SI5351_REG_92_CLOCK_6_7_OUT_DIV          92
#define SI5351_REG_165_CLK0_INITIAL_OFFSET       165
#define SI5351_REG_166_CLK1_INITIAL_OFFSET       166
#define SI5351_REG_167_CLK2_INITIAL_OFFSET       167
#define SI5351_REG_168_CLK3_INITIAL_OFFSET       168
#define SI5351_REG_169_CLK4_INITIAL_OFFSET       169
#define SI5351_REG_170_CLK5_INITIAL_OFFSET       170
#define SI5351_REG_177_PLL_RESET                 177
#define SI5351_REG_183_XTAL_INTERNAL_CAP         183
#define SI5351_REG_187_FANOUT_ENABLE             187

#define SYS_INIT  7
#define LOL_B     6
#define LOL_A     5
#define LOS       4

#define PLL_A     true
#define PLL_B     false

#define CLK_0     0
#define CLK_1     1
#define CLK_2     2
#define CLK_3     3
#define CLK_4     4
#define CLK_5     5
#define CLK_6     6
#define CLK_7     7

#define MASK      true
#define NO_MASK   false

#define ENABLE    true
#define DISABLE   false

#define CLKIN     true
#define XTAL      false

class Si5351
{

  public:

    Si5351();
    static uint8_t slave_addr;

    uint8_t read_register(uint8_t reg_addr);
    uint8_t write_register(uint8_t reg_addr, uint8_t data);

    uint8_t begin();
    uint8_t mask_irq(uint8_t field, bool mask);
    uint8_t read_irq_sticky(uint8_t field);
    uint8_t get_status(uint8_t field);
    uint8_t set_pll(bool pll, bool ref, uint8_t multiplier);
    uint8_t set_clk_frac(uint8_t clk, bool pll, uint8_t divider);
    uint8_t set_clk_int(uint8_t clk, bool pll, uint8_t divider);
    uint8_t clk_ena(uint8_t clk, bool condition);
    uint8_t set_freq(uint8_t multiplier, uint8_t divider, uint8_t gps_disciplined);

};

#endif
