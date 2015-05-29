#ifndef SHADER_H_INCLUDED
#define SHADER_H_INCLUDED

#define GLEW_STATIC

#include <stdio.h>
#include <stdlib.h>

// Include Windows
#ifdef WIN32
#include <GL/glew.h>


// Include Mac

#elif __APPLE__
#define GL3_PROTOTYPES 1
#include <OpenGL/gl3.h>


// Include UNIX/Linux

#else
#define GL3_PROTOTYPES 1
#include <GL3/gl3.h>

#endif

typedef struct
{
    char* vertex_shader;
    char* fragment_shader;
    GLuint program;
    GLuint vertex;
    GLuint fragment;
} Shader;

//Create a shader
Shader* shader_create(char* vertex, char* fragment);

//Destroy a shader
void shader_free(Shader* shader);

//Load and compile a shader
int shader_load(Shader* shader);

//Compile a shader
int shader_compile(GLuint* shader, GLenum type, char* filename);

#endif // SHADER_H_INCLUDED
