/*
 * Camera.c
 *
 *  Created on: 9 mars 2015
 *      Author: ethel
 */

#include "Camera.h"
#include "Transform.h"

void camera_init(Camera* cam){
	cam->fov = 70.f;
	cam->near = 0.1f;
	cam->far = 100.f;
	mat4x4_perspective(cam->perspective_matrix, 70.f, 640.f/480.f, 0.1f, 100.f);
}

void camera_refresh_matrices(Camera* cam){

	transform_refresh_matrix(cam->transform);
}

