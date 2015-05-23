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
	TextView* tv = textview_create();
	widget_add_child((Widget*)but, (Widget*)button);
	widget_add_child((Widget*)but, (Widget*)tv);
	return but;
}

Button* imagebutton_get_button(ImageButton* widget) {
	return (Button*)widget->children->root->value;
}

void imagebutton_set_text(ImageButton* widget, char* text) {
	textview_set_text((TextView*)widget->children->root->next->value, text);
}
