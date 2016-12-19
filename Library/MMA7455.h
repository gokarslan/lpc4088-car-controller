#ifndef MMA7455_H
#define MMA7455_H

#include "I2C.h"
#include "Wait.h"

//Write the 1 left shifted version of 7-bit I2C address of MMA7455
#define MMA7455IC2Address 0x1D << 1

//Write the correct value of Mode Control register
#define MMA7455ModeControlRegister 0x16

//Write the correct value of Status register of MMA7455
#define MMA7455StatusRegister 0x09

void MMA7455_Init(void);

int MMA7455_setMode(int mode);
int MMA7455_getModeControl(void);
int MMA7455_setModeControl(uint8_t controlMode);

int MMA7455_calibrate(void);

int MMA7455_read(int* x, int* y, int* z);
int MMA7455_getStatus(void);

static int xOffset = 0;
static int yOffset = 0;
static int zOffset = 0;

#endif
