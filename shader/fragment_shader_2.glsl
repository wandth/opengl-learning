#version 460 core

layout (location = 0) out vec4 FragColor;
in vec3 outColor;

void main()
{
	FragColor = vec4(0.5f, 0.82f, 0.11f, 1.0f);
}