#version 330

out vec3 out_Color;

in vec3 normal;
in vec4 position;
in vec2 UV;

uniform vec3 target;
uniform mat4 M;
uniform sampler2D Mytexture;

void main()
{	
	out_Color =  texture( Mytexture, UV ).rgb;
	
	//out_Color = vec3(1,0,0);
}