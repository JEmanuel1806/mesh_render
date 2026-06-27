#version 440 core 

uniform sampler2D ssaoBlurTex;
uniform sampler2D colorTex;
uniform sampler2D normalTex;
uniform sampler2D posTex;
uniform sampler2D depthTex;
uniform sampler2D shadowTex;

uniform mat4 invView;
uniform mat4 lightView;
uniform mat4 lightProj;

in vec2 TexCoord;

uniform vec3 lightDir;
uniform vec3 color;
uniform float intensity;

float ambientStrength = 0.1f;
float shininess = 32.0f;

float shadowBias = 0.005;

out vec4 FragColor;

void main(){

    vec3 pos = texture(posTex, TexCoord).xyz; 
    vec3 norm = normalize(texture(normalTex, TexCoord).xyz);
    float depthScene = texture(depthTex, TexCoord).r;
    vec3 alb = texture(colorTex, TexCoord).xyz;
    float ao = texture(ssaoBlurTex, TexCoord).r;

    // Cubemap unaffected by shadow and stuff
    if (depthScene == 1.0) {
        FragColor = texture(colorTex, TexCoord);
    return;
    }


    vec3 lightDirNorm = normalize(lightDir);
    vec3 viewDir = normalize(-pos);
    vec3 toLightDir = -lightDirNorm;
    vec3 halfwayDir = normalize(toLightDir + viewDir);

    float diff = max(dot(norm, toLightDir), 0.0);
    float spec = pow(max(dot(norm, halfwayDir), 0.0), shininess);

    vec3 ambient = alb * color * ambientStrength * ao;
    vec3 diffuse = alb * color * diff;
    vec3 specular = color * spec;

    float shadow = 0.0;
    
    vec4 worldPos = invView * vec4(pos, 1.0);

    vec4 lightPos = lightProj * lightView * worldPos;
    vec3 lightNDC = lightPos.xyz / lightPos.w;
    vec2 lightCoord = lightNDC.xy * 0.5 + 0.5;
    float lightDist = lightNDC.z * 0.5 + 0.5;

    bool insideShadowMap =
    lightCoord.x >= 0.0 && lightCoord.x <= 1.0 &&
    lightCoord.y >= 0.0 && lightCoord.y <= 1.0;

     // pcf 
    if (insideShadowMap){
    for(int x = -2; x <= 2; x++) {
        for(int y = -2; y <= 2; y++) {
            if(texture(shadowTex, lightCoord + vec2(x,y) * (1.0 / vec2(textureSize(shadowTex, 0)))).r + shadowBias < lightDist ) {
                shadow+= 0.7;
            }
        }
    }

    shadow /= 25.0;
    }


    vec3 lighting = ambient + (1.0 - shadow) * (diffuse + specular);

    FragColor = vec4(lighting * intensity, 1.0);
    // FragColor = texture(ssaoBlurTex, TexCoord);

}
