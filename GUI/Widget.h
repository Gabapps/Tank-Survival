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
#include "../Math.h"

typedef enum {VISIBLE, INVISBLE} Visibility;

#define define_widget(type) \
	list_widget *childs; \
	void (*setup) (struct type *widget); \
	void (*draw) (struct type *widget); \
	Visibility visibility; \
	vec2 position; \
	vec2 size; \
	float angleY

typedef struct Widget Widget;

typelist(widget, Widget);

struct Widget {
	define_widget(Widget);
};

void widget_init(Widget* widget);

void widget_add_child(Widget* parent, Widget* child);

void widget_init(Widget* widget, void* setup_fct, void *draw_fct) {
	widget->visibility = VISIBLE;
	widget->childs = list_widget_create();
	widget->angleY = 0;
	widget->setup = setup_fct;
	widget->draw = draw_fct;
	vec2_zero(widget->position);
	vec2_create(widget->size, 0.1, 0.1);
}

#endif /* WIDGET_H_ */
