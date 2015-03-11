/*
 * Transform.h
 *
 *  Created on: 1 mars 2015
 *      Author: Gabriel
 */

#ifndef TRANSFORM_H_
#define TRANSFORM_H_

#include "Math.h"
#include "SceneObject.h"

typedef struct Transform{
	vec3 position;
	quat rotation;
	vec3 scale;
	mat4x4 matrix;
} Transform;


/* SceneObject* transform_get_so(Transform*);
 *
 * \brief get a sceneObject associated to a transform.
 * \param t The transform of a sceneObject.
 * \return The sceneObject associated.
 *
 */

SceneObject* transform_get_so(Transform* t);

void transform_refresh_matrix(Transform* t);


#endif /* TRANSFORM_H_ */
