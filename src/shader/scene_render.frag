#version 440 core

in vec3 NormalViewSpace;
in vec3 PositionViewSpace;
in vec2 TexCoord;

uniform sampler2D tex;

layout(location = 0) out vec4 gColor;
layout(location = 1) out vec4 gNormal;
layout(location = 2) out vec4 gPos;

void main()
{
	gColor = texture(tex, TexCoord);
	gNormal = vec4(NormalViewSpace, 1.0f);
    gPos = vec4(PositionViewSpace, 1.0f);

}