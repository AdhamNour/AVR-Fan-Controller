/*
 * main.c
 *
 *  Created on: Oct 12, 2023
 *      Author: adham
 */

#include "Application/Application.h"


int main(void) {
	Application_Setup();
	while (1) {
		Application_Loop();
	}
}
