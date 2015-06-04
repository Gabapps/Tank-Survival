/**
 * @file Transform.h
 * @author Ethel Marquer, Gabriel Lucas, Nicolas Kaczmarek, Maxime Peralta
 * @date 1 March 2015
 * @brief A transform represents the positioning of a scene object or of a camera
 */


#ifndef TRANSFORM_H_
#define TRANSFORM_H_

#include "Math.h"
#include "List.h"

typedef struct Transform Transform;

typelist(tf, Transform*);

struct Transform{
	Transform *parent;
	list_tf *children;
	vec3 position;
	float rotation;
	vec3 scale;
	mat4x4 matrix;
};

//Update the coordinates of the matrix
void transform_refresh_matrix(Transform* t);

//Return an initialized transform at the origin with no parent and no child
Transform transform_origin_no_parent();

//Move a transform at the origin without changing his parent and children
void transform_origin(Transform* t);

//Return an initialized transform at the point (x,y,z) with no parent and no child
Transform transform_xyz_no_parent(float x, float y, float z);

//Move a transform at the point (x,y,z) without changing his parent and children
void transform_xyz(Transform* t, float x, float y, float z);

//Copy a transform into another without changing their parent and children
void transform_copy(Transform* t, const Transform* u);

//Translate a transform
void transform_translate(Transform* t, vec3 vec);

//Rotation a transform around the y axis
void transform_rotateY(Transform* t, float angle);

//Add a child to a transform
void transform_add_child(Transform* parent, Transform* child);

//Remove a child from a transform
void transform_rm_child(Transform* parent, Transform* child);

//Compute and move a transform to the world space
void transform_to_world_coord(Transform* t);

//Scale the transform
void transform_scale(Transform* t, float x, float y, float z);

#endif /* TRANSFORM_H_ */
