#include "LPC407x_8x_177x_8x.h"
#include "Library/Ultrasonic.h"
#include "Library/SystemStructures.h"
#include "Library/Timer.h"
#include "Library/LCD.h"
#include "Library/Serial.h"

#include <stdio.h>
#define ULTRASONIC_THRESHOLD 10

int lapCount = -1;
int isCarSeen = 0;
void init() {

	// Initialize serial communication for system diagnosis
	Serial_Init();
	// Initialize LCD
	LCD_Init();
	// Initialize Ultrasonic
	Ultrasonic_Init();
	Ultrasonic_Trigger_Timer_Init();
	Ultrasonic_Capture_Timer_Init();
	Ultrasonic_Start_Trigger_Timer();
}
void systemDiagnosis(char* message){
	serialTransmitData = message;
	Serial_WriteData(*serialTransmitData++);
	while(!serialTransmitCompleted);
}
void updateLCD(){
	char lcdMessage[9];
	char lcdDiagnosis[31];
	if(ultrasonicSensorNewDataAvailable){
		ultrasonicSensorDistance = ultrasonicSensorDuration/58;
		if(ultrasonicSensorDistance <= ULTRASONIC_THRESHOLD){
			if(isCarSeen == 0){
				lapCount ++;
				isCarSeen = 1;
				sprintf(lcdMessage, "LAP: %03d",lapCount);
				sprintf(lcdDiagnosis, "Lap count is updated: %03d\r\n", lapCount);
				LCD_clearDisplay();
				LCD_write(lcdMessage);
				systemDiagnosis(lcdDiagnosis);
			}
		}else{
			isCarSeen = 0;
		}
	}
}

int main() {
	init();
	__enable_irq();
	
	while(ultrasonicSensorNewDataAvailable == 0){}
	while(1) {
		updateLCD();
		__WFI();
	                                    }
}
