/*
 * Button.h
 *
 *  Created on: 1 mai 2015
 *      Author: Gabriel
 */

#ifndef GUI_BUTTON_H_
#define GUI_BUTTON_H_

#include "Widget.h"
#include "../Input.h"
#include "../Time.h"

typedef struct Button {
	define_widget(Button);
	void (*onClick) (struct Button *widget);
	void (*onFocus) (struct Button *widget, int focus);
	int focused;
	struct Button* left;
	struct Button* right;
	struct Button* up;
	struct Button* down;
} Button;

Button* button_create();

void button_run(Button* widget);
void button_set_onClickListener(Button *widget, void (*onClick) (struct Button *widget));
void button_set_onFocusListener(Button *widget, void (*onFocus) (struct Button *widget, int focus));

void button_focus(Button *widget);
void button_unfocus(Button *widget);

void button_set_near_buttons(Button* widget, Button* left, Button* right, Button* up, Button* down);

#endif /* GUI_BUTTON_H_ */
