/**
 * @file Camera.h
 * @author Ethel Marquer, Gabriel Lucas, Nicolas Kaczmarek, Maxime Peralta
 * @date 1 Mar 2015
 * @brief A Camera is the mathematical positioning and perspective representation of the 3D world camera.
 */

#ifndef CAMERA_H_
#define CAMERA_H_

#include "Transform.h"
#include "Window.h"
#include "Math.h"

/*!
 * \struct Camera
 * Camera structure
 */
typedef struct Camera{
	vec3 pos, target, up, dir;
	float fov, near, far;
	mat4x4 view_matrix;
	mat4x4 perspective_matrix;
} Camera;

/**
 *  \fn void camera_init(Camera* cam)
 *
 * \brief initialize the perspective and the view at the origin of the world
 * \param cam Camera to initialize
 *
 */

void camera_init(Camera* cam);

/**
 * \fn void camera_refresh_matrices(Camera* cam)
 * \brief Refresh the perspective and the view (in the transform) matrices.
 * \param cam Camera to refresh.
 */
void camera_refresh_matrices(Camera* cam);

/**
 * \fn void camera_look_at(Camera* cam, vec3 pos, vec3 target, vec3 up)
 * \brief Make the camera looking at target from pos
 * \param cam Camera to move
 * \param pos Position of the camera
 * \param target Target of the camera
 * \param up Up orientation of the camera
 */
void camera_look_at(Camera* cam, vec3 pos, vec3 target, vec3 up);

/**
 * \fn float* camera_direction(Camera* cam)
 * \brief Return the direction of the camera
 * \param cam Camera
 */
float* camera_direction(Camera* cam);

#endif /* CAMERA_H_ */
