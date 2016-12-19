#include "MMA7455.h"

void MMA7455_Init() {
	I2C_Init();
}

int MMA7455_setMode(int mode) {
	int isModeStarted = 0;
	int controlMode = 0;

	do {
		controlMode = MMA7455_getModeControl();
		if (controlMode < 0) break;

		controlMode &= ~(0x03 << 0);
		controlMode |= mode << 0;

		if (MMA7455_setModeControl(controlMode)) {
			break;
		}

		isModeStarted = 1;
	} while(0);

	return isModeStarted;
}

int MMA7455_getModeControl() {
    int result = -1;
    char data[1];

    do {
        data[0] = MMA7455ModeControlRegister;
        if (I2C_Write(MMA7455IC2Address, data, 1, 0) != 0) break;

        if (I2C_Read(MMA7455IC2Address, data, 1, 0) != 0) break;

        result = data[0];
    } while (0);
		
    return result;
}

int MMA7455_setModeControl(uint8_t controlMode) {
	int result = -1;
   char data[2];

    do {
        data[0] = MMA7455ModeControlRegister;
        data[1] = (char)controlMode;
        if (I2C_Write(MMA7455IC2Address, data, 2, 0) != 0) break;

        result = 0;

    } while (0);
	return result;
}

int MMA7455_calibrate() {
		int result = 0;
    int failed = 0;
		int i;

    int32_t x = 0;
    int32_t y = 0;
    int32_t z = 0;

    int32_t xr = 0;
    int32_t yr = 0;
    int32_t zr = 0;

    int xOff = 0;
    int yOff = 0;
    int zOff = 16;

    do {
        for (i = 0; i < 6; i++) {
            if (!MMA7455_read(&xr, &yr, &zr)) {
                failed = 1;
                break;
            }
            x += xr;
            y += yr;
            z += zr;

            wait(100);
        }

        if (failed) break;
				
        x /= 6;
        y /= 6;
        z /= 6;

        xOff -= x;
        yOff -= y;
        zOff -= z;

        xOffset = xOff;
        yOffset = yOff;
        zOffset = zOff;
				
        result = 1;
    } while (0);
    return result;
}

int MMA7455_read(int* x, int* y, int* z) {
	int result = 0;
	int status = 0;
	char buf[6];
	
    do {
      status = MMA7455_getStatus();
    } while (status >= 0 && (status & (1 << 0)) == 0);


    do {
        if (status < 0) break;

        buf[0] = 0x00;
        if (I2C_Write(MMA7455IC2Address, buf, 1,0) != 0) break;
        if (I2C_Read(MMA7455IC2Address, buf, 6,0) != 0) break;
			
        if (buf[1] & 0x02) buf[1] |= 0xFC;
        if (buf[3] & 0x02) buf[3] |= 0xFC;
        if (buf[5] & 0x02) buf[5] |= 0xFC;

        *x = (int16_t)((buf[1] << 8) | buf[0]) + xOffset;
        *y = (int16_t)((buf[3] << 8) | buf[2]) + yOffset;
        *z = (int16_t)((buf[5] << 8) | buf[4]) + zOffset;


        result = 1;

    } while(0);
		
    return result;
}

int MMA7455_getStatus() {
    int result = -1;
    char data[1];

    do {
        data[0] = MMA7455StatusRegister;
        if (I2C_Write(MMA7455IC2Address, data, 1,0) != 0) break;

        if (I2C_Read(MMA7455IC2Address, data, 1,0) != 0) break;

        result = data[0];

    } while (0);
		
    return result;
}
