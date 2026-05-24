#include "si24r1_89.h"

static u8 code TX_ADDRESS[TX_ADR_WIDTH] = {0x0A, 0x01, 0x07, 0x0E, 0x01};

/********************************************************
  毫秒延时 (12T 89C52RC, 11.0592MHz)
*********************************************************/
void delay_ms(u16 ms)
{
    u16 i, j;
    for(i = 0; i < ms; i++)
        for(j = 0; j < 114; j++);
}

/********************************************************
  SPI读写一字节
*********************************************************/
static u8 SPI_RW(u8 byte)
{
    u8 bit_ctr;
    for(bit_ctr = 0; bit_ctr < 8; bit_ctr++)
    {
        MOSI = (byte & 0x80) ? 1 : 0;
        byte <<= 1;
        SCK = 1;
        byte |= MISO;
        SCK = 0;
    }
    return byte;
}

/********************************************************
  SI24R1引脚初始化
*********************************************************/
void SI24R1_Init(void)
{
    SCK  = 0;
    CSN  = 1;
    CE   = 0;
    IRQ  = 1;
}

/********************************************************
  写一字节到寄存器
*********************************************************/
u8 SI24R1_Write_Reg(u8 reg, u8 value)
{
    u8 status;
    CSN = 0;
    status = SPI_RW(reg);
    SPI_RW(value);
    CSN = 1;
    return status;
}

/********************************************************
  写多字节到寄存器
*********************************************************/
u8 SI24R1_Write_Buf(u8 reg, const u8 *pBuf, u8 bytes)
{
    u8 status, byte_ctr;
    CSN = 0;
    status = SPI_RW(reg);
    for(byte_ctr = 0; byte_ctr < bytes; byte_ctr++)
        SPI_RW(*pBuf++);
    CSN = 1;
    return status;
}

/********************************************************
  读一字节寄存器
*********************************************************/
u8 SI24R1_Read_Reg(u8 reg)
{
    u8 value;
    CSN = 0;
    SPI_RW(reg);
    value = SPI_RW(0);
    CSN = 1;
    return value;
}

/********************************************************
  读多字节寄存器
*********************************************************/
u8 SI24R1_Read_Buf(u8 reg, u8 *pBuf, u8 bytes)
{
    u8 status, byte_ctr;
    CSN = 0;
    status = SPI_RW(reg);
    for(byte_ctr = 0; byte_ctr < bytes; byte_ctr++)
        pBuf[byte_ctr] = SPI_RW(0);
    CSN = 1;
    return status;
}

/********************************************************
  接收模式初始化
*********************************************************/
void SI24R1_RX_Mode(void)
{
    CE = 0;
    SI24R1_Write_Buf(WRITE_REG + RX_ADDR_P0, TX_ADDRESS, TX_ADR_WIDTH);
    SI24R1_Write_Reg(WRITE_REG + EN_AA, 0x01);
    SI24R1_Write_Reg(WRITE_REG + EN_RXADDR, 0x01);
    SI24R1_Write_Reg(WRITE_REG + RF_CH, 40);
    SI24R1_Write_Reg(WRITE_REG + RX_PW_P0, TX_PLOAD_WIDTH);
    SI24R1_Write_Reg(WRITE_REG + RF_SETUP, 0x0f);
    SI24R1_Write_Reg(WRITE_REG + CONFIG, 0x0f);
    SI24R1_Write_Reg(WRITE_REG + STATUS, 0xff);
    CE = 1;
}

/********************************************************
  发送模式初始化
*********************************************************/
void SI24R1_TX_Mode(void)
{
    CE = 0;
    SI24R1_Write_Buf(WRITE_REG + TX_ADDR, TX_ADDRESS, TX_ADR_WIDTH);
    SI24R1_Write_Buf(WRITE_REG + RX_ADDR_P0, TX_ADDRESS, TX_ADR_WIDTH);
    SI24R1_Write_Reg(WRITE_REG + EN_AA, 0x01);
    SI24R1_Write_Reg(WRITE_REG + EN_RXADDR, 0x01);
    SI24R1_Write_Reg(WRITE_REG + SETUP_RETR, 0x0a);
    SI24R1_Write_Reg(WRITE_REG + RF_CH, 40);
    SI24R1_Write_Reg(WRITE_REG + RF_SETUP, 0x0f);
    SI24R1_Write_Reg(WRITE_REG + CONFIG, 0x0e);
}

/********************************************************
  接收数据包
  返回: 0-收到数据, 1-未收到
*********************************************************/
u8 SI24R1_RxPacket(u8 *rxbuf)
{
    u8 state;
    state = SI24R1_Read_Reg(STATUS);
    SI24R1_Write_Reg(WRITE_REG + STATUS, state);

    if(state & RX_DR)
    {
        SI24R1_Read_Buf(RD_RX_PLOAD, rxbuf, TX_PLOAD_WIDTH);
        SI24R1_Write_Reg(FLUSH_RX, 0xff);
        return 0;
    }
    return 1;
}

/********************************************************
  发送数据包 (含超时, 防止卡死)
  返回: MAX_RT-达到最大重发, TX_DS-发送成功, 0xFF-超时/失败
*********************************************************/
u8 SI24R1_TxPacket(u8 *txbuf)
{
    u8 state;
    u16 timeout;

    CE = 0;
    SI24R1_Write_Buf(WR_TX_PLOAD, txbuf, TX_PLOAD_WIDTH);
    CE = 1;

    timeout = 10000;
    while(IRQ && --timeout);

    CE = 0;

    if(timeout == 0)
    {
        SI24R1_Write_Reg(FLUSH_TX, 0xff);
        SI24R1_Write_Reg(WRITE_REG + STATUS, 0x70);
        return 0xFF;
    }

    state = SI24R1_Read_Reg(STATUS);
    SI24R1_Write_Reg(WRITE_REG + STATUS, state);

    if(state & MAX_RT)
    {
        SI24R1_Write_Reg(FLUSH_TX, 0xff);
        return MAX_RT;
    }
    if(state & TX_DS)
    {
        return TX_DS;
    }
    return 0xFF;
}

/********************************************************
  检测SI24R1模块是否存在
  返回: 1-存在, 0-不存在
*********************************************************/
u8 SI24R1_Check(void)
{
    u8 reg;

    SI24R1_Write_Reg(WRITE_REG + RF_CH, 40);
    reg = SI24R1_Read_Reg(RF_CH);
    return (reg == 40) ? 1 : 0;
}
