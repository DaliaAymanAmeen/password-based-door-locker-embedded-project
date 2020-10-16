/*
 * motor.c
 *
 *  Created on: Sep 22, 2020
 *      Author: user
 */

#include "motor.h"

void motor_on_clk_wise(void)
{
	DDRB |= (1 << PB4) | (1 << PB5); // 2 output pins
	// clk wise
	PORTB |= (1 << PB4);
	PORTB &= ~(1 << PB5);

}

void motor_on_anti_clk_wise(void)
{
	DDRB |= (1 << PB4) | (1 << PB5); // 2 output pins
	// clk wise
	PORTB &= ~(1 << PB4);
	PORTB |= (1 << PB5);

}
void motor_off(void)
{
	DDRB |= (1 << PB4) | (1 << PB5); // 2 output pins
	// clk wise
	PORTB &= ~(1 << PB4);
	PORTB &= ~(1 << PB5);

}
