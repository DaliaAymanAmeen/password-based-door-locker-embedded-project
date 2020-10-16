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

extern uint8 clear;
/* function to get password from the user */
void get_password(uint8 password[]);

/* function to compare 2 passwords*/
uint8 cmp (uint8 password_1[], uint8 password_2[]);
void LCD_clear(void);

#endif /* HELPER_FUNCTIONS_H_ */
