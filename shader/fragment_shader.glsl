#version 460 core

in vec3 outColor;
in vec2 texCoord;

out vec4 FragColor;

uniform sampler2D tex_1;
uniform sampler2D tex_2;

uniform float mix_value;

void main()
{
	// FragColor = vec4(outColor, 1.0f);

	//						??ͼ?? uv????
	FragColor = mix(texture(tex_1, texCoord), texture(tex_2, texCoord), mix_value);
	// FragColor = texture(tex_1, texCoord);
}