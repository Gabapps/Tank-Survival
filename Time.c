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
	Time.maxfps = 40;
}
#ifdef WIN32
#include <windows.h>
#endif
void time_update() {
	Time.deltaTime = (float)(glfwGetTime()-Time.timeSinceStart);
	Time.timeSinceStart = glfwGetTime();

	//Limit the framerate to maxfps
	float sleeptime = (1/(float)Time.maxfps) - Time.deltaTime;
	if(sleeptime>=0.001) {
		#ifdef WIN32
		Sleep((int)(sleeptime*1000));
		Time.deltaTime += (float)(glfwGetTime()-Time.timeSinceStart);
		#endif
	}
}
