#include "LCD.h"

void LCD_Init(void) {

	//Set the direction of LPC4088 pins, which are connected to  LCD, as output by using PORT data structure and MASK values.
	RS_PORT->DIR |= RS_MASK;
	RW_PORT->DIR |= RW_MASK;
	EN_PORT->DIR |= EN_MASK;
	DATA0_PORT->DIR |= DATA0_MASK;
	DATA1_PORT->DIR |= DATA1_MASK;
	DATA2_PORT->DIR |= DATA2_MASK;
	DATA3_PORT->DIR |= DATA3_MASK;
	
	LCD_command(0x03);//Write the correct value
	LCD_command(0x03);//Write the correct value
	LCD_command(0x03);//Write the correct value
	LCD_command(0x02);//Write the correct value
	
	LCD_command(0x28);
	
	LCD_cursorBlinking();
	
	LCD_cursorAutoIncrement();
	
	LCD_clearDisplay();
	
	LCD_setCursorHome();
}

void LCD_command(uint8_t data) {
	//Write correct value to RS Pin.
	GPIO_PIN_Write(RS_PORT,RS_MASK,0x00);
	GPIO_PIN_Write(DATA0_PORT,DATA0_MASK,(data >> 4 & (0x01)));
	GPIO_PIN_Write(DATA1_PORT,DATA1_MASK,(data >> 5 & (0x01)));
	GPIO_PIN_Write(DATA2_PORT,DATA2_MASK,(data >> 6 & (0x01)));
	GPIO_PIN_Write(DATA3_PORT,DATA3_MASK,(data >> 7 & (0x01)));
	
	LCD_toogle();
	
	GPIO_PIN_Write(DATA0_PORT,DATA0_MASK,(data >> 0 & (0x01)));
	GPIO_PIN_Write(DATA1_PORT,DATA1_MASK,(data >> 1 & (0x01)));
	GPIO_PIN_Write(DATA2_PORT,DATA2_MASK,(data >> 2 & (0x01)));
	GPIO_PIN_Write(DATA3_PORT,DATA3_MASK,(data >> 3 & (0x01)));
	
	LCD_toogle();
}

void LCD_data(uint8_t data) {
	//Write correct value to RS Pin.
	GPIO_PIN_Write(RS_PORT,RS_MASK,0x01);
	GPIO_PIN_Write(DATA0_PORT,DATA0_MASK,(data >> 4 & (0x01)));
	GPIO_PIN_Write(DATA1_PORT,DATA1_MASK,(data >> 5 & (0x01)));
	GPIO_PIN_Write(DATA2_PORT,DATA2_MASK,(data >> 6 & (0x01)));
	GPIO_PIN_Write(DATA3_PORT,DATA3_MASK,(data >> 7 & (0x01)));
	
	LCD_toogle();
	
	GPIO_PIN_Write(DATA0_PORT,DATA0_MASK,(data >> 0 & (0x01)));
	GPIO_PIN_Write(DATA1_PORT,DATA1_MASK,(data >> 1 & (0x01)));
	GPIO_PIN_Write(DATA2_PORT,DATA2_MASK,(data >> 2 & (0x01)));
	GPIO_PIN_Write(DATA3_PORT,DATA3_MASK,(data >> 3 & (0x01)));
	
	LCD_toogle();
}

void LCD_write(char* data) {
	while(*data > 0)  {
		LCD_data(*data++);
	}
}

void LCD_toogle() {
	wait(10);
	EN_PORT->PIN |= EN_MASK;
	wait(10);
	EN_PORT->PIN &= ~EN_MASK;
	wait(10);
}

void LCD_clearDisplay() {
	LCD_command(0x01);
}

void LCD_clearDisplayWithoutRAM() {
	LCD_command(0x08);
}

void LCD_cursorON() {
	LCD_command(0x0E);
}

void LCD_cursorOFF() {
	LCD_command(0x0C);
}

void LCD_cursorBlinking() {
	LCD_command(0x0F);
}

void LCD_cursorAutoIncrement() {
	LCD_command(0x06);
}

void LCD_shiftLeft() {
	LCD_command(0x18);
}

void LCD_shiftRight() {
	LCD_command(0x1C);
}

void LCD_moveCursorLeft() {
	LCD_command(0x10);
}

void LCD_moveCursorRight() {
	LCD_command(0x14);
}

void LCD_setCursorHome() {
	LCD_command(0x02);
}

void LCD_setCursorPositionFirstLine(uint8_t position) {
	LCD_command(0x80 + position);
}

void LCD_setCursorPositionSecondLine(uint8_t position) {
	LCD_command(0xC0 + position);
}
