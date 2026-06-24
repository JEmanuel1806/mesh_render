#version 440 core 

uniform sampler2D noiseTex;
uniform sampler2D normalTex;
uniform sampler2D posTex;

uniform vec3 samples[64]; // points to be tested
uniform mat4 proj;
uniform float radius;
uniform float bias;
uniform vec2 noiseScale;
 
in vec2 TexCoord;

out vec4 FragColor;

// to remember: storing AO value for each pixel, which will be used in lighting pass as multiplication factor for ambient
void main() {

	float aoValue = 0.0f;

	vec3 point = texture(posTex, TexCoord).xyz;
	vec3 normal = normalize(texture(normalTex, TexCoord).xyz);

	if (normal == vec3(0.0)) {
		aoValue = 1.0f;
	}
	else{
		vec3 randomVec = texture(noiseTex, TexCoord * noiseScale).xyz;
		vec3 tangent = normalize(randomVec - (normal * dot(randomVec, normal)));
		vec3 bitangent = normalize(cross(normal, tangent));
		mat3 tbn = mat3(tangent, bitangent, normal);

		for(int i = 0; i < 64; i++) {
			vec3 currentSample = samples[i];
			currentSample = point + (tbn * currentSample) * radius;

			vec4 sampleClip = proj * vec4(currentSample, 1.0);
			vec2 sampleScreen = (sampleClip.xy / sampleClip.w) * 0.5 + 0.5;

		if (sampleScreen.x < 0.0 || sampleScreen.x > 1.0 ||sampleScreen.y < 0.0 || sampleScreen.y > 1.0) 
			continue;

			float depthSample = texture(posTex, sampleScreen.xy).z;

			if (depthSample < currentSample.z){
				aoValue += 1.0f;
			}
		}
		aoValue = aoValue/64.0f;

	}

	FragColor = vec4(vec3(aoValue), 1.0);
	}