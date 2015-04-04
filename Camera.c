/*
 * Camera.c
 *
 *  Created on: 9 mars 2015
 *      Author: ethel
 */

#include "Camera.h"

void camera_init(Camera* cam){
	cam->fov = 70.f;
	cam->near = 0.1f;
	cam->far = 100.f;
	mat4x4_perspective(cam->perspective_matrix,
			cam->fov, window_get_ratio(), cam->near, cam->far);
}
//initialisation of the camera

void camera_refresh_matrices(Camera* cam){

	mat4x4_look_at(cam->view_matrix, cam->pos, cam->target, cam->up);
}


void camera_look_at(Camera* cam, vec3 pos, vec3 target, vec3 up) {
	vec3_cpy(cam->pos, pos);
	vec3_cpy(cam->target, target);
	vec3_cpy(cam->up, up);

}

float* camera_direction(Camera* cam) {
	vec3 dir;
	vec3_cpy(dir, cam->target);
	vec3_sub(dir, dir, cam->pos);
	return dir;
}
