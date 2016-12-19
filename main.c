#include "LPC407x_8x_177x_8x.h"
#include "Library/Ultrasonic.h"
#include "Library/SystemStructures.h"
#include "Library/Timer.h"
#include "Library/LCD.h"
#include "Library/Serial.h"

#include <stdio.h>
void init() {
	Ultrasonic_Init();
	Ultrasonic_Trigger_Timer_Init();
	Ultrasonic_Capture_Timer_Init();
	
	LED1_Init();
	LED2_Init();
	LED3_Init();
	LED4_Init();
	
	LED1_Off();
	LED2_Off();
	LED3_Off();
	LED4_Off();
	
	Ultrasonic_Start_Trigger_Timer();

	Serial_Init();
}


void update() {
	if(ultrasonicSensorNewDataAvailable){
		char temp[20];
		ultrasonicSensorDistance = ultrasonicSensorDuration/58;
		if(ultrasonicSensorDistance < 10){
			//LCD_write("<10");
			LED1_Off();
			LED2_Off();
		}else{
			//LCD_write(">=10");
			LED1_On();
			LED2_On();
		}
		
		sprintf(temp, "Distance:%d\r\n", ultrasonicSensorDistance);
		serialTransmitData = temp;
		Serial_WriteData(*serialTransmitData++);
		while(!serialTransmitCompleted);
	}
	

}

int main() {
	init();
	__enable_irq();
	
	while(ultrasonicSensorNewDataAvailable == 0){}
	LED1_On();
	while(1) {
		update();
		//__WFI();
	                                    }
}

