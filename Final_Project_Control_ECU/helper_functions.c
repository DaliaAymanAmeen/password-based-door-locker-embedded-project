/*
 * helper_functions.c
 *
 *  Created on: Oct 6, 2020
 *      Author: user
 */

#include "helper_functions.h"
#include "motor.h"
#include "timer.h"

uint8 cmp (uint8 password_1[], uint8 password_2[])
{
	for(uint8 i = 0; i < 5; i++)
	{
		if (password_1[i] != password_2[i]) return 0;
	}

	return 1;
}

/* CallBack Functions */

void Buzzer_on(void)
{
	PORTC &= ~(1 << 7);
	SREG &= ~(1 << 7); // I_bit
}

void CB_motor_off(void)
{
	motor_off();
}

void CB_reverse_motor(void)
{
	motor_on_anti_clk_wise();
	Timer1_set_CallBack(CB_motor_off);
	Timer1_config timer_config = {F_CPU_1024, 0 , 8000};
	Timer1_init(&timer_config);  // 1 second*/
	//Timer1_init(8000);
}


