#ifndef __SI24R1_89_H__
#define __SI24R1_89_H__

#include <reg52.h>

/* ========== 晶体频率 (根据实际修改) ========== */
#define MAIN_Fosc		11059200L

/* ========== 数据类型 ========== */
typedef unsigned char u8;
typedef unsigned int  u16;
typedef unsigned long u32;

/* ========== SI24R1 引脚定义 ========== */
sbit MOSI = P1^1;
sbit MISO = P1^6;
sbit SCK  = P1^7;
sbit CSN  = P1^3;
sbit CE   = P1^2;
sbit IRQ  = P1^6;

/* ========== 数据包宽度 ========== */
#define TX_ADR_WIDTH   5
#define TX_PLOAD_WIDTH 32

/* ========== SPI 命令 ========== */
#define READ_REG        0x00
#define WRITE_REG       0x20
#define RD_RX_PLOAD     0x61
#define WR_TX_PLOAD     0xA0
#define FLUSH_TX        0xE1
#define FLUSH_RX        0xE2
#define REUSE_TX_PL     0xE3
#define NOP             0xFF

/* ========== 寄存器地址 ========== */
#define CONFIG          0x00
#define EN_AA           0x01
#define EN_RXADDR       0x02
#define SETUP_AW        0x03
#define SETUP_RETR      0x04
#define RF_CH           0x05
#define RF_SETUP        0x06
#define STATUS          0x07
#define OBSERVE_TX      0x08
#define RSSI            0x09
#define RX_ADDR_P0      0x0A
#define RX_ADDR_P1      0x0B
#define RX_ADDR_P2      0x0C
#define RX_ADDR_P3      0x0D
#define RX_ADDR_P4      0x0E
#define RX_ADDR_P5      0x0F
#define TX_ADDR         0x10
#define RX_PW_P0        0x11
#define RX_PW_P1        0x12
#define RX_PW_P2        0x13
#define RX_PW_P3        0x14
#define RX_PW_P4        0x15
#define RX_PW_P5        0x16
#define FIFO_STATUS     0x17

/* ========== STATUS 标志位 ========== */
#define RX_DR           0x40
#define TX_DS           0x20
#define MAX_RT          0x10

/* ========== 函数声明 ========== */
void SI24R1_Init(void);
u8   SI24R1_Write_Reg(u8 reg, u8 value);
u8   SI24R1_Write_Buf(u8 reg, const u8 *pBuf, u8 bytes);
u8   SI24R1_Read_Reg(u8 reg);
u8   SI24R1_Read_Buf(u8 reg, u8 *pBuf, u8 bytes);
void SI24R1_RX_Mode(void);
void SI24R1_TX_Mode(void);
u8   SI24R1_RxPacket(u8 *rxbuf);
u8   SI24R1_TxPacket(u8 *txbuf);
u8   SI24R1_Check(void);
void delay_ms(u16 ms);

#endif
