/*
 * Pwm.c
 *
 *  Created on: 8 mar 2019
 *      Author: Student241580
 */

#include"Pwm.h"
const char temp1text [] PROGMEM = "Temp1:";
const char error[] PROGMEM="Awaria czujnika";
const char temp2text [] PROGMEM = " Temp2";
const char fanpowertext [] PROGMEM ="Moc wiatraka: " ;





void Pwm_init(void){
	DDRB |= (1<<PB3);					//Seting OC2 as an output
	TCCR2 |= (1<<WGM21)|(1<<WGM20);		// FastPwm selected
	TCCR2 |= (1<<COM21);				// Setting OC2 after overflow of TCNT2
	TCCR2 |= (1<<CS22);					// prescaler = 64
	OCR2=0;							// conts 0 as defalute value at output
}
void Display(){
	int power;
	char buf[3];
	LCD_Clear();
	LCD_WriteText_P(temp1text);
	LCD_WriteText(itoa(temp1,buf,10));
	LCD_WriteText_P(temp2text);
	LCD_WriteText(itoa(temp2,buf,10));
	LCD_GoTo(0,1);
	LCD_WriteText_P(fanpowertext);
	power=OCR2;
	power *=100;
	power =power/255;
	LCD_WriteText(itoa(power,buf,10));
	LCD_WriteText("%");


}
void ask_sensors(void){
	DS18X20_start_meas(DS18X20_POWER_PARASITE,NULL);
_delay_ms(750);
if(!(DS18X20_OK==DS18X20_read_meas(gSensorIDs[0],&sign,&temp1,&temp1_fraction)))
	LCD_WriteText_P(error);
if(!(DS18X20_OK==DS18X20_read_meas(gSensorIDs[1],&sign,&temp2,&temp2_fraction)))
	LCD_WriteText_P(error);
}
void fan_control(void){
//********************************************************
	//factorization to format (XX,X)*10
	int diff=temp1-temp2;
	int diff_fraction=temp1_fraction-temp2_fraction;

	diff_fraction &=(1<<0);
	diff *=10;
	diff +=diff_fraction;
//********************************************************
	//low-pass filter
	static int diffsr;
diffsr=(5*diffsr+diff)/6;
//********************************************************
	if(diffsr>50)
		OCR2=255;
	else if(diffsr>45)
			OCR2=220;
	else if(diffsr>40)
			OCR2=200;
	else if(diffsr>35)
			OCR2=170;
	else if(diffsr>30)
			OCR2=150;
	else if(diffsr>25)
			OCR2=130;
	else if(diffsr>20)
			OCR2=100;
	else if(diffsr>15)
			OCR2=100;
	else if(diffsr>10)
			OCR2=0;
}
