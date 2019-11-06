#version 410 core

layout (location = 0) in vec3 v_pos;
layout (location = 1) in vec3 v_colour;
layout (location = 2) in vec2 v_texture;

uniform vec3	offset;

out vec3 colour;
out vec2 texturePos;

void main()
{
	gl_Position = vec4((v_pos + offset), 1.0f);
	colour = v_colour;
	texturePos = v_texture;
}
