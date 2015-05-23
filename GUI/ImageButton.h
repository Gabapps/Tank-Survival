/*
 * ImageButton.h
 *
 *  Created on: 3 mai 2015
 *      Author: Gabriel
 */

#ifndef GUI_IMAGEBUTTON_H_
#define GUI_IMAGEBUTTON_H_

#include "Widget.h"
#include "Button.h"
#include "Image.h"
#include "TextView.h"

typedef Image ImageButton;

ImageButton* imagebutton_create();

Button* imagebutton_get_button(ImageButton* widget);

void imagebutton_set_text(ImageButton* widget, char* text);

#endif /* GUI_IMAGEBUTTON_H_ */
