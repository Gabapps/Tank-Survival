/*
 * Image.h
 *
 *  Created on: 5 avr. 2015
 *      Author: Gabriel
 */

#ifndef GUI_IMAGE_H_
#define GUI_IMAGE_H_

#include "../Texture.h"
#include "../Ressources.h"

#include "Widget.h"

typedef struct Image {
	define_widget(Image);
	Texture image;
} Image;

Image* image_create();

void image_setup(Image *image);
void image_draw(Image *image);

void image_set_texture(Image *image, Texture_ID id);

Image* image_create() {
	Image* img = (Image*)malloc(sizeof(Image));
	widget_init(img, image_setup, image_draw);
	img->image = NULL;
	return img;
}

void image_setup(Image *image) {

}

void image_draw(Image *image) {

}

void image_set_texture(Image *image, Texture_ID id) {
	image->image = ressources_get_texture(id);
}

#endif /* GUI_IMAGE_H_ */
