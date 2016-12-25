#ifndef DATASTRUCTURE_H
#define DATASTRUCTURE_H

#include "LPC407x_8x_177x_8x.h"

#define GPIO_ADDRESS	0x20098000

#define PORT0	((PORT_TypeDef*) PORT0_BASE)
#define PORT1	((PORT_TypeDef*) PORT1_BASE)
#define PORT2	((PORT_TypeDef*) PORT2_BASE)
#define PORT3	((PORT_TypeDef*) PORT3_BASE)
#define PORT4	((PORT_TypeDef*) PORT4_BASE)
#define PORT5	((PORT_TypeDef*) PORT5_BASE)

#define PORT0_BASE		(GPIO_ADDRESS + 0x000)
#define PORT1_BASE		(GPIO_ADDRESS + 0x020)
#define PORT2_BASE		(GPIO_ADDRESS + 0x040)
#define PORT3_BASE		(GPIO_ADDRESS + 0x060)
#define PORT4_BASE		(GPIO_ADDRESS + 0x080)
#define PORT5_BASE		(GPIO_ADDRESS + 0x0A0)

//Correctly define PORT_TypeDef struct.
typedef struct {
	volatile	uint8_t MASK;
	volatile	uint64_t DIR;
						uint32_t RESERVED0[4];
  volatile	uint16_t SET;
  volatile	uint32_t PIN;
  volatile  uint32_t CLR;
} PORT_TypeDef;

#endif
