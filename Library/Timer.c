#include "Timer.h"

void Ultrasonic_Capture_Timer_Init() {
	PCONP |= 1 << 23;
	
	TIMER3->CTCR = 0x0;
	
	TIMER3->TCR &= ~(1 << 0);
	
	TIMER3->TCR |= (1 << 1);
	
	TIMER3->PR = PERIPHERAL_CLOCK_FREQUENCY / 1000000 - 1;
	
	TIMER3->CCR = (1 << 0) | (1 << 2);
	
	TIMER3->TCR &= ~(1 << 1);
	
	TIMER3->TCR |= (1 << 0);

	NVIC_EnableIRQ(TIMER3_IRQn);
}

void TIMER3_IRQHandler() {
	if(ultrasonicSensorCaptureRisingEdge == 1) {
		LPC_TIM3->CCR = (1 << 1) | (1 << 2);
		ultrasonicSensorCaptureRisingEdge = 0;
	}
	else {
		ultrasonicSensorDuration = TIMER3->CR0;
		ultrasonicSensorNewDataAvailable = 1;
		
		LPC_TIM3->CCR = (1 << 0) | (1 << 2);
		ultrasonicSensorCaptureRisingEdge = 1;
	}
	
	TIMER3->IR = 1 << 4;
	TIMER3->TC = 0;
}
