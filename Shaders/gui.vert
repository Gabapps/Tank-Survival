#version 150 core

in vec3 in_Vertex;
in vec2 in_UV;

out vec2 UV;

uniform mat4 P;
uniform mat4 M;

void main()
{
	UV = in_UV;
	gl_Position =  P * M * vec4(in_Vertex,1);
}