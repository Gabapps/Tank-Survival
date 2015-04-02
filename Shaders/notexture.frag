#version 330

out vec4 out_Color;

in vec3 normal;
in vec4 position;

uniform vec3 target;
uniform mat4 M;
uniform sampler2D texture;

void main()
{
	float a = dot(normalize(M*vec4(normal,1)), normalize(position-vec4(target,1)));
	vec4 color = vec4(0.1,0.8,0.2,1);
	a=abs(a);
	out_Color = color*a*0.8+color*0.2;
	
	//out_Color = vec4(texture( myTextureSampler, UV ),rgb,1);
}