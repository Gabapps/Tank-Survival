/*
 * Camera.h
 *
 *  Created on: 1 mars 2015
 *      Author: Gabriel
 */

#ifndef CAMERA_H_
#define CAMERA_H_

#include "Transform.h"
#include "Window.h"
#include "Math.h"

typedef struct Camera{
	//Transform transform;
	vec3 pos, target, up, dir;
	float fov, near, far;
	mat4x4 view_matrix;
	mat4x4 perspective_matrix;
} Camera;

/* \fn void camera_init(Camera* cam)
 *
 * \brief initialize the perspective and the view at the origin of the world
 * \param cam Camera to initialize
 *
 */

void camera_init(Camera* cam);

/**
 * \fn void camera_refresh_matrices(Camera* cam)
 * \brief Refresh the perspective and the view (in the transform) matrices.
 *
 * \param cam Camera to refresh.
 */
void camera_refresh_matrices(Camera* cam);

//Make the camera looking at target from pos
void camera_look_at(Camera* cam, vec3 pos, vec3 target, vec3 up);

//Return the direction of the camera
float* camera_direction(Camera* cam);

#endif /* CAMERA_H_ */
