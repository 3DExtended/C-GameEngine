#version 330 core

in vec2 uvs;

uniform sampler2D tex;

out vec4 color;

const float width = 0.5f;
const float edge = 0.05f;

void main(){

	float distance = 1 - texture(tex,uvs).a;

	float alpha = 1 - smoothstep(width, width + edge, distance);

	//color = texture(tex,uvs);

	//color = vec4(1,1,1,alpha);


	if(texture(tex,uvs).a < 0.5)
		discard;
	else
		color = vec4(1,1,1,1);
	
}