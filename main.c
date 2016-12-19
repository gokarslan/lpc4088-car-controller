#include "LPC407x_8x_177x_8x.h"
#include "Library/Ultrasonic.h"
#include "Library/SystemStructures.h"
#include "Library/Timer.h"
#include "Library/LCD.h"
#include "Library/Serial.h"
#include "Library/MMA7455.h"
#include "Library/Serial.h"

#include <stdio.h>
void init() {
	
	MMA7455_Init();
	//Write to Correct Mode to MMA7455
	MMA7455_setMode(0x01);//2g
	MMA7455_calibrate();
	Serial_Init();
	
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
	char temp[20];
	MMA7455_read(&x, &y, &z);
	//sprintf(temp, "Distance:%d\r\n", ultrasonicSensorDistance);
	sprintf(temp, "X: %d Y: %d Z: %d\r\n", x, y, z);
	serialTransmitData = temp;
	Serial_WriteData(*serialTransmitData++);
	while(!serialTransmitCompleted);
	/*if(ultrasonicSensorNewDataAvailable){
		
		
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
		
	}*/
	wait(100);
	

}

int main() {
	init();
	__enable_irq();
	
	//while(ultrasonicSensorNewDataAvailable == 0){}
	LED1_On();
	while(1) {
		update();
		//__WFI();
	                                    }
}

