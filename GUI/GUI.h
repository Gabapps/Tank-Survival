/*
 * GUI.h
 *
 *  Created on: 4 avr. 2015
 *      Author: Gabriel
 */

#ifndef GUI_H_
#define GUI_H_

#include "Widget.h"

typedef struct GUI_s {
	Widget* root;
} GUI_s;

GUI_s GUI;

void GUI_init();
void GUI_draw();

void GUI_init() {
	mesh_load_canvas();
}

#endif /* GUI_H_ */
