#include <stdlib.h>
#include <stdio.h>
#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "Shader.h"
#include "Mesh.h"
#include "Math.h"

static void error_callback(int error, const char* description)
{
    fputs(description, stderr);
}

static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
    glfwSetWindowShouldClose(window, GL_TRUE);
}

int main(void)
{
    GLFWwindow* window;

    if (!glfwInit())
        exit(EXIT_FAILURE);
    window = glfwCreateWindow(640, 480, "Simple example", NULL, NULL);

    if (!window)
    {
        glfwTerminate();
        exit(EXIT_FAILURE);
    }
    glfwSetErrorCallback(error_callback);
    glfwMakeContextCurrent(window);
    glfwSetKeyCallback(window, key_callback);

    glewExperimental=GL_FALSE;
    GLenum error = glGetError();

    if (error != GL_NO_ERROR)
    {
        printf("OpenGL Error: %d\n", error);
    }
    GLenum glewinit = glewInit();
    if (glewinit != GLEW_OK) {
        printf("Glew's not okay! %s\n", glewGetErrorString(glewinit));
        exit(EXIT_FAILURE);
    }
    if (!GLEW_VERSION_2_1)  // check that the machine supports the 2.1 API.
    	exit(EXIT_FAILURE);

    Shader shader = {"Shaders/vertex.vert", "Shaders/fragment.frag",0,0,0};
    shader_load(&shader);

    Mesh mesh;
    mesh_load_from_obj(&mesh, "Models/Tank.obj");
    float *vertices = mesh_get_vertices(&mesh);
    float *normals = mesh_get_normals(&mesh);

    mat4x4 M, V, P, MVP;
    vec3 pos = {-2,1.25,-3};
    vec3 dir = {0,0,0};
    vec3 up = {0,1,0};
    vec3 target;

    vec3_sub(target, dir, pos);

    mat4x4_identity(M);

    mat4x4_look_at(V,pos,dir,up);

    mat4x4_perspective(P, 70.f, 640.f/480.f, 0.1f, 100.f);

    mat4x4_mul(MVP, V, M);
    mat4x4_mul(MVP, P, MVP);

    glEnable(GL_DEPTH_TEST);

    while (!glfwWindowShouldClose(window))
    {

    	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    	glUseProgram(shader.program);

    	    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, vertices);
    	    glEnableVertexAttribArray(0);
    	    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, normals);
    	    glEnableVertexAttribArray(1);

    	    glUniformMatrix4fv(glGetUniformLocation(shader.program, "MVP"), 1, GL_FALSE, &MVP[0][0]);
    	    glUniformMatrix4fv(glGetUniformLocation(shader.program, "M"), 1, GL_FALSE, &M[0][0]);
    	    glUniformMatrix4fv(glGetUniformLocation(shader.program, "V"), 1, GL_FALSE, &V[0][0]);
    	    glUniformMatrix4fv(glGetUniformLocation(shader.program, "P"), 1, GL_FALSE, &P[0][0]);
    	    glUniform3fv(glGetUniformLocation(shader.program, "target"), 1,target);

    	    glDrawArrays(GL_TRIANGLES, 0, mesh.f*3);

    	    glDisableVertexAttribArray(1);
    	    glDisableVertexAttribArray(0);

    	glUseProgram(0);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    mesh_free(&mesh);

    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}
