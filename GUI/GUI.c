/*
 * GUI.c
 *
 *  Created on: 3 mai 2015
 *      Author: Gabriel
 */

#include "GUI.h"

void GUI_init() {
	mesh_load_canvas();
	widgets_init();
}

GUI* GUI_create() {
	GUI* gui = (GUI*)malloc(sizeof(GUI));
	gui->current_root = NULL;
	gui->roots = list_widget_create();
	return gui;
}

void GUI_draw_rec(Widget* widget) {
	if(widget->children->root == NULL) {
		widget_refresh_matrix(widget);
		if(widget->draw) widget->draw(widget);
	}
	else {
		widget_refresh_matrix(widget);
		if(widget->draw) widget->draw(widget);
		node_widget *iterator = widget->children->root;
		while(iterator != NULL) {
			GUI_draw_rec(iterator->value);
			iterator = iterator->next;
		}
	}
}

void GUI_draw(GUI* gui) {
	GUI_draw_rec(gui->current_root);
}

void GUI_run_rec(Widget* widget) {
	if(widget->children->root == NULL) {
		if(widget->run) widget->run(widget);
	}
	else {
		if(widget->run) widget->run(widget);
		node_widget *iterator = widget->children->root;
		while(iterator != NULL) {
			GUI_run_rec(iterator->value);
			iterator = iterator->next;
		}
	}
}


void GUI_run(GUI* gui) {
	GUI_run_rec(gui->current_root);
}

void GUI_destroy_rec(Widget* widget) {
	if(widget->children->root == NULL) {
		widget_destroy(widget);
	}
	else {
		node_widget *iterator = widget->children->root;
		while(iterator != NULL) {
			GUI_destroy_rec(iterator->value);
			iterator = iterator->next;
		}
		widget_destroy(widget);
	}
}

void GUI_destroy(GUI* gui) {
	node_widget* iterator = gui->roots->root;
	while(iterator != NULL) {
		GUI_destroy_rec(iterator->value);
		iterator = iterator->next;
	}
}

void* move_ptr(void** ptr, size_t size) {
	void* temp = *ptr;
	*ptr+=size;
	return temp;
}

void GUI_parse_rec(Widget* parent, Widget* current, int nbchildren, void* parsing_structure) {
	if(nbchildren == 0) {
		if(parent) {
			widget_add_child(parent, current);
		}
	}
	else {

		if(parent && parent != current) {
			widget_add_child(parent, current);
		}

		int i;
		for(i=0; i<nbchildren; i++) {
			Widget** child = (Widget**)parsing_structure;
			parsing_structure+= sizeof(Widget*);
			unsigned int *newnbchildren = (unsigned int*)parsing_structure;
			parsing_structure+= sizeof(unsigned int);

			GUI_parse_rec(current, *child, *newnbchildren, parsing_structure);

			free(newnbchildren);
		}
	}
}

void GUI_parse(Widget* root, void* parsing_structure) {
	GUI_parse_rec(NULL, root, 1, parsing_structure);
}

void GUI_add_root(GUI* gui, Widget* root) {
	list_widget_put(gui->roots, root);
	if(gui->roots->count == 1) gui->current_root = root;
}

void GUI_select_root(GUI* gui, unsigned int index) {
	if(gui->roots->count<= index) return;
	node_widget* iterator = gui->roots->root;
	while(iterator != NULL) {
		if(!index) {
			gui->current_root = iterator->value;
			return;
		}
		index--;
		iterator = iterator->next;
	}
}
