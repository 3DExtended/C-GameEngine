#version 330 core
//values we receive
layout(location = 0) in vec3 vertex;
layout(location = 1) in vec3 normal;
layout(location = 2) in vec2 texture;
layout(location = 3) in vec4 color;

uniform mat4 matrix;
uniform mat4 nmatrix;
uniform mat4 pmatrix; //View * model

//values we send
out vec3 vVertex;
flat out vec3 vNormal;
out vec2 vTexture;
out vec4 vColor;

void main(){
	//Send color data to fragment shader
	vColor = color;

	//interpolate UV coords
	vTexture = texture;

	//recalculate normal vector
	vNormal = normalize((nmatrix * vec4(normal, 1.0)).xyz);

	//send projected vertex coord
	vVertex = (pmatrix * vec4(vertex,1.0)).xyz;

	//apply position as we received
	gl_Position = matrix * vec4(vertex,1.0);
}