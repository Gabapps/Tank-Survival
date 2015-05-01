/*
 * Image.h
 *
 *  Created on: 5 avr. 2015
 *      Author: Gabriel
 */

#ifndef GUI_IMAGE_H_
#define GUI_IMAGE_H_

#define GLEW_STATIC
#include <GL/glew.h>

#include "../Texture.h"
#include "../Ressources.h"

#include "Widget.h"

typedef struct Image {
	define_widget(Image);
	Texture* image;
	vec3 alphaColor;
} Image;

Image* image_create();

void image_setup(Image *image);
void image_draw(Image *image);

void image_set_texture(Image *image, Texture_ID id);

#endif /* GUI_IMAGE_H_ */
