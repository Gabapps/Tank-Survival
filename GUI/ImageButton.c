/*
 * ImageButton.c
 *
 *  Created on: 3 mai 2015
 *      Author: Gabriel
 */

#include "ImageButton.h"

ImageButton* imagebutton_create() {
	ImageButton* but = image_create();
	Button* button = button_create();
	widget_add_child((Widget*)but, (Widget*)button);
	return but;
}

Button* imagebutton_get_button(ImageButton* widget) {
	return (Button*)widget->children->root->value;
}
