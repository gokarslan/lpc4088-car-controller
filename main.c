#include "LPC407x_8x_177x_8x.h"
#include "Library/Ultrasonic.h"
#include "Library/SystemStructures.h"
#include "Library/Timer.h"
#include "Library/LCD.h"
#include "Library/Serial.h"
#include "Library/MMA7455.h"
#include "Library/Serial.h"
#include "Library/PWM.h"

#include <stdio.h>
#define ULTRASONIC_THRESHOLD 10

int lapCount = -1;
int isCarSeen = 0;
void init() {
	//Initialize, set mode of MMA7455 and calibrate
	MMA7455_Init();
	MMA7455_setMode(0x01);//2g
	MMA7455_calibrate();
	// Initialize serial communication for system diagnosis
	Serial_Init();
	// Initialize LCD
	LCD_Init();
	// Initialize PWM
	PWM_Init();
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
				sprintf(lcdDiagnosis, "Lap count is updated: %03d\r\n", ultrasonicSensorDistance);
				LCD_clearDisplay();
				LCD_write(lcdMessage);
				systemDiagnosis(lcdDiagnosis);
			}
		}else{
			isCarSeen = 0;
		}
	}
}
void updateSpeed(){
	int x=0;
	int y=0;
	int z=0;
	char speedDignosis[30];
	MMA7455_read(&x, &y, &z);
	if(x < 0){
		x = -1 * x;
	}
	if(x >= 5){
		PWM_Write(x * 1000 / 64);
		sprintf(speedDignosis, "Car speed is updated: %03d\r\n", x);
		systemDiagnosis(speedDignosis);
	}
	

}
	
	
	

void update() {
	updateLCD();
	updateSpeed();
}

int main() {
	init();
	__enable_irq();
	
	//while(ultrasonicSensorNewDataAvailable == 0){}
	while(1) {
		update();
		//__WFI();
	                                    }
}

