#version 330 core

layout(location = 0) in vec3 vertex;
layout(location = 1) in vec2 uv;

out vec2 uvs;

void main(){
	//vec2 temp = vec2(uv.x, uv.y);
	uvs = uv;
	gl_Position = vec4(vertex,1.0);
}