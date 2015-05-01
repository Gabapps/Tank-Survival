/*
 * Widget.c
 *
 *  Created on: 20 avr. 2015
 *      Author: Gabriel
 */

#include "Widget.h"

void widget_init(Widget* widget, void* setup_fct, void *draw_fct) {
	widget->visibility = VISIBLE;
	widget->children = list_widget_create();
	widget->angleY = 0;
	widget->setup = setup_fct;
	widget->draw = draw_fct;
	vec2_zero(widget->position);
	vec2_create(widget->size, 0.1, 0.1);
	mat4x4_identity(widget->matrix);
}

void widget_add_child(Widget* parent, Widget* child) {
	list_widget_put(parent->children, child);
}

void widget_refresh_matrix(Widget* widget) {
	mat4x4_identity(widget->matrix);
	mat4x4_translate(widget->matrix, widget->position[0], widget->position[1], 0);
	mat4x4_scale_aniso(widget->matrix, widget->matrix, widget->size[0], widget->size[1], 0);
}

void widget_resize(Widget* widget, float x, float y) {
	if(x==0 && y>0) {
		float a = y/widget->size[1];
		widget->size[0]*=a;
		widget->size[1]=y;
	}
	else if(y==0 && x>0) {
		float a = x/widget->size[0];
		widget->size[0]=x;
		widget->size[1]*=a;
	}
	else if(x>0 && y>0) {
		widget->size[0]=x;
		widget->size[1]=y;
	}
}

void widget_set_position(Widget* widget, float x, float y) {
	widget->position[0]=x;
	widget->position[1]=y;
}
