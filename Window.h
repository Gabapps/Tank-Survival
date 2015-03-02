/*
 * Window.h
 *
 *  Created on: 1 mars 2015
 *      Author: Gabriel
 */

#ifndef WINDOW_H_
#define WINDOW_H_

#include <GLFW/glfw3.h>

typedef struct{
	int height;
	int width;
	GLFWwindow* window;
}Window_s;

extern Window_s Window;

int window_open();
float window_get_ratio();

#endif /* WINDOW_H_ */
