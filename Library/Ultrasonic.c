#include "Ultrasonic.h"

uint32_t ultrasonicSensorDuration = 0;
uint32_t ultrasonicSensorDistance = 0;
uint8_t ultrasonicSensorNewDataAvailable = 0;

uint8_t ultrasonicSensorTriggerStart = 0;
uint8_t ultrasonicSensorCaptureRisingEdge = 0;

void Ultrasonic_Init() {	
	//Give the Correct Function Values to IOCON_TRIGGER and IOCON_ECHO
	IOCON_TRIGGER |= (1 << 0);
	IOCON_TRIGGER |= (1 << 1);
	IOCON_TRIGGER &= ~(1 << 2);
	
	IOCON_ECHO |= (1 << 0);
	IOCON_ECHO |= (1 << 1);
	IOCON_ECHO &= ~(1 << 2);
}

void Ultrasonic_Trigger_Timer_Init() {
	
	PCONP |= (1 << 22);
	TIMER2->CTCR = 0x00;
	TIMER2->TCR &= ~(1 << 0);
	TIMER2->TCR |= (1 << 1);
	TIMER2->PR = PERIPHERAL_CLOCK_FREQUENCY/1000000-1;
	TIMER2->EMR |= (1 << 3);
	TIMER2->EMR |= (3 << 10);
	
	//Enable Timer2.
	
	
	//Change the mode of Timer2 to Timer Mode.
	
	
	//Disable Timer Counter and Prescale Counter for Timer2.
	
	//Reset Timer Counter and Prescale Counter for Timer2.
	
	//Change PR Register value for 1 microsecond incrementing
	
	//Write the Correct Configuration for EMR (Toggle Output Value and Initial value is HIGH)
	
	//Enable TIMER2_IRQn (Interrupt Request).
	
	//Set Priority Timer2 IRQ as 5.
	
	//Clear pendings for Timer2.
}

void Ultrasonic_Start_Trigger_Timer() {
	//Give correct value to MR3 Register for 10 microsecond
	
	//Enable interrupt for MR3 register, if MR3 register matches the TC.
	
	//Remove the reset on counters of Timer2.
	
	//Enable Timer Counter and Prescale Counter for counting.
}

void TIMER2_IRQHandler() {
	if(ultrasonicSensorTriggerStart == 0) {
		//Change MR3 Register Value for Suggested Waiting
		TIMER2->MR3 = 0;
		ultrasonicSensorTriggerStart = 1;
	}
	else {
		TIMER2->MR3 = 10;
		ultrasonicSensorTriggerStart = 0;
	}
	
	//Write HIGH bit value to IR Register for Corresponding Interrupt
	TIMER2->IR = 0 << 0;
	TIMER2->TC = 0;
}

