/*
 * Transform.c
 *
 *  Created on: 11 mars 2015
 *      Author: ethel
 */

#include "Transform.h"

void transform_refresh_matrix(Transform* t){
	//mat4x4_from_quat(t->matrix, t->rotation);
	mat4x4_translate(t->matrix, t->position[0], t->position[1], t->position[2]);
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

void transform_look_at(Transform* t, vec3 eye, vec3 center, vec3 up) {
	mat4x4_look_at(t->matrix, eye, center, up);
}
