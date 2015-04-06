/*
 * Widget.h
 *
 *  Created on: 4 avr. 2015
 *      Author: Gabriel
 */

#ifndef WIDGET_H_
#define WIDGET_H_

#include "List.h"

#define define_widget(type) \
	list_widget *childs; \
	void *(setup) (type *widget); \
	void *(draw) (type *widget) \

typedef Widget Widget;

typelist(widget, Widget);

struct Widget {
	define_widget(Widget);
};

void widget_add_child(Widget* parent, Widget* child);

#endif /* WIDGET_H_ */
