#version 440 core 

uniform sampler2D colorTex; 

in vec2 TexCoord;

out vec4 FragColor;

void main(){

	FragColor  = texture(colorTex, TexCoord);
}

