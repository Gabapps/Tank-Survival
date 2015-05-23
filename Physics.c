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

int RotRectsCollision(Transform* tr1, BoxCollider* b1, Transform* tr2, BoxCollider* b2)
{
	vec3	A, B;   // Sommets du rectangle 1
	vec3    C;      // Centre du rectangle 2
	vec3	BL, TR; // Sommets du rectangle 2 (bottom-left, top-right)

	float ang, cosa, sina;

	float t, x, a;      // Variables temporaires
	float dx;           // deltaX pour les equations lineaires
	float ext1, ext2;   // min/max verticale

	transform_refresh_matrix(tr1);
	transform_refresh_matrix(tr2);

	vec3 position1, position2;

	vec3_cpy(position1, tr1->matrix[3]);
	vec3_cpy(position2, tr2->matrix[3]);

	ang = tr2->rotation - tr1->rotation;	// Angle du rectangle 1
	cosa = cos(ang);           				// Pré calculs
	sina = sin(ang);

	// C la position de R2 par rapport à R1 (R1 est fictivement au centre)
	vec3_sub(C, position1, position2);

	// Rotation de C par l'angle du deuxième rectangle pour l'aligner à la grille
	vec3_rot(C, tr2->rotation);

	// Détermine les sommets du rectangle 2 (après l'avoir aligné)
	// BL = TR = C;
	vec3_cpy(BL, C);
	vec3_cpy(TR, C);

	BL[0] -= b2->longueur;
	BL[2] -= b2->largeur;

	TR[0] += b2->longueur;
	TR[2] += b2->largeur;

	// calculate vertices of (rotated := 'r') rr1

	//A[0] = -b1->longueur*sina; B[0] = A[0]; t = b1->largeur*cosa; A[0] += t; B[0] -= t;
	//A[2] =  b1->longueur*cosa; B[2] = A[2]; t = b1->largeur*sina; A[2] += t; B[2] -= t;

	//t = sina*cosa;


	// Détermine les sommets du rectangle 1
	A[0] = -(b1->largeur) * sina;
	B[0] = A[0];
	t = (b1->longueur) * cosa;
	A[0] += t;
	B[0] -= t;
	A[2] = (b1->largeur) * cosa;
	B[2] = A[2];
	t = (b1->longueur) * sina;
	A[2] += t;
	B[2] -= t;

	t = sina*cosa;

	// Selon la rotation du rectangle 1, il faut vérifier si les min/max verticale
	// sont cohérents. Si t<0, il faut les inverser
	if (t < 0)
	{
		t = A[0]; A[0] = B[0]; B[0] = t;
		t = A[2]; A[2] = B[2]; B[2] = t;
	}

	// Vérifie si B est le minimum horizontal (Sommet le plus à gauche)
	// Sinon on permutte B[0] et B[2]
	if (sina < 0) { B[0] = -B[0]; B[2] = -B[2]; }

	// Si le rectangle 1 n'est pas entre les limites horizontales du rectangle 2
	// La collision est impossible
	if (B[0] > TR[0] || B[0] > -BL[0]) return 0;

	// Si le rectangle 1 est aligné, les min et max vertcal sont évidents
	if (t == 0)
	{
		ext1 = A[2];
		ext2 = -ext1;
	}
	else  // Sinon, il faut trouver les min/max verticale dans [BL.x, TR.x]
	{
		x = BL[0]-A[0]; a = TR[0]-A[0];
		ext1 = A[2];
		// Si le premier min/max vertical n'est pas dans (BL.x, TR.x), alos
		// il faut trouver le vertical min/max sur BL[0] ou sur TR[0]
		if (a*x > 0)
		{
			dx = A[0];
			if (x < 0) { dx -= B[0]; ext1 -= B[2]; x = a; }
			else       { dx += B[0]; ext1 += B[2]; }
			ext1 *= x; ext1 /= dx; ext1 += A[2];
		}

		x = BL[0]+A[0]; a = TR[0]+A[0];
		ext2 = -A[2];
		// Si le second min/max vertical n'est pas dans (BL.x, TR.x), alos
		// il faut trouver le vertical sur BL[0] ou sur TR[0]
		if (a*x > 0)
		{
			dx = -A[0];
			if (x < 0) { dx -= B[0]; ext2 -= B[2]; x = a; }
			else       { dx += B[0]; ext2 += B[2]; }
			ext2 *= x; ext2 /= dx; ext2 -= A[2];
		}
	}

	// Vérifie si le rectangle 2 est entre les limites verticales du rectangle 1
	return !((ext1 < BL[2] && ext2 < BL[2]) ||
			(ext1 > TR[2] && ext2 > TR[2]));
}
