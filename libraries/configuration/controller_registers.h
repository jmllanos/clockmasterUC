
#ifndef _CONTROLLER_REGISTERS_H_INCLUDED
#define _CONTROLLER_REGISTERS_H_INCLUDED

// Registers address
#define RESET       0x00
#define ENABLE      0x01
#define IO          0x02
#define FREQ        0x03
#define MW_BUF_L    0x04
#define MW_BUF_H    0x05
#define MR_BUF_L    0x06
#define MR_BUF_H    0x07
#define MEM_A_0     0x08
#define MEM_A_1     0x09
#define MEM_A_2     0x0a
#define MEM_CONF    0x0b
#define SAMP_L      0x0c
#define SAMP_CNTR   0x0d
#define MON_CONF    0x0e
#define MON_CNT_H0  0x0f
#define MON_CNT_H1  0x10
#define MON_CNT_H2  0x11
#define MON_CNT_H3  0x12
#define FRT_SEL_1   0x13
#define FRT_SEL_2   0x14
#define ACK_KEY     0x15
#define MON_CNT_L0  0x16
#define MON_CNT_L1  0x17
#define MON_CNT_L2  0x18
#define MON_CNT_L3  0x19

// Registers default values
#define DEFAULT_ACK_KEY 0X6A

// Reset register
#define RST (1<<0)

//Enable register
#define MN_EN  (1<<4)
#define SA_EN  (1<<3)
#define US_ET  (1<<2)
#define SYN_EN (1<<1)
#define R_EN   (1<<0) // Radar enable

//IO register
#define EXT_SYNC (1<<2)
#define SW       (1<<1)
#define TX       (1<<0)

//MEM_CONF register
#define CLR_ADR (1<<5)
#define M_FR    (1<<4)
#define M_SEL1  (1<<3)
#define M_SEL0  (1<<2)
#define M_WR    (1<<1)
#define M_RD    (1<<0)

//MON_CONF register
#define PULSE_SEL_3 (1<<7)
#define PULSE_SEL_2 (1<<6)
#define PULSE_SEL_1 (1<<5)
#define PULSE_SEL_0 (1<<4)
#define MON_RD_EN   (1<<3)
#define OVF_H       (1<<2)
#define OVF_L       (1<<1)

#endif
