#version 460 core

in vec3 outColor;
in vec2 texCoord;

out vec4 FragColor;

uniform sampler2D tex;

void main()
{
	// FragColor = vec4(outColor, 1.0f);

	//						ÌùÍ¼£¬ uv×ø±ê
	FragColor = texture2D(tex, texCoord);
}