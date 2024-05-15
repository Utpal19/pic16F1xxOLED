/* 
 * File:   i2c_2.h
 * Author: utpal
 *
 * Created on 15 May, 2024, 10:58 AM
 */

#ifndef I2C_2_H
#define	I2C_2_H

#ifdef	__cplusplus
extern "C" {
#endif

// I2C Master Clock Speed
#define _XTAL_FREQ 4000000  // Set this according to your actual oscillator frequency
#define I2C_STANDARD_SPEED 100000 // Set your desired I2C baudrate
    
    
void setup(void);
void I2C_Master_Init(const unsigned long c);
void I2C_Master_Wait(void);
void I2C_Master_Start(void);
void I2C_Master_Stop(void);
void I2C_Master_Write(uint8_t d);
uint8_t I2C_Master_Read(uint8_t a);
void I2C_Master_Write_Str(uint8_t* arg, uint8_t size);



#ifdef	__cplusplus
}
#endif

#endif	/* I2C_2_H */

