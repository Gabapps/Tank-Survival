/*
 * Physics.c
 *
 *  Created on: 6 avr. 2015
 *      Author: Nicolas
 */

#include "Physics.h"

BoxCollider* collider_create(float largeur, float longueur)
{
	BoxCollider* collider = (BoxCollider*)malloc(sizeof(BoxCollider));
	collider->largeur = largeur;
	collider->longueur = longueur;

	return collider;
}

// Rotated Rectangles Collision Detection, Oren Becker, 2001
int RotRectsCollision(Transform* tr1, BoxCollider* b1, Transform* tr2, BoxCollider* b2)
{
	vec3	A, B;   // vertices of the rotated rr2
	vec3    C;      // center of rr2
	vec3	BL, TR; // vertices of rr2 (bottom-left, top-right)

	float ang, cosa, sina;

	float t, x, a;      // temporary variables for various uses
	float dx;           // deltaX for linear equations
	float ext1, ext2;   // min/max vertical values

// so->transform->rotation
	ang = tr1->rotation - tr2->rotation;  // orientation of rotated so1
	cosa = cos(ang);           // precalculated trigonometic -
	sina = sin(ang);           // - values for repeated use

	// move rr2 to make rr1 cannonic
	vec3_sub(C, tr2->position, tr1->position);

	// rotate rr2 clockwise by rr2->ang to make rr2 axis-aligned
	vec3_rot(C, tr2->rotation);

	// calculate vertices of (moved and axis-aligned := 'ma') rr2
	//BL = TR = C;
	vec3_cpy(BL, C);
	vec3_cpy(TR, C);

	BL[0] -= b2->largeur;
	BL[2] -= b2->longueur;

	TR[0] -= b2->largeur;
	TR[2] -= b2->longueur;

	// calculate vertices of (rotated := 'r') rr1

	A[0] = -b1->longueur*sina; B[0] = A[0]; t = b1->largeur*cosa; A[0] += t; B[0] -= t;
	A[2] =  b1->longueur*cosa; B[2] = A[2]; t = b1->largeur*sina; A[2] += t; B[2] -= t;

	t = sina*cosa;



	// verify that A is vertical min/max, B is horizontal min/max
	if (t < 0)
	{
		t = A[0]; A[0] = B[0]; B[0] = t;
		t = A[2]; A[2] = B[2]; B[2] = t;
	}

	// verify that B is horizontal minimum (leftest-vertex)
	if (sina < 0) { B[0] = -B[0]; B[2] = -B[2]; }

	// if rr2(ma) isn't in the horizontal range of
	// colliding with rr1(r), collision is impossible
	if (B[0] > TR[0] || B[0] > -BL[0]) return 0;

	// if rr1(r) is axis-aligned, vertical min/max are easy to get
	if (t == 0)
	{
		ext1 = A[2];
		ext2 = -ext1;
	}
	else  // else, find vertical min/max in the range [BL.x, TR.x]
	{
		x = BL[0]-A[0]; a = TR[0]-A[0];
		ext1 = A[2];
		// if the first vertical min/max isn't in (BL.x, TR.x), then
		// find the vertical min/max on BL.x or on TR.x
		if (a*x > 0)
		{
			dx = A[0];
			if (x < 0) { dx -= B[0]; ext1 -= B[2]; x = a; }
			else       { dx += B[0]; ext1 += B[2]; }
			ext1 *= x; ext1 /= dx; ext1 += A[2];
		}

		x = BL[0]+A[0]; a = TR[0]+A[0];
		ext2 = -A[2];
		// if the second vertical min/max isn't in (BL.x, TR.x), then
		// find the local vertical min/max on BL.x or on TR.x
		if (a*x > 0)
		{
			dx = -A[0];
			if (x < 0) { dx -= B[0]; ext2 -= B[2]; x = a; }
			else       { dx += B[0]; ext2 += B[2]; }
			ext2 *= x; ext2 /= dx; ext2 -= A[2];
		}
	}

	// check whether rr2(ma) is in the vertical range of colliding with rr1(r)
	// (for the horizontal range of rr2)
	return !((ext1 < BL[2] && ext2 < BL[2]) ||
			(ext1 > TR[2] && ext2 > TR[2]));
}
