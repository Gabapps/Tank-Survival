#version 410

layout(location = 0) in vec3 in_Vertex;
layout(location = 1) in vec3 in_Normal;
layout(location = 2) in vec2 in_UV;

out vec3 normal;
out vec4 position;
out vec2 UV;

uniform mat4 V;
uniform mat4 P;
uniform mat4 M;

void main()
{
	normal = in_Normal;
    position = M * vec4(in_Vertex,1);
    UV = in_UV;
	gl_Position =  P*V*M * vec4(in_Vertex,1);
}