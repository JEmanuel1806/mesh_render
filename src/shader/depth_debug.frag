#version 440 core 

uniform sampler2D depthTex; 

in vec2 TexCoord;

out vec4 FragColor;

void main(){

	float depth = texture(depthTex, TexCoord).r;
    FragColor = vec4(vec3(depth), 1.0);
}

