#version 440 core 

uniform sampler2D ssaoBlurTex;
uniform sampler2D colorTex;

in vec2 TexCoord;
in vec3 Normal;
in vec3 FragPos;
in vec4 vertLightPos;

uniform vec3 lightDir;
uniform vec3 color;
uniform float intensity;
uniform vec3 viewPos;

uniform sampler2D tex;
uniform sampler2D depthTex;

float ambientStrength = 0.1f;
float shininess = 32.0f;

out vec4 FragColor;

void main(){

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

    vec4 textureColor = texture(tex, TexCoord);

    vec3 ndc = vertLightPos.xyz / vertLightPos.w;
    vec3 normalizedCoords = ndc * 0.5 + 0.5;

    float currentDepth = normalizedCoords.z;
    float shadow = 0.0;

    
    bool insideShadowMap =
        normalizedCoords.x >= 0.0 && normalizedCoords.x <= 1.0 &&
        normalizedCoords.y >= 0.0 && normalizedCoords.y <= 1.0 &&
        normalizedCoords.z >= 0.0 && normalizedCoords.z <= 1.0;

    if (insideShadowMap){
        float bias = 0.005;
        vec2 texelSize = 1.0 / vec2(textureSize(depthTex, 0));

        // 5x5 kernel
        for (int i = -2; i <= 2; ++i){
            for (int j = -2; j <= 2; ++j){

                float closestDepth = texture(depthTex,normalizedCoords.xy + vec2(i, j) * texelSize).r;

                if (currentDepth > closestDepth + bias){
                    shadow += 1.0;
                }
            }
        }

        shadow /= 25.0;
    }

    FragColor = vec4(lighting, 1.0) * textureColor * intensity;

}