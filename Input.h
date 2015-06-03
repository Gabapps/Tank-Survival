/*
* Input.h
*
* Created on: 1 mars 2015
* Author: Gabriel
*/

#ifndef INPUT_H_
#define INPUT_H_

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "Window.h"
#include "Controls.h"

/**
 * \fn void input_update();
 * \brief Check if the useful keys are pressed or not and update the Controls structure
 */
void input_update();

// void input_set_controls();

/**
 * \fn Controls* input_get_controls(char* nom_control)
 * \brief Check the status of the key from its name in the Controls structure
 *
 * \param nom_control The name of the key
 *
 * \return The status of the key
 */
Controls* input_get_controls(char* nom_control);


/**
 * \fn Controls* input_get_controls_index(int key_number)
 * \brief Check the status of the key from its index number in the Controls structure
 *
 * \param key_number The index number of the key
 *
 * \return The status of the key
 */
Controls* input_get_controls_index(int key_number);


/**
 * \fn int input_keypressed(char* nom_control)
 * \brief Return true if the key is pressed (depend of the previous input_update)
 *
 * \param nom_control The name of the key
 *
 * \return true if the key is pressed
 */
int input_keypressed(char* nom_control);


/**
 * \fn int input_keypressed(char*)
 * \brief Return true if the key is pressed (depend of the previous input_update)
 *
 * \param key The index number of the key
 *
 * \return true if the key is pressed
 */
int input_keypressed_index(int key);


#endif /* INPUT_H_ */
