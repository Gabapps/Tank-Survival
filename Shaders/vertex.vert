#version 150 core

in vec3 in_Vertex;
in vec3 in_Normal;

out vec3 normal;

uniform mat4 MVP;
uniform mat4 V;
uniform mat4 P;

void main()
{
	normal = in_Normal;
    // Output position of the vertex, in clip space : MVP * position
	gl_Position =  MVP * vec4(in_Vertex,1);
}