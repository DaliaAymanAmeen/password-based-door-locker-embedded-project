/*
 * helper_functions.h
 *
 *  Created on: Oct 6, 2020
 *      Author: user
 */

#ifndef HELPER_FUNCTIONS_H_
#define HELPER_FUNCTIONS_H_

#include "std_types.h"
#include "micro_config.h"
#include "common_macros.h"

/* function to compare 2 passwords*/
uint8 cmp (uint8 password_1[], uint8 password_2[]);

void Buzzer_on(void);
void CB_motor_off(void);
void CB_reverse_motor(void);


#endif /* HELPER_FUNCTIONS_H_ */

