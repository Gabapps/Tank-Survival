/*
 * RelativeLayout.h
 *
 *  Created on: 3 mai 2015
 *      Author: Gabriel
 */

#ifndef GUI_RELATIVELAYOUT_H_
#define GUI_RELATIVELAYOUT_H_

#include "Widget.h"
#include "../Window.h"

typedef struct RelativeLayout {
	define_widget(RelativeLayout);
} RelativeLayout;

RelativeLayout* layout_rel_create();


void layout_rel_add_child(RelativeLayout* parent, Widget* child, float x, float y);

#endif /* GUI_RELATIVELAYOUT_H_ */
