#version 410 core

in vec3 colour;
in vec2 texturePos;
out vec4 FragColor;

uniform sampler2D ourTexture;

void main()
{
	FragColor = texture(ourTexture, texturePos);
	// FragColor = vec4(colour, 1.0f);
}
