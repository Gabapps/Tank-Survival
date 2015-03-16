/*
 * Window.h
 *
 *  Created on: 1 mars 2015
 *      Author: Gabriel
 */

#ifndef WINDOW_H_
#define WINDOW_H_

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <stdio.h>
#include <stdlib.h>



typedef struct Window_s{
	int height;
	int width;
	GLFWwindow* window;
}Window_s;

Window_s Window;

int window_open();
float window_get_ratio();
GLFWwindow* window_get();

#endif /* WINDOW_H_ */
