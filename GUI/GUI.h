/*
 * GUI.h
 *
 *  Created on: 4 avr. 2015
 *      Author: Gabriel
 */

#ifndef GUI_H_
#define GUI_H_

#include "Widget.h"
#include <stddef.h>

#define parse_widget(type, name) type* name; unsigned int nb_##name


#define parse_config(structname, nameparam, nbchild)\
	structname.nb_##nameparam = nbchild

typedef struct GUI {
	list_widget* roots;
	Widget* current_root;
} GUI;

void GUI_init();

GUI* GUI_create();

void GUI_draw(GUI* gui);
void GUI_run(GUI* gui);

void GUI_destroy(GUI* gui);

void GUI_add_root(GUI* gui, Widget* root);
void GUI_select_root(GUI* gui, unsigned int index);

void GUI_parse(Widget* root, void* parsing_structure);

#endif /* GUI_H_ */
