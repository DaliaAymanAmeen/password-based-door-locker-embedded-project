/*
 * main.c
 *
 *  Created on: Oct 6, 2020
 *      Author: user
 */

#include "uart.h"
#include "eeprom.h"
#include "motor.h"
#include "helper_functions.h"
#include "timer.h"
#define READY 0x10
#define MATCHING 0x20
#define DISMATCHING 0x30
#define THEIF 0x40

int main(void)
{
	SREG |= (1 << 7); // I_bit
	//DDRA |= 0xFF; // LEDS for testing
	//PORTA = 0; // LEDS for testing
	DDRC |= (1 << 7);  // output pin for BUZZER
	PORTC &= ~(1 << 7); //  initial value = 0

	UART_config config = {BIT_8, DISABLE, STOP_BIT_1};   // 8_bit frame, parity disabled, 1 stop bit
	uart_init(&config);
	EEPROM_init();

	uint8 compare;
	uint8 read_password; // data read from EEPRM
	uint8 read_password_arr[5];
	uint8 password[5]; // the received password using UART

	/* receive the new password and store(write) it in the EEPRM */
	while (uart_recieveByte() != READY){};
	for (uint8 i = 0; i < 5 ; i++)
	{
		uart_sendByte(READY);
		password[i] = uart_recieveByte();
		EEPROM_writeByte((0x000 | i), password[i]);
		_delay_ms(10);
	}

// testing
/*
	for (uint8 i = 0; i < 5; i++)
	{
		EEPROM_readByte((0x000 | i), &read_new_password);
		PORTA = read_new_password;
		_delay_ms(500);
	}
*/
	while(1)
	{
		/* receive option(-) open door, check the password */
		while (uart_recieveByte() != READY){};  // receiving READY from UART every action/option
		//PORTA = 0xFF;

		uint8 data_recieved = uart_recieveByte();  // data_recieved:(option) = (-) or (+)  // in case of thief (data_recieved = "THIEF" )
		if (data_recieved == '-')
		{
			//PORTA = 10;
			for (uint8 i = 0; i < 5 ; i++) // receiving the password
			{
				uart_sendByte(READY);
				password[i] = uart_recieveByte();
			}

			for (uint8 i = 0; i < 5 ; i++)  // read the existing password from EEPROM
			{
				EEPROM_readByte((0x000 | i), &read_password);
				read_password_arr[i] = read_password;
			}
			compare = cmp (password, read_password_arr);  // compare the 2 passwords

			if (compare) //matching
			{
				while(uart_recieveByte() != READY){}
				//uart_sendByte(READY);
				uart_sendByte(MATCHING);
				//PORTA = 0xFF;
				motor_on_clk_wise();
				Timer1_set_CallBack(CB_reverse_motor);
				//Timer1_init(8000);  // 1 second
				Timer1_config timer_config = {F_CPU_1024, 0, 8000};
				Timer1_init(&timer_config);  // 1 second*/

				/*_delay_ms(1000);
				motor_on_anti_clk_wise();
				_delay_ms(1000);
				motor_off();*/
				//PORTA = 0;
			}
			else // dis_matching
			{
				while(uart_recieveByte() != READY){};
				//uart_sendByte(READY);
				uart_sendByte(DISMATCHING);
				//PORTA = 10;
				//motor_off();
				//_delay_ms(100);
			}
		}

		/* receive option(+) change password, check the password */
		else if (data_recieved == '+')
		{

			for (uint8 i = 0; i < 5 ; i++) // receiving the password
			{
				uart_sendByte(READY);
				password[i] = uart_recieveByte();
			}

			for (uint8 i = 0; i < 5 ; i++)  // read the existing password from EEPROM
			{
					EEPROM_readByte((0x000 | i), &read_password);
					read_password_arr[i] = read_password;
			}
			compare = cmp (password, read_password_arr);  // compare the 2 passwords

			if (compare) //matching
			{
				while(uart_recieveByte() != READY){}
				uart_sendByte(MATCHING);
				//PORTA = 0xFF;
				//_delay_ms(100);
				//PORTA = 0;
				/* receive the new password and store(write) it in the EEPRM */
				while (uart_recieveByte() != READY){};
				for (uint8 i = 0; i < 5 ; i++)
				{
					uart_sendByte(READY);
					password[i] = uart_recieveByte();
					EEPROM_writeByte((0x000 | i), password[i]);
					_delay_ms(10);
				}
			}
			else // dis_matching
			{
					while(uart_recieveByte() != READY){};
					//uart_sendByte(READY);
					uart_sendByte(DISMATCHING);
					//PORTA = 10;
					//motor_off();
					//_delay_ms(100);
			}
		}

		/* buzzer */
		else
		{
			/*PORTC |= (1 << 7);
			_delay_ms(100);
			PORTC &= ~(1 << 7);*/
			Timer1_set_CallBack(Buzzer_on);
			PORTC |= (1 << 7);
			Timer1_config timer_config = {F_CPU_1024, 0 , 65000};
			Timer1_init(&timer_config);  // 1 second*/
		}

	}
}
