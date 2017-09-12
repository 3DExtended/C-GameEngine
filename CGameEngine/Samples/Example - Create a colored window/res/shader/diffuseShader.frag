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

	float ToonThresholds[4];
    ToonThresholds[0] = 0.9;
    ToonThresholds[1] = 0.5;
    ToonThresholds[2] = 0.2;
    ToonThresholds[3] = 0.003;

	float ToonBrightnessLevels[5];
    ToonBrightnessLevels[0] = 1.0;
    ToonBrightnessLevels[1] = 0.8;
    ToonBrightnessLevels[2] = 0.6;
    ToonBrightnessLevels[3] = 0.35;
    ToonBrightnessLevels[4] = 0.0;

	float diffuse = clamp(dot(normalize(vNormal), normalize(-vVertex)),0,1);
	//apply color to fragment
	vec4 colorTemp = vColor;

	if (diffuse > ToonThresholds[0]) {
        colorTemp *= ToonBrightnessLevels[0];
    } else if (diffuse > ToonThresholds[1])  {
        colorTemp *= ToonBrightnessLevels[1];
    } else if (diffuse > ToonThresholds[2]) {
        colorTemp *= ToonBrightnessLevels[2];
    } else if (diffuse > ToonThresholds[3]) {
        colorTemp *= ToonBrightnessLevels[3];
    } else {
        colorTemp *= ToonBrightnessLevels[4];
    }
    
    color = vec4( colorTemp.xyz, 1.0 );

	//color = vec4(vColor.xyz * diffuse , vColor.a);
}