/*
 * Pwm.h
 *
 *  Created on: 8 mar 2019
 *      Author: Student241580
 */

#ifndef PWM_PWM_H_
#define PWM_PWM_H_
#include <stdlib.h>
#include "../1wire/ds18x20.h"
#include "../Lcd/HD44780.h"
#include <avr/pgmspace.h>
#include <avr/eeprom.h>
#include <util/delay.h>

extern const char temp1text [] PROGMEM;
extern const char error[] PROGMEM;
extern const char temp2text [] PROGMEM ;
extern const char fanpowertext [] PROGMEM ;

uint8_t sensors;
uint8_t temp1,temp1_fraction,temp2,temp2_fraction,sign;

void fan_control(void);
void Pwm_init(void);
void Display();
void ask_sensors(void);


#endif /* PWM_PWM_H_ */
