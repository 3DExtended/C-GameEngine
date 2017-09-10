#version 330 core
//values we receive
in vec4 vColor;

//values we send
out vec4 color;

void main(){
	//apply color to fragment
	color = vColor;
}