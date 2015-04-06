/*
 * Physics.h
 *
 *  Created on: 6 avr. 2015
 *      Author: Nicolas
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

typedef struct BoxCollider{
	float largeur;
	float longueur;
} BoxCollider;


BoxCollider* collider_create(float largeur, float longueur);
int RotRectsCollision(Transform* tr1, BoxCollider* b1, Transform* tr2, BoxCollider* b2);


#endif /* PHYSICS_H_ */
