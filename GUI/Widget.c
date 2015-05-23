/*
 * Widget.c
 *
 *  Created on: 20 avr. 2015
 *      Author: Gabriel
 */

#include "Widget.h"

void widgets_init() {
	mat4x4_ortho(ortho, -window_get_ratio(), window_get_ratio(), -1, 1, 0, 3);
}

void widget_init(Widget* widget, void* run_fct, void *draw_fct) {
	widget->visibility = VISIBLE;
	widget->children = list_widget_create();
	widget->parent = NULL;
	widget->angleY = 0;
	widget->run = run_fct;
	widget->draw = draw_fct;
	vec2_zero(widget->position);
	vec2_create(widget->size, 0.1, 0.1);
	mat4x4_identity(widget->matrix);
	mat4x4_identity(widget->childmatrix);
}

void widget_destroy(Widget* widget) {
	free(widget);
}

void widget_add_child(Widget* parent, Widget* child) {
	list_widget_put(parent->children, child);
	child->parent = parent;
}

void widget_refresh_matrix(Widget* widget) {
	mat4x4_identity(widget->childmatrix);
	mat4x4_translate(widget->childmatrix, widget->position[0], widget->position[1], 0);
	mat4x4_scale_aniso(widget->matrix, widget->childmatrix, widget->size[0], widget->size[1], 0);
	if(widget->parent) mat4x4_mul(widget->matrix, widget->parent->childmatrix, widget->matrix);
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
	else if(x<0 && y>0) {
		widget->size[1]=y;
	}
	else if(x>0 && y<0) {
		widget->size[0]=x;
	}
}

void widget_set_position(Widget* widget, float x, float y) {
	widget->position[0]=x;
	widget->position[1]=y;
}

void widget_set_shader_gui(int shader_gui_id) {
	shader_gui = shader_gui_id;
}
