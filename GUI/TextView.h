/*
 * TextView.h
 *
 *  Created on: 8 mai 2015
 *      Author: Gabriel
 */

#ifndef GUI_TEXTVIEW_H_
#define GUI_TEXTVIEW_H_

#define GLEW_STATIC
#include <GL/glew.h>

#include "../Ressources.h"

#include "Widget.h"

typedef struct TextView {
	define_widget(TextView);
	char* text;
	Texture* font;
	Mesh* mesh;
} TextView;

TextView* textview_create();

void textview_draw(TextView* tv);

void textview_set_text(TextView* tv, char* text);

void textview_set_font(TextView* tv, Texture_ID font);

void textview_use_font(Texture_ID font);

#endif /* GUI_TEXTVIEW_H_ */
