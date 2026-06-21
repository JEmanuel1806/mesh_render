#version 440 core

in vec2 TexCoord;
in vec3 Normal;
in vec3 FragPos; 
in vec4 vertLightPos;

out vec4 FragColor;

uniform sampler2D tex;
uniform sampler2D depthTex;

uniform vec3 lightDir;
uniform vec3 color;
uniform float intensity;
uniform vec3 viewPos; 

float ambientStrength = 0.1f;
float shininess = 32.0f;

void main() {


    vec3 norm = normalize(Normal);
    vec3 lightDirNorm = normalize(lightDir);
    
    vec3 viewDir = normalize(viewPos - FragPos); 
    vec3 toLightDir = -lightDirNorm;
    vec3 halfwayDir = normalize(toLightDir + viewDir);

    float diff = max(dot(norm, toLightDir), 0.0);
    float spec = pow(max(dot(norm, halfwayDir), 0.0), shininess);

    vec3 ambient = color * ambientStrength;
    vec3 diffuse = color * diff;
    vec3 specular = color * spec;

    vec3 lighting = ambient + diffuse + specular;
    vec4 textureColor = texture(tex, TexCoord);

    vec3 ndc = vertLightPos.xyz/vertLightPos.w;
    vec3 normalizedCoords = ndc * 0.5 + 0.5;

    float currentDepth = normalizedCoords.z;
    float shadow = 0.0;

    bool insideShadowMap =
        normalizedCoords.x >= 0.0 && normalizedCoords.x <= 1.0 &&
        normalizedCoords.y >= 0.0 && normalizedCoords.y <= 1.0 &&
        normalizedCoords.z >= 0.0 && normalizedCoords.z <= 1.0;

    if (insideShadowMap) {
        float closestDepth = texture(depthTex, normalizedCoords.xy).r;
        float bias = 0.005;
        if (currentDepth > closestDepth + bias ) {
            shadow = 0.7;
        }
        else{
            shadow = 0.0;
        }
    }

    lighting =  ambient + (1.0 - shadow) * (diffuse + specular);

    FragColor = vec4(lighting, 1.0) * textureColor * intensity;
}
