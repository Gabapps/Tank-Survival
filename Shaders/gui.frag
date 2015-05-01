#version 150 core

out vec3 out_Color;

in vec2 UV;

uniform sampler2D Mytexture;

void main()
{
	out_Color = texture( Mytexture, UV ).rgb;
}