/**
 * @file Physics.h
 * @author Ethel Marquer, Gabriel Lucas, Nicolas Kaczmarek, Maxime Peralta
 * @date 6 Apr 2015
 * @brief The Physics module contains functions and structures for collision purpose.
 */

#ifndef PHYSICS_H_
#define PHYSICS_H_

#include "stdlib.h"
#include "Math.h"
#include "Transform.h"

//Angle en radian et Position du centre dispo dans Transform.h
//so->transform->rotation	float rotation;
//so->transform->position	vec3 position;

//Bounding box rectangle à créer

/*!
 * \struct BoxCollider
 * BoxCollider structure
 */
typedef struct BoxCollider{
	float largeur;
	float longueur;
} BoxCollider;


/**
 * \fn BoxCollider* collider_create(float largeur, float longueur);
 * \brief create a BoxCollider structure with the given parameters
 *
 * \param largeur	The width of the shape
 * \param longueur	The length of the shape
 *
 * \return a BoxCollider pointer
 */
BoxCollider* collider_create(float largeur, float longueur);


/**
 * \fn int RotRectsCollision(Transform* tr1, BoxCollider* b1, Transform* tr2, BoxCollider* b2);
 * \brief Detect if there is a collision between two rectangles (based on Oren Becker's code)
 *
 * \param tr1	Transformation structure of the first rectangle
 * \param b1	BoxCollider of the first rectangle (define the physique shape)
 * \param tr2	Transformation structure of the second rectangle
 * \param b2	BoxCollider of the second rectangle (define the physique shape)
 *
 * \return 1 if there is a collision. 0 otherwise.
 */
int RotRectsCollision(Transform* tr1, BoxCollider* b1, Transform* tr2, BoxCollider* b2);


#endif /* PHYSICS_H_ */
