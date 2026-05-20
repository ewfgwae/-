#ifndef __SI24R2_H__
#define __SI24R2_H__

#include <reg52.h>
#include <intrins.h>

/* ========== ???? ========== */
sbit SI24R2_CE  = P1^0;
sbit SI24R2_CSN = P1^1;
sbit SI24R2_IRQ = P3^2;

/* SPI??: SCLK=P1.5, MISO=P1.4, MOSI=P1.3 */
sbit MOSI = P1^3;
sbit MISO = P1^4;
sbit SCLK = P1^5;

#define SI24R2_CE_SET()     (SI24R2_CE = 1)
#define SI24R2_CE_CLR()     (SI24R2_CE = 0)
#define SI24R2_CSN_SET()    (SI24R2_CSN = 1)
#define SI24R2_CSN_CLR()    (SI24R2_CSN = 0)
#define SI24R2_IRQ_READ()   (SI24R2_IRQ)

/* ========== ????? ========== */
#define REG_CONFIG      0x00
#define REG_EN_AA       0x01
#define REG_EN_RXADDR   0x02
#define REG_SETUP_AW    0x03
#define REG_SETUP_RETR  0x04
#define REG_RF_CH       0x05
#define REG_RF_SETUP    0x06
#define REG_STATUS      0x07
#define REG_OBSERVE_TX  0x08
#define REG_CD          0x09
#define REG_RX_ADDR_P0  0x0A
#define REG_RX_ADDR_P1  0x0B
#define REG_RX_ADDR_P2  0x0C
#define REG_RX_ADDR_P3  0x0D
#define REG_RX_ADDR_P4  0x0E
#define REG_RX_ADDR_P5  0x0F
#define REG_TX_ADDR     0x10
#define REG_RX_PW_P0    0x11
#define REG_RX_PW_P1    0x12
#define REG_RX_PW_P2    0x13
#define REG_RX_PW_P3    0x14
#define REG_RX_PW_P4    0x15
#define REG_RX_PW_P5    0x16
#define REG_FIFO_STATUS 0x17
#define REG_DYNPD       0x1C
#define REG_FEATURE     0x1D

#define CMD_R_REGISTER      0x00
#define CMD_W_REGISTER      0x20
#define CMD_R_RX_PAYLOAD    0x61
#define CMD_W_TX_PAYLOAD    0xA0
#define CMD_FLUSH_TX        0xE1
#define CMD_FLUSH_RX        0xE2
#define CMD_REUSE_TX_PL     0xE3
#define CMD_NOP             0xFF

#define STATUS_RX_DR        0x40
#define STATUS_TX_DS        0x20
#define STATUS_MAX_RT       0x10

/* ========== ???? (??????????) ========== */
#define PAYLOAD_LEN         32
#define RF_CHANNEL          40
#define RETR_SETUP          0x1A    /* 500us, 10??? */
#define RF_SETUP_VAL        0x07    /* 0dBm, 1Mbps */

/* ???? (??????????,??code???) */
extern unsigned char RX_Addr[5];

void DelayMs(unsigned int ms);

void SI24R2_Init(void);
unsigned char SI24R2_Check(void);

void SI24R2_SetTXMode(void);
void SI24R2_SetRXMode(void);

unsigned char SI24R2_TxPacket(unsigned char *txBuf);
unsigned char SI24R2_RxPacket(unsigned char *rxBuf);

unsigned char SI24R2_ReadReg(unsigned char reg);
unsigned char SI24R2_WriteReg(unsigned char reg, unsigned char value);
void SI24R2_ReadBuf(unsigned char reg, unsigned char *pBuf, unsigned char len);
void SI24R2_WriteBuf(unsigned char reg, unsigned char *pBuf, unsigned char len);

void SI24R2_FlushTX(void);
void SI24R2_FlushRX(void);

unsigned char SI24R2_GetStatus(void);

#endif