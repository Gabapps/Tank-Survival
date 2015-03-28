/*
 * Texture.h
 *
 *  Created on: 28 mars 2015
 *      Author: Gabriel
 */

#ifndef TEXTURE_H_
#define TEXTURE_H_

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <stdlib.h>
#include <stdio.h>

typedef struct Texture {
	char* path;
	GLuint texID;
	int height, width;
	unsigned char* data;
} Texture;

Texture* texture_create(char* path);

void texture_load(Texture* texture);

void texture_from_BMP(Texture* texture);

#endif /* TEXTURE_H_ */
