#version 150 core

out vec4 out_Color;

in vec3 normal;

uniform vec3 target;
uniform mat4 M;

void main()
{
	float a = dot(normalize(M*vec4(normal,1)), normalize(vec4(-target,1)));
	a=abs(a);
	out_Color = vec4(0.5,0.2,0.2,1)*a;
}