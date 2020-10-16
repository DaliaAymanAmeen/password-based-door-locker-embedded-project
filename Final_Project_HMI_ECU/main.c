/*
 * main.c
 *
 *  Created on: Oct 5, 2020
 *      Author: user
 */

#include "lcd.h"
#include "uart.h"
#include "keypad.h"
#include "helper_functions.h"
#include "timer.h"

#define READY 0x10
#define MATCHING 0x20
#define DISMATCHING 0x30
#define THEIF 0x40

int main(void)
{
	LCD_init();
	UART_config config = {BIT_8, DISABLE, STOP_BIT_1};  // 8_bit frame, parity disabled, 1 stop bit
	uart_init(&config);

	uint8 compare;
	uint8 new_password[5];
	uint8 re_new_password[5];

	/* step(1) "enter new password, re_enter the new password, and check whether they are matching or not" */
	do
	{
		LCD_displayString("enter new pass: ");
		get_password(new_password);
		LCD_displayString("re_enter new pass: ");
		get_password(re_new_password);
		compare = cmp (new_password, re_new_password);
	}
	while (!compare);

	/* send the new password using UART to the MC2 */
	uart_sendByte(READY);
	for (uint8 i = 0; i < 5; i++)
	{
		while (uart_recieveByte() != READY){};
		uart_sendByte(new_password[i]);
	}


	while (1)
	{
		/* select an option */
		while (clear != 0) {}; LCD_displayString("select an option");
		uint8 option = KeyPad_getPressedKey();
		LCD_clearScreen();

		/* option(-) open door */
		if (option == '-') //open door
		{
			uint8 success = 0;
			uint8 tries = 0;
			do
			{
				/* get password from user*/
				LCD_displayString("enter the pass: ");
				get_password(new_password);

				/* send the password using UART */
				uart_sendByte(READY);
				uart_sendByte('-');
				for (uint8 i = 0; i < 5; i++)
				{
					while (uart_recieveByte() != READY){};
					uart_sendByte(new_password[i]);
				}

				/* receive the result from MC2 (matching or dis_matching) */
				//while (uart_recieveByte() != READY){};
				uart_sendByte(READY);  // matching
				if (uart_recieveByte() == MATCHING)
				{
					/*LCD_displayString("door unlocking");
					_delay_ms(1000);
					LCD_clearScreen();
					LCD_displayString("door locking");
					_delay_ms(1000);
					LCD_clearScreen();
					success = 1;*/

						Timer1_set_CallBack(LCD_clear);
						LCD_displayString("door unlocking");
						clear = 1;
						//Timer1_init(8000);
						Timer1_config timer_config = {F_CPU_1024, 0, 8000};
						Timer1_init(&timer_config);
						while(clear == 1) {};
						LCD_displayString("door locking");
						clear = 1;
						//Timer1_init(8000);
						Timer1_init(&timer_config);
						success = 1;

				}
				else  // dis_matching
				{
					LCD_displayString("dis_matching");
					_delay_ms(100);
					LCD_clearScreen();
					success = 0;
					tries ++;
				}

			}while(!(success) && tries != 3);

			if (tries == 3)
			{
				Timer1_set_CallBack(LCD_clear);
				LCD_displayString("THIEF");
				uart_sendByte(READY);
				uart_sendByte(THEIF);
				clear = 1;
				//Timer1_init(65000);
				Timer1_config timer_config = {F_CPU_1024, 0, 65000};
				Timer1_init(&timer_config);
				//_delay_ms(100);
				//LCD_clearScreen();
			}

		}


		/* option(+) change password*/
		else if (option == '+') //change password
		{
			uint8 success = 0;
			uint8 tries = 0;
			do
			{
				/* get password from user*/
				LCD_displayString("enter the pass: ");
				get_password(new_password);

				/* send the password using UART */
				uart_sendByte(READY);
				uart_sendByte('+');
				for (uint8 i = 0; i < 5; i++)
				{
					while (uart_recieveByte() != READY){};
					uart_sendByte(new_password[i]);
				}

				/* receive the result from MC2 (matching or dis_matching) */
				//while (uart_recieveByte() != READY){};
				uart_sendByte(READY);  // matching
				if (uart_recieveByte() == MATCHING)
				{
					LCD_displayString("matching");
					_delay_ms(100);
					LCD_clearScreen();
					success = 1;
					do
					{
						LCD_displayString("enter new pass: ");
						get_password(new_password);
						LCD_displayString("re_enter new pass: ");
						get_password(re_new_password);
						compare = cmp (new_password, re_new_password);
					}
					while (!compare);


					/* send the new password using uart to the MC2 */
					uart_sendByte(READY);
					for (uint8 i = 0; i < 5; i++)
					{
						while (uart_recieveByte() != READY){};
						uart_sendByte(new_password[i]);
					}

				}
				else  // dis_matching
				{
					LCD_displayString("dis_matching");
					_delay_ms(100);
					LCD_clearScreen();
					success = 0;
					tries ++;
				}

			}while(!(success) && tries != 3);

			if (tries == 3)
			{
				Timer1_set_CallBack(LCD_clear);
				LCD_displayString("THIEF");
				uart_sendByte(READY);
				uart_sendByte(THEIF);
				clear = 1;
				//Timer1_init(65000); // 1 second*/
				Timer1_config timer_config = {F_CPU_1024, 0, 8000};
				Timer1_init(&timer_config);
				/*_delay_ms(100);
				LCD_clearScreen();*/
			}

		}
	}
}
