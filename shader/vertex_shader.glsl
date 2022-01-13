#version 460 core

layout (location = 0) in vec3 pos;
layout (location = 1) in vec3 color;

out vec3 outColor;

uniform mat4 transform;

void main()
{
	gl_Position = transform * vec4(pos, 1.0f);
	outColor = color;
}