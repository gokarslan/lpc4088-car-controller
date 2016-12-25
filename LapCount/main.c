#include "LPC407x_8x_177x_8x.h"
#include "Library/Ultrasonic.h"
#include "Library/SystemStructures.h"
#include "Library/Timer.h"
#include "Library/LCD.h"
#include "Library/Serial.h"

#include <stdio.h>
#define ULTRASONIC_MAX_THRESHOLD 10
#define ULTRASONIC_MIN_THRESHOLD 1
#define CAR_NOT_SEEN_MAX 40
uint16_t lapCount = 0;
uint16_t carNotSeen = 0;
void init() {

	// Initialize serial communication for system diagnosis
	Serial_Init();
	// Initialize LCD
	LCD_Init();
	LCD_clearDisplay();
	LCD_write("LAP: 000");
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
		sprintf(lcdDiagnosis, "New distance read: %03d\r\n", ultrasonicSensorDistance);
		systemDiagnosis(lcdDiagnosis);
		if(ultrasonicSensorDistance <= ULTRASONIC_MAX_THRESHOLD && ultrasonicSensorDistance >= ULTRASONIC_MIN_THRESHOLD){
			if(carNotSeen >= CAR_NOT_SEEN_MAX){
				lapCount ++;
				carNotSeen = 0;
				sprintf(lcdMessage, "%03d",lapCount);
				sprintf(lcdDiagnosis, "Lap count is updated: %03d\r\n", lapCount);
				//LCD_clearDisplay();
				LCD_moveCursorLeft();
				LCD_moveCursorLeft();
				LCD_moveCursorLeft();
				LCD_write(lcdMessage);
				systemDiagnosis(lcdDiagnosis);
			}
		}else{
			if(carNotSeen < CAR_NOT_SEEN_MAX){
				carNotSeen++ ;
			}
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

