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
	mat4x4_scale_aniso(t->matrix, t->matrix, t->scale[0], t->scale[1], t->scale[2]);
	if(t->parent) {
		//Transform in parent space
		mat4x4_mul(t->matrix, t->parent->matrix, t->matrix);
	}
}

void transform_origin(Transform* t) {
	vec3_zero(t->position);
	vec3_create(t->scale, 1,1,1);
	t->rotation = 0;
	mat4x4_identity(t->matrix);
}

Transform transform_origin_no_parent() {
	Transform t;
	transform_origin(&t);
	t.parent = NULL;
	t.children = list_tf_create();
	return t;
}

void transform_xyz(Transform* t, float x, float y, float z)
{
	transform_origin(t);
	t->position[0] = x;
	t->position[1] = y;
	t->position[2] = z;
}

Transform transform_xyz_no_parent(float x, float y, float z)
{
	Transform t = transform_origin_no_parent();
	t.position[0] = x;
	t.position[1] = y;
	t.position[2] = z;
	return t;
}

void transform_copy(Transform* t, const Transform* u) {
	vec3_cpy(t->position, u->position);
	vec3_cpy(t->scale, u->scale);
	t->rotation = u->rotation;
}

void transform_look_at(Transform* t, vec3 eye, vec3 center, vec3 up) {
	mat4x4_look_at(t->matrix, eye, center, up);
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

void transform_add_child(Transform* parent, Transform* child) {
	child->parent = parent;
	list_tf_put(parent->children, child);
}

void transform_rm_child(Transform* parent, Transform* child) {
	list_tf_delete(parent->children, child, 0);
}

void transform_to_world_coord(Transform* t) {
	transform_refresh_matrix(t);
	//mat4x4_mul_vec3(t->position, t->matrix, t->position);
	vec3_cpy(t->position, t->matrix[3]);
	t->rotation=t->parent->rotation;
}

void transform_scale(Transform* t, float x, float y, float z) {
	 vec3_create(t->scale, x, y, z);
}
