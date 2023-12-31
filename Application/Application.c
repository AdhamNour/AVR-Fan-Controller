/*
 * Application.c
 *
 *  Created on: Oct 21, 2023
 *      Author: adham
 */

#include "Application.h"

#include <util/delay.h>
#include <stdlib.h>
#include <string.h>

#include "../HAL/DC_Motor/DC_Motor.h"
#include "../HAL/LCD/LCD.h"
#include "../HAL/LM35/LM35.h"

static void Application_init();
static void Application_splashScreen();
static void Application_readTempreture();
static void Application_printTempreture();
static void Application_setFanStatus();
static void Application_cotrolTheFan();

static uint8 current_temp = 0;
static uint8 tempreature_string[3];
static uint8 displayString[16];
static DCMotor_State dcMotorState = OFF;
static uint8 dcMotorSpead = 0;

void Application_Setup() {
	static uint8 tempString[] = "Temp =     C";
	static uint8 fanString[] = "Fan is OFF";
	Application_init();
	Application_splashScreen();
	LCD_displayStringRowColumn(0, 3, fanString);

	LCD_displayStringRowColumn(1, 2, tempString);

}

void Application_Loop() {
	Application_readTempreture();
	Application_printTempreture();
	Application_setFanStatus();
	Application_cotrolTheFan();

}

static void Application_init() {
	LCD_init();
	DcMotor_Init();
	LM35_init();
}

static void Application_splashScreen() {
	LCD_displayString("Welcome to ur ");
	LCD_displayStringRowColumn(1, 0, "Fan Controller");

	_delay_ms(500);
	LCD_clearScreen();
	LCD_displayString("The Fan Will");
	LCD_displayStringRowColumn(1, 0, "follow the temp");
	_delay_ms(500);

	LCD_clearScreen();
}

static void Application_readTempreture() {
	current_temp = LM35_readTemp();

}
static void Application_printTempreture() {
	itoa(current_temp, tempreature_string, 10);
	LCD_displayStringRowColumn(1, 9, tempreature_string);
	LCD_displayString("  ");
}

static void Application_cotrolTheFan() {
	LCD_displayStringRowColumn(0, 10, dcMotorState==OFF?"OFF":"ON ");
	DcMotor_Rotate(dcMotorState, dcMotorSpead);
}

static void Application_setFanStatus() {
	if (current_temp < 30) {
		dcMotorSpead=0;
		dcMotorState=OFF;
	} else if (current_temp >= 30 && current_temp < 60) {
		dcMotorSpead=25;
		dcMotorState=CW;
	}

	else if (current_temp >= 60 && current_temp < 90) {
		dcMotorSpead=50;
				dcMotorState=CW;

	} else if (current_temp >= 90 && current_temp < 120) {
		dcMotorSpead=75;
				dcMotorState=CW;

	} else if (current_temp >= 120) {
		dcMotorSpead=100;
				dcMotorState=CW;

	} else {
		LCD_displayStringRowColumn(0, 10, "err");

	}
}
