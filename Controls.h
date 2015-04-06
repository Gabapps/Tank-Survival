/*
 * Controls.h
 *
 *  Created on: 1 mars 2015
 *      Author: Gabriel
 */

#ifndef CONTROLS_H_
#define CONTROLS_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct{
	char* action_name;
	int key_number;
	int key_state;
} Controls;

/**
 * \fn void init_controlsTable();
 * \brief Allocate the Controls structure
 */
void init_controlsTable();

/**
 * \fn int controls_create(char* action_name, int key_number);
 * \brief Create a control by giving a key number. Then the control is known as the action_name give as parameter.
 *
 * \param action_name The name of the key
 * \param key_number The index number of the key
 *
 * return 0 when there is not any problems
 */
int controls_create(char* action_name, int key_number);

/**
 * \fn int controls_destroy(char* control_name);
 * \brief Destroy a control from its action_name give as parameter.
 *
 * \param action_name The name of the key
 *
 * return 0 when there is not any problems
 */
int controls_destroy(char* control_name);

#endif /* CONTROLS_H_ */
