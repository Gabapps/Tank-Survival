/*
 * Window.c
 *
 *  Created on: 7 mars 2015
 *      Author: max
 */


#include "Window.h"


int window_open()
{
	if(!glfwInit()) {
			fprintf(stderr, "Failed to initialize GLFW.\n");
			return -1;
		}

	(Window.window) = glfwCreateWindow(1024, 768, "Tank Survival", NULL, NULL);
	(Window.height) = 768;
	(Window.width) = 1024;
	if(Window.window == NULL){
	    fprintf(stderr, "Failed to open GLFW window.\n" );
	    glfwTerminate();
	    return -1;
	}

	return 0;
}


void window_close() {
    glfwSetWindowShouldClose(Window.window, GL_TRUE);
}

float window_get_ratio()
{
	return ((float)Window.width / (float)Window.height);
}

GLFWwindow* window_get() {
	return Window.window;
}
