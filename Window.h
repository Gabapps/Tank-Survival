/**
 * @file Window.h
 * @author Ethel Marquer, Gabriel Lucas, Nicolas Kaczmarek, Maxime Peralta
 * @date 1 March 2015
 * @brief The global Window module contains some functions to manipulate windows
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

/**
 * \fn int window_open()
 * \brief Initialize and open the window
 *
 * \return -1 if something went wrong, 0 otherwise
 */
int window_open();

/**
 * \fn int window_close()
 * \brief Close a window
 */
void window_close();

/**
 * \fn float window_get_ratio()
 * \brief Return the window's width/height ratio
 *
 * \return The window's width/height ratio
 */
float window_get_ratio();

/**
 * \fn float GLFWwindow* window_get()
 * \brief Return a pointer to the window
 *
 * \return A pointer to the window
 */
GLFWwindow* window_get();

#endif /* WINDOW_H_ */
