/*
 * Transform.c
 *
 *  Created on: 11 mars 2015
 *      Author: ethel
 */

#include "Transform.h"

SceneObject* transform_get_so(Transform* t){
	return (SceneObject*)t;
}


void transform_refresh_matrix(Transform* t){
	mat4x4_from_quat(t->matrix, t->rotation);
	mat4x4_translate_in_place(t->matrix, t->position[0], t->position[1], t->position[2]);
	mat4x4_scale_aniso(t->matrix, t->matrix, t->scale[0], t->scale[1], t->scale[2]);
}
