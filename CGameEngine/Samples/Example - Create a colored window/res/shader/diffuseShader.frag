#version 330 core
//values we receive
in vec3 vVertex;
in vec3 vNormal;
in vec2 vTexture;
in vec4 vColor;


//values we send
out vec4 color;

uniform mat4 matrix;
uniform mat4 nmatrix;
uniform mat4 pmatrix; //View * model


void main(){

	float diffuse = clamp(dot(normalize(vNormal), normalize(-vVertex)),0.15,1);

	color = vec4(vColor.xyz * diffuse , vColor.a);
}