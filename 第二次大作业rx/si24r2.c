#include "si24r2.h"

/* ???? (RAM??,??????????) */
unsigned char RX_Addr[5] = {0x34, 0x43, 0x10, 0x10, 0x01};

/* ========== ???? ========== */
static void DelayUs(unsigned int us)
{
    while(us--)
    {
        _nop_(); _nop_(); _nop_(); _nop_();
    }
}

void DelayMs(unsigned int ms)
{
    unsigned int i, j;
    for(i = 0; i < ms; i++)
        for(j = 0; j < 120; j++);
}

/* ========== SPI ???? ========== */
static unsigned char SPI_RW(unsigned char byte)
{
    unsigned char i;
    unsigned char retval = 0;
    
    for(i = 0; i < 8; i++)
    {
        retval <<= 1;
        
        if(byte & 0x80)
            MOSI = 1;
        else
            MOSI = 0;
        byte <<= 1;
        
        SCLK = 1;
        _nop_(); _nop_();
        
        if(MISO)
            retval |= 0x01;
        
        SCLK = 0;
        _nop_(); _nop_();
    }
    return retval;
}

/* ========== ????? ========== */
unsigned char SI24R2_ReadReg(unsigned char reg)
{
    unsigned char val;
    SI24R2_CSN_CLR();
    SPI_RW(CMD_R_REGISTER | reg);
    val = SPI_RW(CMD_NOP);
    SI24R2_CSN_SET();
    return val;
}

unsigned char SI24R2_WriteReg(unsigned char reg, unsigned char value)
{
    unsigned char status;
    SI24R2_CSN_CLR();
    status = SPI_RW(CMD_W_REGISTER | reg);
    SPI_RW(value);
    SI24R2_CSN_SET();
    return status;
}

void SI24R2_ReadBuf(unsigned char reg, unsigned char *pBuf, unsigned char len)
{
    unsigned char i;
    SI24R2_CSN_CLR();
    SPI_RW(reg);
    for(i = 0; i < len; i++)
        pBuf[i] = SPI_RW(CMD_NOP);
    SI24R2_CSN_SET();
}

void SI24R2_WriteBuf(unsigned char reg, unsigned char *pBuf, unsigned char len)
{
    unsigned char i;
    SI24R2_CSN_CLR();
    SPI_RW(reg);
    for(i = 0; i < len; i++)
        SPI_RW(pBuf[i]);
    SI24R2_CSN_SET();
}

void SI24R2_FlushTX(void)
{
    SI24R2_CSN_CLR();
    SPI_RW(CMD_FLUSH_TX);
    SI24R2_CSN_SET();
}

void SI24R2_FlushRX(void)
{
    SI24R2_CSN_CLR();
    SPI_RW(CMD_FLUSH_RX);
    SI24R2_CSN_SET();
}

unsigned char SI24R2_GetStatus(void)
{
    return SI24R2_ReadReg(REG_STATUS);
}

/* ========== ??? ========== */
void SI24R2_Init(void)
{
    /* IO??? */
    SI24R2_CE = 0;
    SI24R2_CSN = 1;
    
    /* SPI????? */
    MOSI = 0;
    SCLK = 0;
    
    DelayMs(20);    /* ???? */
    
    /* ?????? */
    SI24R2_WriteReg(REG_CONFIG, 0x0E);          /* ??, 2??CRC, TX?? */
    SI24R2_WriteReg(REG_EN_AA, 0x01);           /* ??0???? */
    SI24R2_WriteReg(REG_EN_RXADDR, 0x01);       /* ????0 */
    SI24R2_WriteReg(REG_SETUP_AW, 0x03);        /* 5???? */
    SI24R2_WriteReg(REG_SETUP_RETR, RETR_SETUP);
    SI24R2_WriteReg(REG_RF_CH, RF_CHANNEL);
    SI24R2_WriteReg(REG_RF_SETUP, RF_SETUP_VAL);
    SI24R2_WriteReg(REG_STATUS, 0x7E);          /* ???? */
    
    /* ??? */
    SI24R2_WriteBuf(CMD_W_REGISTER | REG_RX_ADDR_P0, RX_Addr, 5);
    SI24R2_WriteBuf(CMD_W_REGISTER | REG_TX_ADDR, RX_Addr, 5);
    
    SI24R2_WriteReg(REG_RX_PW_P0, PAYLOAD_LEN);
    SI24R2_WriteReg(REG_DYNPD, 0x00);
    SI24R2_WriteReg(REG_FEATURE, 0x00);
    
    SI24R2_FlushTX();
    SI24R2_FlushRX();
    SI24R2_WriteReg(REG_STATUS, 0x7E);
}

/* ???????? */
unsigned char SI24R2_Check(void)
{
    unsigned char test;
    test = SI24R2_ReadReg(REG_RF_SETUP);
    return (test == RF_SETUP_VAL);
}

/* ========== ???? ========== */
void SI24R2_SetTXMode(void)
{
    SI24R2_CE_CLR();
    SI24R2_WriteReg(REG_CONFIG, 0x0E);  /* PWR_UP=1, PRIM_RX=0 */
    SI24R2_CE_SET();
    DelayUs(150);
}

void SI24R2_SetRXMode(void)
{
    SI24R2_CE_CLR();
    SI24R2_WriteReg(REG_CONFIG, 0x0F);  /* PWR_UP=1, PRIM_RX=1 */
    SI24R2_CE_SET();
    DelayUs(150);
}

/* ========== ????? ========== */
unsigned char SI24R2_TxPacket(unsigned char *txBuf)
{
    unsigned char status;
    unsigned int timeout;
    
    SI24R2_CE_CLR();
    SI24R2_WriteBuf(CMD_W_TX_PAYLOAD, txBuf, PAYLOAD_LEN);
    SI24R2_CE_SET();
    DelayUs(20);
    
    /* ??IRQ??,??? */
    timeout = 5000;
    while(SI24R2_IRQ_READ() != 0 && timeout--)
    {
        DelayUs(10);
    }
    
    SI24R2_CE_CLR();
    
    if(timeout == 0)
    {
        SI24R2_WriteReg(REG_STATUS, 0x7E);
        SI24R2_FlushTX();
        return 0;
    }
    
    status = SI24R2_ReadReg(REG_STATUS);
    SI24R2_WriteReg(REG_STATUS, status);
    
    if(status & STATUS_TX_DS)
    {
        return 1;
    }
    else if(status & STATUS_MAX_RT)
    {
        SI24R2_FlushTX();
        return 2;
    }
    return 0;
}

/* ========== ????? ========== */
unsigned char SI24R2_RxPacket(unsigned char *rxBuf)
{
    unsigned char status;
    
    status = SI24R2_ReadReg(REG_STATUS);
    
    if(status & STATUS_RX_DR)
    {
        /* ????:????????CE,?????? */
        SI24R2_ReadBuf(CMD_R_RX_PAYLOAD, rxBuf, PAYLOAD_LEN);
        SI24R2_WriteReg(REG_STATUS, status);
        return 1;
    }
    return 0;
}