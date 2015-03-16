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

/*
typedef struct Input_s{
Controls_s* controls;
int count_countrols;
}Input_s;
 */
void input_update();
void input_set_controls();

/*
Controls_s* input_get_controls(char*);
Controls_s* input_get_controls_index(int);
 */
int input_keypressed(char*);
int input_keypressed_index(int);
/*
int input_keypressed_index(int, int);
 */

#endif /* INPUT_H_ */
