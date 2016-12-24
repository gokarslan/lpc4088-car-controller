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
void init() {
	
	MMA7455_Init();
	//Write to Correct Mode to MMA7455
	MMA7455_setMode(0x01);//2g
	MMA7455_calibrate();
	Serial_Init();
	LCD_Init();
	PWM_Init();
	
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
	
}


void update() {
	int x=0;
	int y=0;
	int z=0;
	char serialTemp[20];
	char lcdTemp[9];
	PWM_Write(900);
	if(ultrasonicSensorNewDataAvailable){
		ultrasonicSensorDistance = ultrasonicSensorDuration/58;
		if(ultrasonicSensorDistance <= ULTRASONIC_THRESHOLD){
			lapCount ++;
			sprintf(lcdTemp, "LAP: %03d",lapCount);
			LCD_clearDisplay();
			LCD_write(lcdTemp);
			
			
		}
		
	}
	MMA7455_read(&x, &y, &z);
	//sprintf(temp, "Distance:%d\r\n", ultrasonicSensorDistance);
	sprintf(serialTemp, "X: %d Y: %d Z: %d\r\n", x, y, z);
	serialTransmitData = serialTemp;
	Serial_WriteData(*serialTransmitData++);
	while(!serialTransmitCompleted);
	
	//wait(100);
	

}

int main() {
	init();
	__enable_irq();
	
	while(ultrasonicSensorNewDataAvailable == 0){}
	while(1) {
		update();
		__WFI();
	                                    }
}

