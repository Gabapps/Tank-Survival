/*
 * Window.c
 *
 *  Created on: 7 mars 2015
 *      Author: max
 */


#include "Window.h"

const int height = 1080, width = 1920, fullscreen = 1;

int window_open()
{
	if(!glfwInit()) {
			fprintf(stderr, "Failed to initialize GLFW.\n");
			return -1;
		}

	const GLFWvidmode * mode = glfwGetVideoMode(glfwGetPrimaryMonitor());

	(Window.height) = mode->height;
	(Window.width) = mode->width;
	(Window.window) = glfwCreateWindow(Window.width, Window.height, "Tank Survival", (fullscreen ? glfwGetPrimaryMonitor() : NULL), NULL);

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
