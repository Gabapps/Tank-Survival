#version 150 core

in vec3 in_Vertex;

void main()
{
	gl_Position =   vec4(in_Vertex,1);
}