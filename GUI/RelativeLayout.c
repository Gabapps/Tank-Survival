/*
 * RelativeLayout.c
 *
 *  Created on: 3 mai 2015
 *      Author: Gabriel
 */

#include "RelativeLayout.h"

RelativeLayout* layout_rel_create() {
	RelativeLayout* img = (RelativeLayout*)malloc(sizeof(RelativeLayout));
	widget_init((Widget*)img, NULL, NULL);
	widget_resize((Widget*)img, 1, 1);
	return img;
}


void layout_rel_add_child(RelativeLayout* parent, Widget* child, float x, float y) {
	widget_add_child((Widget*)parent, child);
	widget_set_position(child, x*window_get_ratio(), y);
}
