/*
 * particles.c
 *
 *  Created on: 1 mai 2015
 *      Author: ethel
 */

#include "particles.h"


void particles_setup(){

	g_particule_position_size_data = (GLfloat*)malloc(sizeof(GLfloat)*MAXPARTICLES);
	g_particule_color_data = (GLfloat*)malloc(sizeof(GLfloat)*MAXPARTICLES);

	glGenBuffers(1, &billboard_vertex_buffer);
	glBindBuffer(GL_ARRAY_BUFFER, billboard_vertex_buffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_STATIC_DRAW);

	// The VBO containing the positions and sizes of the particles

	glGenBuffers(1, &particles_position_buffer);
	glBindBuffer(GL_ARRAY_BUFFER, particles_position_buffer);
	// Initialize with empty (NULL) buffer : it will be updated later, each frame.
	glBufferData(GL_ARRAY_BUFFER, MAXPARTICLES * 4 * sizeof(GLfloat), NULL, GL_STREAM_DRAW);

	// The VBO containing the colors of the particles
	glGenBuffers(1, &particles_color_buffer);
	glBindBuffer(GL_ARRAY_BUFFER, particles_color_buffer);
	// Initialize with empty (NULL) buffer : it will be updated later, each frame.
	glBufferData(GL_ARRAY_BUFFER, MAXPARTICLES * 4 * sizeof(GLubyte), NULL, GL_STREAM_DRAW);
}

void update_particles(){

	glBindBuffer(GL_ARRAY_BUFFER, particles_position_buffer);
	glBufferData(GL_ARRAY_BUFFER, MAXPARTICLES * 4 * sizeof(GLfloat), NULL, GL_STREAM_DRAW); // Buffer orphaning, a common way to improve streaming perf. See above link for details.
	glBufferSubData(GL_ARRAY_BUFFER, 0, ParticlesCount * sizeof(GLfloat) * 4, g_particule_position_size_data);
	glBindBuffer(GL_ARRAY_BUFFER, particles_color_buffer);
	glBufferData(GL_ARRAY_BUFFER, MAXPARTICLES * 4 * sizeof(GLubyte), NULL, GL_STREAM_DRAW); // Buffer orphaning, a common way to improve streaming perf. See above link for details.
	glBufferSubData(GL_ARRAY_BUFFER, 0, ParticlesCount * sizeof(GLubyte) * 4, g_particule_color_data);}

void draw(){
	GLuint program = ressources_get_shader(SHADER_PARTICLES)->program;
	// 1rst attribute buffer : vertices
	glUseProgram(program);
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, billboard_vertex_buffer);
	glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,0,(void*)0);

	// 2nd attribute buffer : positions of particles' centers
	glEnableVertexAttribArray(1);
	glBindBuffer(GL_ARRAY_BUFFER, particles_position_buffer);
	glVertexAttribPointer(1,4,GL_FLOAT,GL_FALSE,0,(void*)0);
	glEnableVertexAttribArray(2);
	glBindBuffer(GL_ARRAY_BUFFER, particles_color_buffer);
	glVertexAttribPointer(2,4,GL_UNSIGNED_BYTE,GL_TRUE,0,(void*)0);
	glDrawArraysInstanced(GL_TRIANGLE_STRIP, 0, 4, ParticlesCount);

	glUniformMatrix4fv(glGetUniformLocation(program, "V"), 1, GL_FALSE, mat4x4_ptr(Game.scene->camera.view_matrix));
	glUniformMatrix4fv(glGetUniformLocation(program, "P"), 1, GL_FALSE, mat4x4_ptr(Game.scene->camera.perspective_matrix));

	glVertexAttribDivisor(0, 0); // particles vertices : always reuse the same 4 vertices -> 0
	glVertexAttribDivisor(1, 1); // positions : one per quad (its center) -> 1
	glVertexAttribDivisor(2, 1); // color : one per quad -> 1
	glDrawArraysInstanced(GL_TRIANGLE_STRIP, 0, 4, ParticlesCount);

	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(2);

	glUseProgram(0);
}

void particles_init(){
	int i;
	for(i=0;i<MAXPARTICLES;i++){
		ParticlesContainer[i].a=255;
		ParticlesContainer[i].b=10;
		ParticlesContainer[i].g=15;
		ParticlesContainer[i].r=200;
		ParticlesContainer[i].angle=20;
		ParticlesContainer[i].life=100;
		vec3_create(ParticlesContainer[i].pos,15,0,15);
		ParticlesContainer[i].size=5;
		ParticlesContainer[i].weight=5;
		vec3_create(ParticlesContainer[i].speed,2,0,2);
	}
}


