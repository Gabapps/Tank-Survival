/**
 * @file Time.h
 * @author Ethel Marquer, Gabriel Lucas, Nicolas Kaczmarek, Maxime Peralta
 * @date 6 Apr 2015
 * @brief An useful structure for scaling the game speed with the time
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
