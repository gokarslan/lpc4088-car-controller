#ifndef I2C_H
#define I2C_H

#include "LPC407x_8x_177x_8x.h"
#include "SystemStructures.h"
#include "Wait.h"

typedef struct
{
  __IO uint32_t CONSET;
  __I  uint32_t STAT;
  __IO uint32_t DAT;
  __IO uint32_t ADR0;
  __IO uint32_t SCLH;
  __IO uint32_t SCLL;
  __O  uint32_t CONCLR;
  __IO uint32_t MMCTRL;
  __IO uint32_t ADR1;
  __IO uint32_t ADR2;
  __IO uint32_t ADR3;
  __I  uint32_t DATA_BUFFER;
  __IO uint32_t MASK0;
  __IO uint32_t MASK1;
  __IO uint32_t MASK2;
  __IO uint32_t MASK3;
} I2C_TypeDef;

//Write the Base Address of I2C0
#define I2C0_BASE	0x4001C000
#define I2C0	((I2C_TypeDef*) I2C0_BASE)

//Write the IOCON address of  I2C0 Data Input/Output
#define I2C_Data_PIN_ADDRESS	0x4002C06C //P0.27
#define I2C_Data_PIN	*((volatile uint32_t*)(I2C_Data_PIN_ADDRESS))

//Write the IOCON address of  I2C0 Clock Input/Output
#define I2C_Clock_PIN_ADDRESS	0x4002C070 //P0.28
#define I2C_Clock_PIN	*((volatile uint32_t*)(I2C_Clock_PIN_ADDRESS))

//Write I2CDutyCycle which is (I2CSCLL + I2CSCLH) / 2
#define I2CDutyCycle 450

void I2C_Init(void);

int I2C_Start(void);

int I2C_Stop(void);

int I2C_Write(uint32_t address, const char* data,int length, int repeated);

int I2C_WriteData(uint32_t address, const char* data,int length, int stop);

int I2C_Read(uint32_t address, char* data, int length, int repeated);

int I2C_ReadData(uint32_t address, char* data, int length, int stop);

int I2C_DoWrite(int value);

int I2C_DoRead(int last);

int I2C_Wait_SI(void);
	
#endif
