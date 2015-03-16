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

void init_controlsTable();
int controls_create(char* action_name, int key_number);
int controls_destroy(char* control_name);

#endif /* CONTROLS_H_ */
