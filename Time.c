/*
 * Time.c
 *
 *  Created on: 17 mars 2015
 *      Author: Gabriel
 */

#include "Time.h"

void time_init() {
	Time.deltaTime = 0;
	Time.timeSinceStart = 0;
}

void time_update() {
	Time.deltaTime = (float)(glfwGetTime()-Time.timeSinceStart);
	Time.timeSinceStart = glfwGetTime();
}
