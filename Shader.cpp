#include "Shader.h"

Shader::Shader(const char* vertex_shader_path, const char* fragment_shader_path)
{
	int success;
	char log_info[512];

	unsigned int vertex_shader = compileShader(vertex_shader_path, GL_VERTEX_SHADER);
	unsigned int fragment_shader = compileShader(fragment_shader_path, GL_FRAGMENT_SHADER);

	this->id = glCreateProgram();
	glAttachShader(id, vertex_shader);
	glAttachShader(id, fragment_shader);

	glLinkProgram(this->id);

	glGetProgramiv(this->id, GL_LINK_STATUS, &success);
	if (!success)
	{
		glGetProgramInfoLog(id, 512, NULL, log_info);
		std::cout << "link error : " << log_info << std::endl;
	}
	
	glDeleteShader(vertex_shader);
	glDeleteShader(fragment_shader);
}

void Shader::active()
{
	glUseProgram(this->id);
}

std::string Shader::loadShaderSrc(const char* file_path)
{
	std::ifstream file;
	std::stringstream buffer;
	std::string res = "";

	file.open(file_path);
	if (file.is_open()) {
		buffer << file.rdbuf();
		res = buffer.str();
	}
	else
		std::cout << "error open file" << std::endl;

	return res;
}

unsigned int Shader::compileShader(const char* file_path, GLenum type)
{
	int success;
	char log_info[512];

	auto shader_id = glCreateShader(type);
	auto src = loadShaderSrc(file_path);
	const char* shader = src.c_str();

	glShaderSource(shader_id, 1, &shader, nullptr);
	glCompileShader(shader_id);

	glGetShaderiv(shader_id, GL_LINK_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(shader_id, 512, NULL, log_info);
		std::cout << "shader error : " << log_info << std::endl;
	}
	return shader_id;
}

void Shader::setMat4(const std::string& attr_name, glm::mat4 val)
{
	glUniformMatrix4fv(glGetUniformLocation(this->id, attr_name.c_str()), 1, GL_FALSE, glm::value_ptr(val));
}

void Shader::setInt(const std::string& attr_name, int val)
{
	 glUniform1i(glGetUniformLocation(id, attr_name.c_str()), val);
}
