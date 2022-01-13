#pragma once

#include <glad/glad.h>
#include <sstream>
#include <string>
#include <fstream>
#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>

class Shader
{
public:
	unsigned int id;

public:
	Shader(const char* vertex_shader_path, const char* fragment_shader_path);

	void active();
	void setMat4(const std::string& attr_name, glm::mat4 val);


private:
	std::string loadShaderSrc(const char* file_path);
	unsigned int compileShader(const char* file_path, GLenum type);

};

