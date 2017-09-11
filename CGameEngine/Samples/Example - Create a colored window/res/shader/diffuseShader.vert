#version 330 core
//values we receive
layout(location = 0) in vec3 vertex;
layout(location = 1) in vec3 normal;
layout(location = 2) in vec2 texture;
layout(location = 3) in vec4 color;

//values we send
out vec4 vColor;

void main(){
	//Send color data to fragment shader
	vColor = color;

	//apply position as we received
	gl_Position = vec4(vertex,1.0);
}