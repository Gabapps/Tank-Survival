#version 150 core

out vec3 out_Color;

in vec3 normal;
in vec4 position;
in vec2 UV;

uniform vec3 lightdir;
uniform vec3 lightcolor;
uniform float lightforce;
uniform vec3 camdir;

uniform sampler2D Mytexture;

void main()
{	
	vec3 color;
	vec3 texture_color =  texture( Mytexture, UV ).rgb;

	out_Color = texture_color;
}