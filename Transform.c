/*
 * Transform.c
 *
 *  Created on: 11 mars 2015
 *      Author: ethel
 */

#include "Transform.h"


void transform_refresh_matrix(Transform* t){
	mat4x4 translation;
	mat4x4_from_quat(t->matrix, t->rotation);
	mat4x4_translate(translation, t->position[0], t->position[1], t->position[2]);
	mat4x4_mul(t->matrix, translation, t->matrix);
	//mat4x4_scale_aniso(t->matrix, t->matrix, t->scale[0], t->scale[1], t->scale[2]);
}

Transform transform_origin() {
	Transform t;
	vec3_zero(t.position);
	vec3_zero(t.scale);
	quat_identity(t.rotation);
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
	vec4 vec2;
	quat conj;
	vec2[0]=vec[0];
	vec2[0]=vec[1];
	vec2[0]=vec[2];
	vec2[0]=vec[3];
	mat4x4 rotation;
	//mat4x4 translation;
	//vec3 position;
	mat4x4_from_quat(rotation, t->rotation);
	//mat4x4_mul(rotation, translation, rotation);
	/*mat4x4_mul_vec4(vec2, rotation, vec2);
	vec3_add(t->position, vec_copy, t->position);*/
	vec4_mul(vec2, t->rotation, vec2);
	quat_conj(conj, t->rotation, conj);
	vec4_mul(vec2,conj,vec2);
	mat4x4_mul_vec4(vec2, rotation, vec2);
	vec3_add(t->position, vec2, t->position);
}

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

void transform_rotateY(Transform* t, float angle) {
	vec3 axisY = {0,1,0};
	quat delta;
	quat_create(delta, axisY,angle);
	quat_mul(t->rotation,t->rotation,delta);
}
