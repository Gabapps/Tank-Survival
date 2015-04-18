/*
 * Transform.h
 *
 *  Created on: 1 mars 2015
 *      Author: Gabriel
 */

#ifndef TRANSFORM_H_
#define TRANSFORM_H_

#include "Math.h"
#include "List.h"

typedef struct Transform Transform;

typelist(tf, Transform*);

struct Transform{
	Transform *parent;
	list_tf *children;
	vec3 position;
	float rotation;
	vec3 scale;
	mat4x4 matrix;
};

void transform_refresh_matrix(Transform* t);

Transform transform_origin_no_parent();

void transform_origin(Transform* t);

Transform transform_xyz_no_parent(float x, float y, float z);

void transform_xyz(Transform* t, float x, float y, float z);

void transform_copy(Transform* t, const Transform* u);

//void transform_look_at(Transform* t, vec3 eye, vec3 center, vec3 up); //not implemented

void transform_translate_world(Transform* t, vec3 vec);
void transform_translate(Transform* t, vec3 vec);

//void transform_quatY(Transform* t, float angle); //not implemented
//void transform_quatX(Transform* t, float angle); //not implemented
//void transform_quatZ(Transform* t, float angle); //not implemented

void transform_rotateY(Transform* t, float angle);

void transform_add_child(Transform* parent, Transform* child);
void transform_rm_child(Transform* parent, Transform* child);

void transform_to_world_coord(Transform* t);

#endif /* TRANSFORM_H_ */
