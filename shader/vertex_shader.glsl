#version 460 core

layout (location = 0) in vec3 pos;
layout (location = 1) in vec3 color;
layout (location = 2) in vec2 tex_coordinate;

// out color to fragment shader
out vec3 outColor;
out vec2 texCoord;
uniform mat4 transform;

void main()
{
	// gl_Position = transform * vec4(pos, 1.0f);
	gl_Position =  vec4(pos, 1.0f);
	outColor = color;
	texCoord = tex_coordinate;
}