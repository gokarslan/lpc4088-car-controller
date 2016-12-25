#include "LPC407x_8x_177x_8x.h"
#include "Library/SystemStructures.h"
#include "Library/Serial.h"
#include "Library/MMA7455.h"
#include "Library/PWM.h"
#include <stdio.h>
char speedDignosis[40];
char accDignosis[40];
uint8_t speedChanged = 0;
void init() {
	//Initialize, set mode of MMA7455 and calibrate
	MMA7455_Init();
	MMA7455_setMode(0x01);//2g
	MMA7455_calibrate();
	// Initialize seraial communication for system diagnosis
	Serial_Init();
	// Initialize PWM
	PWM_Init();

}
void systemDiagnosis(){
	serialTransmitData = accDignosis;
	Serial_WriteData(*serialTransmitData++);
	while(!serialTransmitCompleted);
	if(speedChanged == 1){
		serialTransmitData = speedDignosis;
		Serial_WriteData(*serialTransmitData++);
		while(!serialTransmitCompleted);
		speedChanged = 0;
	}

}

void updateSpeed(){
	int x=0;
	int y=0;
	int z=0;
	int dutyCycle = 0;
	
	MMA7455_read(&x, &y, &z);
	sprintf(accDignosis, "MMA7455 is read(x,y,z): %d, %d, %d\r\n", x, y, z);
	if(x < 0){
		x = -1 * x;
	}
	if(x >= 5){
		dutyCycle = x * 1000 / 50;
		PWM_Write(dutyCycle);
		sprintf(speedDignosis, "Speed of Car is: %03d\r\n", dutyCycle);
		speedChanged = 1;
	}else{
		PWM_Write(0);
	}
	
	wait(100);
}
	

int main() {
	init();
	__enable_irq();
	while(1) {
		updateSpeed();
		systemDiagnosis();
	                                    
	}
}

