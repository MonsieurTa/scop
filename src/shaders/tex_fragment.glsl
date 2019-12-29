#version 410 core

in vec3 colour;
in vec2 texturePos;
out vec4 FragColor;

uniform sampler2D texture1;
uniform sampler2D texture2;
uniform float			blend;

void main()
{
	FragColor = mix(texture(texture1, texturePos), texture(texture2, texturePos), blend);
}
