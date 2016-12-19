#include "I2C.h"

void I2C_Init() {	
	//Turn on I2C0
	PCONP |= 1 << 7;
	
	I2C0->SCLL = I2CDutyCycle;
	I2C0->SCLH = I2CDutyCycle;
	
	I2C0->CONCLR =	(1 << 5)
								| (1 << 3)
								| (1 << 2);
	
	//In Initialization routine, Write Correct value to CONSET register for Master only functions
	I2C0->CONSET = 0x40;
	
	I2C_Data_PIN &= 0x03;
	I2C_Data_PIN |= 0x01;
	
	I2C_Clock_PIN &= 0x03;
	I2C_Clock_PIN |= 0x01;
}

int I2C_Start() {
	int status = 0;
	
	I2C0->CONCLR =	(1 << 5)
								| (1 << 3)
								| (1 << 2);
    
	I2C0->CONSET =	(1 << 2);
	
	//In Start Master Transmit function, Write Correct Value to CONSET register
	I2C0->CONSET = 0x20;
	
	I2C_Wait_SI();
	
	status = I2C0->STAT;
    
	I2C0->CONCLR =	(1 << 5);
	
	return status;
}

int I2C_Stop() {
	int timeout = 0;

	I2C0->CONSET =	(1 << 4);
	
	I2C0->CONCLR =	(1 << 3);
	
	while(I2C0->CONSET & (1 << 4)) {
		timeout ++;
		if (timeout > 100000) return 1;
	}

	return 0;
}

int I2C_Write(uint32_t address, const char* data,int length, int repeated) {
	int stop;
	int written;

	if(repeated == 0) {
		stop = 1;
	}
	else {
		stop = 0;
	}
	
	written = I2C_WriteData(address, data, length, stop);
	
	return length != written;
}

int I2C_WriteData(uint32_t address, const char* data,int length, int stop) {
	int status;
	int i;
    
	status = I2C_Start();

	//Stop and Return When A START or A repeated START Condition has not been transmitted.
	if ((status != 0x08) && (status != 0x10)) {
		I2C_Stop();
		return -1;
	}

	status = I2C_DoWrite(address & 0xFE);
	
	//Stop and Return When First Data Byte is not Transmitted
	if (status != 0x18) {
		I2C_Stop();
		return -1;
	}

	for (i=0; i<length; i++) {
		status = I2C_DoWrite(data[i]);
		//Stop and Return When Data is not Transmitted
		if (status != 0x28) {
			I2C_Stop();
			return i;
		}
	}
	
	if (stop) {
		I2C_Stop();
	}

	return length;
}

int I2C_Read(uint32_t address, char* data, int length, int repeated) {
	int stop;
	int readed;
	if(repeated == 0) {
		stop = 1;
	}
	else {
		stop = 0;
	}
	
	readed = I2C_ReadData(address, data, length, stop);
	
	return length != readed;
}

int I2C_ReadData(uint32_t address, char* data, int length, int stop) {
	int status;
	int count;
	
	int value;
	status = I2C_Start();

	 if ((status != 0x10) && (status != 0x08)) {
		I2C_Stop();
		return -1;
	}

	status = I2C_DoWrite(address | 0x01);
	
	//Stop and Return When ACK is not received
	if (status != 0x40) {
		I2C_Stop();
		return -1;
	}

	for (count = 0; count < (length - 1); count++) {
		int value = I2C_DoRead(0);
		status = I2C0->STAT;
		
		//Stop and Return When Data is not received
		if (status != 0x50) {
			I2C_Stop();
			return count;
	}
		
		data[count] = value;
	}
	
	value = I2C_DoRead(1);
	
	status = I2C0->STAT;
	
	//Stop and Return When Last Data is not received
	if (status != 0x58) {
		I2C_Stop();
		return length - 1;
	}

	data[count] = value;
	
	if (stop) {
		I2C_Stop();
	}

	return length;
}

int I2C_DoWrite(int value) {
	I2C0->DAT = value;

	I2C0->CONCLR = (1 << 3);

    I2C_Wait_SI();
    return I2C0->STAT;
}

int I2C_DoRead(int last) {
	if(last) {
		I2C0->CONCLR = (1 << 2);

	}
	else {
		I2C0->CONSET = (1 << 2);
	}

	I2C0->CONCLR =	(1 << 3);

	I2C_Wait_SI();

	return (I2C0->DAT & 0xFF);
}

int I2C_Wait_SI() {
    int timeout = 0;
    while (!(I2C0->CONSET & (1 << 3))) {
        timeout++;
        if (timeout > 100000) return -1;
    }
    return 0;
}
