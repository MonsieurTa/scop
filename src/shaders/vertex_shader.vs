#version 410 core

layout (location = 0) in vec3 v_pos;
layout (location = 1) in vec3 v_colour;

uniform vec3	offset;

out vec3 colour;

void main()
{
	colour = v_colour;
	gl_Position = vec4((v_pos + offset), 1.0f);
}
