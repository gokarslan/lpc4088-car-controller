#include "GPIO.h"

void GPIO_DIR_Write(GPIO_TypeDef* PORT,uint32_t MASK,uint8_t value) {
	if(value == 0) {
		PORT->DIR &= ~MASK;
	}
	else {
		PORT->DIR |= MASK;
	}
}

void GPIO_PIN_Write(GPIO_TypeDef* PORT,uint32_t MASK,uint8_t value) {
	if(value == 0) {
		PORT->PIN &= ~MASK;
	}
	else {
		PORT->PIN |= MASK;
	}
}

void LED1_Init() {
	//Write code for initializing LED1.
}

void LED2_Init() {
	//Write code for initializing LED2.
}

void LED3_Init() {
	//Write code for initializing LED3.
}

void LED4_Init() {
	//Write code for initializing LED4.
}

void LED1_Off() {
	//Write code for turning off LED1.
}

void LED2_Off() {
	//Write code for turning off LED2.
}

void LED3_Off() {
	//Write code for turning off LED3.
}

void LED4_Off() {
	//Write code for turning off LED4.
}

void LED1_On() {
	//Write code for turning on LED1.
}

void LED2_On() {
	//Write code for turning on LED2.
}

void LED3_On() {
	//Write code for turning on LED3.
}

void LED4_On() {
	//Write code for turning on LED4.
}

