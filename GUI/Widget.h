/*
 * Widget.h
 *
 *  Created on: 4 avr. 2015
 *      Author: Gabriel
 */

#ifndef WIDGET_H_
#define WIDGET_H_

#define GLEW_STATIC
#include <GL/glew.h>

#include "../List.h"
#include "../Mesh.h"
#include "../Shader.h"
#include "../Math.h"
#include "../Window.h"

#define RESIZE_LINEAR 0
#define RESIZE_NONLINEAR -1

typedef enum {VISIBLE, INVISBLE} Visibility;

int shader_gui;
mat4x4 ortho;

#define define_widget(type) \
	list_widget *children; \
	struct Widget* parent; \
	void (*run) (struct type *widget); \
	void (*draw) (struct type *widget); \
	Visibility visibility; \
	vec2 position; \
	vec2 size; \
	float angleY; \
	mat4x4 matrix; \
	mat4x4 childmatrix

typedef struct Widget Widget;

typelist(widget, Widget*);

struct Widget {
	define_widget(Widget);
};

void widgets_init();

void widget_init(Widget* widget, void* setup_fct, void *draw_fct);

void widget_destroy(Widget* widget);

void widget_add_child(Widget* parent, Widget* child);

void widget_refresh_matrix(Widget* widget);

void widget_resize(Widget* widget, float x, float y);

void widget_set_position(Widget* widget, float x, float y);

void widget_set_shader_gui(int shader_gui_id);

#endif /* WIDGET_H_ */
