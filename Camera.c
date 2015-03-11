/*
 * Camera.c
 *
 *  Created on: 9 mars 2015
 *      Author: ethel
 */

#include "Camera.h"
//==> window_getratio()pour 640.f/480.f

//view et perspective sont relatives a la gestion de la camera?
void camera_init(Camera* cam){
	cam->fov = 70.f;
	cam->near = 0.1f;
	cam->far = 100.f;
}

void camera_refresh_matrices(Camera* cam){
	//ça a pas de sens? je devrais utiliser que perspective_matrix
	mat4x4 M, V, P, MVP;
	 mat4x4_mul(MVP, V, M); // MVP = P * V * M
	 mat4x4_mul(MVP, P, MVP);
}
//
