#version 440 core 

uniform sampler2D ssaoTex;

in vec2 FragCoord;

out vec4 FragColor;

void main() {

    float ao = 0.0;

    vec2 texelSize = 1.0 / vec2(textureSize(ssaoTex, 0));

    for(int x = -1; x <= 1; x++){
        for(int y = -1; y <= 1; y++){
            vec2 currentPos = FragCoord + vec2(x, y) * texelSize;
            ao += texture(ssaoTex, currentPos).r;
        }
    }

    float finalValue = ao / 9.0;

    FragColor = vec4(vec3(finalValue), 1.0);
}