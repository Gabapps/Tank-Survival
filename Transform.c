/*
 * Transform.c
 *
 *  Created on: 11 mars 2015
 *      Author: ethel
 */
#include <stdio.h>
#include <stdlib.h>
#include "Transform.h"


void transform_refresh_matrix(Transform* t){
	mat4x4 translation;
	mat4x4_identity(t->matrix);
	mat4x4_rotate_Y(t->matrix, t->matrix, t->rotation);
	mat4x4_translate(translation, t->position[0], t->position[1], t->position[2]);
	mat4x4_mul(t->matrix, translation, t->matrix);
}

Transform transform_origin() {
	Transform t;
	vec3_zero(t.position);
	vec3_zero(t.scale);
	t.rotation =0;
	mat4x4_identity(t.matrix);
	return t;
}

Transform transform_xyz(float x, float y, float z)
{
	Transform t = transform_origin();
	t.position[0] = x;
	t.position[1] = y;
	t.position[2] = z;
	return t;
}

void transform_look_at(Transform* t, vec3 eye, vec3 center, vec3 up) {
	mat4x4_look_at(t->matrix, eye, center, up);
}

void transform_translate_world(Transform* t, vec3 vec) {
	vec3_add(t->position, t->position, vec);
}

void transform_translate(Transform* t, vec3 vec) {

	vec3_rot(vec, -t->rotation);

	vec3_add(t->position,t->position, vec);
	vec3_norm(vec, vec);
}

/*
void transform_quatY(Transform* t, float angle){
	vec3 axisY = {0,1,0};
	quat_create(t->rotation, axisY,angle);
}
void transform_quatX(Transform* t, float angle){
	vec3 axisX = {1,0,0};
	quat_create(t->rotation,axisX,angle);
}
void transform_quatZ(Transform* t, float angle){
	vec3 axisZ = {0,0,1};
	quat_create(t->rotation,axisZ,angle);
}
 */
void transform_rotateY(Transform* t, float angle) {
	t->rotation += angle;
	if(t->rotation>2*M_PI) t->rotation-=2*M_PI;
	if(t->rotation<-2*M_PI) t->rotation+=2*M_PI;
}
