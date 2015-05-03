#version 150 core

out vec4 out_Color;

in vec2 UV;

uniform sampler2D Mytexture;
uniform vec3 alphaColor;

void main()
{
	vec4 color = texture( Mytexture, UV );
	if(all(equal(color.rgb, alphaColor))) color = vec4(0,0,0,0);
	out_Color = color;
}