

#include <xc.h>
#include "i2c_2.h"


void setup(void) {
    // OSCILLATOR Source Selection
    OSCCON1 = 0x60;  // Set HFINTOSC as the oscillator source
    OSCFRQ = 0x02;   // Set HFINTOSC to 1 MHz 
    LATB = 0x6;
//    TRISB = 0xFF;
    // I/O pins for I2C
    TRISBbits.TRISB1 = 1; // Set SCL (RB1) as input
    TRISBbits.TRISB2 = 1; // Set SDA (RB2) as input
    ANSELB = 0xF9;
    /** PPS registers */
    SSP2CLKPPS = 0x9;   //RB1->MSSP2:SCL2;
    RB1PPS = 0x16;      //RB1->MSSP2:SCL2;
    SSP2DATPPS = 0xA;   //RB2->MSSP2:SDA2;
    RB2PPS = 0x17;      //RB2->MSSP2:SDA2;  
    
    __delay_ms(500);
    // Setup I2C
    I2C_Master_Init(100000); // Initialize I2C Master with 100kHz clock
}

void I2C_Master_Init(const unsigned long c) {
    // SSP2CON1 settings
    SSP2CON1 = 0b00101000;  // SSPEN enabled, I2C Master mode
    SSP2CON2 = 0x00;

    // Clock = FOSC / (4 * (SSPxADD+1))
//    SSP2ADD = (_XTAL_FREQ / (4 * c)) - 1;
    SSP2ADD = 0x9;

    // SSP2 Status Register
    SSP2STAT = 0x00;    // Slew rate control disabled for Standard Speed mode
}

void I2C_Master_Start(void) {
    I2C_Master_Wait();
    SSP2CON2bits.SEN = 1; // Initiate Start condition
}

void I2C_Master_Stop(void) {
    I2C_Master_Wait();
    SSP2CON2bits.PEN = 1; // Initiate Stop condition
}

void I2C_Master_Wait(void) {
    while ((SSP2STAT & 0x04) || (SSP2CON2 & 0x1F)); // Wait for Start and Stop to clear
}

void I2C_Master_Write(uint8_t d) {
    I2C_Master_Wait();
    SSP2BUF = d; // Write data to SSPBUF
}

uint8_t I2C_Master_Read(uint8_t a) {
    uint8_t temp;
    I2C_Master_Wait();
    SSP2CON2bits.RCEN = 1; // Enable receive
    I2C_Master_Wait();
    temp = SSP2BUF;        // Read the received data
    I2C_Master_Wait();
    SSP2CON2bits.ACKDT = (a) ? 0 : 1; // Acknowledge bit (0 = ACK, 1 = NACK)
    SSP2CON2bits.ACKEN = 1;           // Start Acknowledge sequence
    return temp;
}

void I2C_Master_Write_Str(uint8_t* arg, uint8_t size)
{
    uint8_t s_data[64], i = 0;
//    strncpy
    while(size-- > 0)
    {
        I2C_Master_Write(arg[i++]);
    }
    
}