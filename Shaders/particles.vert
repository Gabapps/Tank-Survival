#version 150 core

in vec3 in_Vertex;
in vec4 in_Normal; //Ce n'est pas la normale mais la position de la particule
in vec4 in_UV; //Ce n'est pas l'UV mais la couleur de la particule

out vec4 Color;

uniform mat4 V;
uniform mat4 P;

void main(){
	Color = in_UV;
	gl_Position = P*V*(vec4(in_Vertex,1) + in_Normal);
}
