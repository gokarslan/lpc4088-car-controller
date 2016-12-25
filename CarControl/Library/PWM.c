#include "PWM.h"
#define IOCON_MOTOR_ADDRESS	0x4002C088
#define IOCON_MOTOR	*((volatile uint32_t*)(IOCON_MOTOR_ADDRESS))
	

void PWM_Init() {
	IOCON_MOTOR |= 3;
	//Tur|n on PWM
	PCONP |= 1 << 5;
	
	//Enable PWM output for corresponding pin.
	PWMX->PCR = 1 << 9;
	//PWM gives pulse every 20 ms.
	PWMX->MR0 = (PERIPHERAL_CLOCK_FREQUENCY / 1000000) * 20 * 1000;
	
	PWMX->MR1 = 0;
	
	//Enable PWM Match 0 and 3 Latch.
	PWMX->LER |= 1 << 0;
	PWMX->LER |= 1 << 1;
	
	//Write the Correct Values to TCR for Enabling Counter and PWM
	PWMX->TCR |= 1 << 0;
	PWMX->TCR |= 1 << 3;
	
	PWM_Write(1000);
}

void PWM_Write(uint32_t value) {
	uint32_t trueValue;
	
	if(value > 1000) {
		value = 1000;
	}
	
	trueValue = (uint32_t)(((PWMX->MR0) * value) / 1000);
	
	if (trueValue == PWMX->MR0) {
		trueValue++;
	}
	
	PWMX->MR1 = trueValue;
	
	PWMX->LER |= 1 << 1;
}
