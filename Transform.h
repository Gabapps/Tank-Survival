/*
 * Transform.h
 *
 *  Created on: 1 mars 2015
 *      Author: Gabriel
 */

#ifndef TRANSFORM_H_
#define TRANSFORM_H_

#include "Math.h"

typedef struct Transform{
	vec3 position;
	quat rotation;
	vec3 scale;
	mat4x4 matrix;
} Transform;

void transform_refresh_matrix(Transform* t);

Transform transform_origin();

Transform transform_xyz(float x, float y, float z);

void transform_look_at(Transform* t, vec3 eye, vec3 center, vec3 up); //not implemented

void transform_translate(Transform* t, vec3 vec);

void transform_quatY(Transform* t, float angle);
void transform_quatX(Transform* t, float angle);
void transform_quatZ(Transform* t, float angle);

void transform_rotateY(Transform* t, float angle);

#endif /* TRANSFORM_H_ */
