#version 440 core

in vec2 TexCoord;
in vec3 Normal;
in vec3 FragPos;
in vec4 vertLightPos;

in vec3 NormalViewSpace;
in vec3 PositionViewSpace;

layout(location = 0) out vec4 FragColor;
layout(location = 1) out vec4 normalTex;
layout(location = 2) out vec4 posTex;


uniform sampler2D tex;
uniform sampler2D depthTex;

uniform vec3 lightDir;
uniform vec3 color;
uniform float intensity;
uniform vec3 viewPos;

float ambientStrength = 0.1f;
float shininess = 32.0f;

void main()
{

	normalTex = vec4(NormalViewSpace, 1.0f);
    posTex = vec4(PositionViewSpace, 1.0f);

}