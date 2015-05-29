/*
 * Time.h
 *
 *  Created on: 17 mars 2015
 *      Author: Gabriel
 */

#ifndef TIME_H_
#define TIME_H_

#include <GL/glew.h>
#include <GLFW/glfw3.h>

typedef struct Time_s {
	double timeSinceStart;
	float deltaTime;
	int maxfps;
} Time_s;

Time_s Time;

//Initialize the time module
void time_init();

//Update the time module
void time_update();

#endif /* TIME_H_ */
