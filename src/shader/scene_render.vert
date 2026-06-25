#version 440 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aTexCoord;
layout (location = 2) in vec3 aNormal;

out vec2 TexCoord;
out vec3 Normal;
out vec3 FragPos; 
out vec4 vertLightPos;

out vec3 NormalViewSpace;
out vec3 PositionViewSpace;

uniform mat4 model;
uniform mat4 view;
uniform mat4 proj;

uniform mat4 lightView;
uniform mat4 lightProj;

void main() {
    vec4 worldPosition = model * vec4(aPos, 1.0);

    FragPos = worldPosition.xyz;
    TexCoord = aTexCoord;
    Normal = mat3(transpose(inverse(model))) * aNormal;

    gl_Position = proj * view * worldPosition;
    vertLightPos = lightProj * lightView * worldPosition;

    NormalViewSpace = mat3(transpose(inverse(view * model))) * aNormal;
    PositionViewSpace = (view * worldPosition).xyz;

}
