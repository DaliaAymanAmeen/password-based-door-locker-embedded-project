/*
 * motor.h
 *
 *  Created on: Sep 22, 2020
 *      Author: user
 */

#ifndef MOTOR_H_
#define MOTOR_H_

#include "util/delay.h"
#include "std_types.h"
#include "micro_config.h"
#include "common_macros.h"

void motor_on_clk_wise(void);
void motor_on_anti_clk_wise(void);
void motor_off(void);

#endif /* MOTOR_H_ */
