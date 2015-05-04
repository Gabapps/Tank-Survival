/*
 * particles.h
 *
 *  Created on: 7 avr. 2015
 *      Author: ethel
 */

#ifndef PARTICLES_H_
#define PARTICLES_H_
#define GLEW_STATIC
#define MAXPARTICLES 100000

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <stdlib.h>
#include <stdio.h>
#include "Math.h"
#include "Ressources.h"


typedef struct Particle{
	vec3 pos, speed;
	    unsigned char r,g,b,a; // Color
	    float size, angle, weight;
	    float life;
} Particle;

Particle ParticlesContainer[MAXPARTICLES];

typedef struct emmiter{

} emmiter;

void particles_init();
void particles_setup();
void draw();
void update_particles();

static const GLfloat g_vertex_buffer_data[] ={
		-0.5f, -0.5f, 0.0f,
		0.5f, -0.5f,0.0f,
		-0.5f, 0.5f, 0.0f,
		0.5f, 0.5f, 0.0f};

GLuint particles_position_buffer; // buffer for the particles’ centers.
GLuint particles_color_buffer;// buffer for the particles’ colors.
GLuint billboard_vertex_buffer;//buffer for the vertices of the mesh

GLuint ParticlesCount;
GLfloat * g_particule_position_size_data;
GLfloat * g_particule_color_data;


#endif /* PARTICLES_H_ */
