/*
 * Camera.h
 *
 *  Created on: 1 mars 2015
 *      Author: Gabriel
 */

#ifndef CAMERA_H_
#define CAMERA_H_

#include "Transform.h"
#include "Math.h"

typedef struct Camera{
Transform transform;
float fov, near, far;
mat4x4 view_matrix;
}Camera;
//Camera structure

void camera_refresh_matrices();

#endif /* CAMERA_H_ */
