/*
 * Button.c
 *
 *  Created on: 1 mai 2015
 *      Author: Gabriel
 */

#include "Button.h"

float time = 0;

Button* button_create() {
	Button* but = (Button*)malloc(sizeof(Button));
	widget_init((Widget*)but, button_run, NULL);
	but->focused = 0;
	but->onClick = NULL;
	but->onFocus = NULL;
	but->left = NULL;
	but->right = NULL;
	but->up = NULL;
	but->down = NULL;
	return but;
}

void button_run(struct Button *widget) {
	if(widget->focused) {
		time+=Time.deltaTime;
		if(time>0.4) {
			if(widget->left && input_keypressed("Left")) {
				button_unfocus(widget);
				button_focus(widget->left);
			}
			else if(widget->right && input_keypressed("Right")) {
				button_unfocus(widget);
				button_focus(widget->right);
			}
			else if(widget->up && input_keypressed("Up")) {
				button_unfocus(widget);
				button_focus(widget->up);
			}
			else if(widget->down && input_keypressed("Down")) {
				button_unfocus(widget);
				button_focus(widget->down);
			}
			else if(input_keypressed("Enter")) {
				if(widget->onClick) widget->onClick(widget);
			}
		}
	}
}

void button_set_onClickListener(Button *widget, void (*onClick) (struct Button *widget)) {
	widget->onClick = onClick;
}


void button_set_onFocusListener(Button *widget, void (*onFocus) (struct Button *widget, int focus)) {
	widget->onFocus = onFocus;
}

void button_focus(Button *widget) {
	widget->focused = 1;
	time = 0;
	if(widget->onFocus) widget->onFocus(widget, 1);
}

void button_unfocus(Button *widget) {
	widget->focused = 0;
	if(widget->onFocus) widget->onFocus(widget, 0);
}

void button_set_near_buttons(Button* widget, Button* left, Button* right, Button* up, Button* down) {
	widget->left = left;
	widget->right = right;
	widget->up = up;
	widget->down = down;
}
