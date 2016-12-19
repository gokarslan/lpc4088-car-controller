#include "Serial.h"

char serialReceivedCharacter = 0;
char* serialTransmitData = 0;
uint8_t serialTransmitCompleted = 0;

void Serial_Init() {
	//Change the function of TX and RX pins for UART.
	Serial_UART_TX_PIN |= (1 << 0);
	Serial_UART_TX_PIN &= ~(1 << 1);
	Serial_UART_TX_PIN &= ~(1 << 2);
	Serial_UART_RX_PIN |= (1 << 0);
	Serial_UART_RX_PIN &= ~(1 << 1);
	Serial_UART_RX_PIN &= ~(1 << 2);	
	
	//Turn on UART0.
	
	PCONP |= (1 << 3);	
	//Enable FIFO for UART0.
	Serial_UART->FCR |= (1 << 0);
	
	Serial_UART->LCR |= (1 << 7);
	Serial_UART->DLL = 0x25;
	Serial_UART->DLM = 0x01;
	Serial_UART->FDR = 0x31;
	Serial_UART->LCR &= ~(1 << 7);
	
	Serial_UART->LCR |= (3 << 0);
	Serial_UART->LCR &= ~(1 << 2);
	Serial_UART->LCR |=(1 << 3);
	Serial_UART->LCR |= (1 << 4);
	Serial_UART->IER |= (1 << 0);
	Serial_UART->IER |= (1 << 1);
	NVIC_EnableIRQ(UART0_IRQn);
	NVIC_SetPriority(UART0_IRQn, 6);
	
	
	//In order to change the DLM, DLL and FDR values, Write correct code for enabling the access to Divisor Latches.

	//Write correct DLM, DLL and FDR values for 9600 baudrate

	//Write correct code for disabling the access to Divisor Latches.
	
	//Change LCR register value for 8-bit character transfer, 1 stop bits and Even Parity.
							
	//Enable the Receive Data Available and THRE Interrupt.
	
	//Enable UART0_IRQn Interrupt.
	
	//Set UART0_IRQn Priority to 5.
}

void UART0_IRQHandler() {	
	uint32_t currentInterrupt = ((Serial_UART->IIR & (0x7 << 1)) >> 1);
	
	//First if statement is for Receive Data Available interrupt. (0x00 is a dummy value.)
	if(currentInterrupt == 0x02) {
		serialReceivedCharacter = Serial_ReadData();
	}
	//Second if statement is for THRE interrupt
	else if(currentInterrupt == 0x01) {
		if(*serialTransmitData > 0) {
			Serial_WriteData(*serialTransmitData++);
		}
		else {
			serialTransmitCompleted = 1;
		}
	}
}

char Serial_ReadData() {
	return Serial_UART->RBR;
}

void Serial_WriteData(char data) {
	serialTransmitCompleted = 0;
	Serial_UART->THR = data;
}

