/*
 * helper_functions.c
 *
 *  Created on: Oct 6, 2020
 *      Author: user
 */

#include "helper_functions.h"
#include "lcd.h"
#include "keypad.h"
#include "timer.h"

uint8 clear = 0;

void get_password(uint8 password[])
{
	uint8 i = 0;
	for (i = 0; i < 5 ; i++)
	{
		password[i] = KeyPad_getPressedKey();
		_delay_ms(50);
		LCD_goToRowColumn(1,i);
		//LCD_intgerToString(password[i]);
		LCD_displayCharacter('*');
	}
	KeyPad_getPressedKey();
	LCD_clearScreen();
}

uint8 cmp (uint8 password_1[], uint8 password_2[])
{
	for(uint8 i = 0; i < 5; i++)
	{
		if (password_1[i] != password_2[i]) return 0;
	}

	return 1;
}

void LCD_clear(void)
{
	if (clear == 1)
	{
		LCD_clearScreen();
		clear = 0;
		SREG &= ~(1 << 7); // I_bit
	}
	SREG &= ~(1 << 7); // I_bit
}

