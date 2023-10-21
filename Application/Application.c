/*
 * Application.c
 *
 *  Created on: Oct 21, 2023
 *      Author: adham
 */

#include "Application.h"

#include <util/delay.h>
#include <stdlib.h>

#include "../HAL/DC_Motor/DC_Motor.h"
#include "../HAL/LCD/LCD.h"
#include "../HAL/LM35/LM35.h"

static void Application_init();
static void Application_splashScreen();

void Application_Setup() {
	Application_init();
	Application_splashScreen();

}

void Application_Loop() {
	LCD_clearScreen();
	uint8 x = LM35_readTemp();
	uint8 a[16];
	itoa(x, a, 10);
	LCD_displayString(a);
	_delay_ms(1000);
}

static void Application_init(){
	LCD_init();
	DcMotor_Init();
	LM35_init();
}

static void Application_splashScreen(){
	LCD_displayString("Welcome to ur ");
	LCD_displayStringRowColumn(1,0,"Fan Controller");

	_delay_ms(500);
	LCD_clearScreen();
	LCD_displayString("The Fan Will");
	LCD_displayStringRowColumn(1,0,"follow the temp");
	_delay_ms(500);

	LCD_clearScreen();
}
