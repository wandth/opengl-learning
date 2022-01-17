#version 460 core

in vec3 outColor;
in vec2 texCoord;

out vec4 FragColor;

uniform sampler2D tex_1;
uniform sampler2D tex_2;

void main()
{
	// FragColor = vec4(outColor, 1.0f);

	//						ÌùÍ¼£¬ uv×ø±ê
	// FragColor = mix(texture(tex_1, texCoord), texture(tex_2, texCoord), 0.5);
	FragColor = texture(tex_1, texCoord);
}