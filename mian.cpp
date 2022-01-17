#include <iostream>
#include <fstream>
#include <sstream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#include "Shader.h"


const int WIDTH = 800;
const int HEIGHT = 600;

void processInput(GLFWwindow* window);
void framebufferSizeCB(GLFWwindow* window, int width, int height);


int main()
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	auto windows = glfwCreateWindow(WIDTH, HEIGHT, "trangle", NULL, NULL);

	glfwMakeContextCurrent(windows);
	glfwSetFramebufferSizeCallback(windows, framebufferSizeCB);
	gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);

	// shader
	Shader shader = { "shader/vertex_shader.glsl", "shader/fragment_shader.glsl" };
	//Shader second_trangle_shader = { "shader/vertex_shader.glsl", "shader/fragment_shader_2.glsl" };

	float vertices[] = {
		// position					 colors					texture coordinates
		-0.5f,	 -0.5f,	 0.0f,		1.0f,	 1.0f,	 0.5f,	0.0f, 0.0f, // buttom left
		-0.5f,	 0.5f,	 0.0f,		0.5f,	 1.0f,	 0.4f,	0.0f, 1.0f, // top left
		0.5f,	 -0.5f,	 0.0f,		0.8f,	 1.0f,	0.0f,	1.0f, 0.0f, // buttom right
		0.5f,	 0.5f,	 0.0f,		1.0f,	1.0f,	0.5f,	1.0f, 1.0f// top right
	};

	unsigned int indeices[] = {
		0, 1, 2,		// first trangle
		3, 1, 2			// second trangle
	};

	unsigned int vertex_array_object, vertex_buffer_object, element_buffer_object;

	glGenVertexArrays(1, &vertex_array_object);
	glGenBuffers(1, &vertex_buffer_object);
	glGenBuffers(1, &element_buffer_object);

	// bind vao	
	glBindVertexArray(vertex_array_object);

	// bind vbo and assign data
	glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer_object);

	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	// setup ebo
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, element_buffer_object);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indeices), indeices, GL_STATIC_DRAW);

	// set attribute  pointer
	// positions
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 8, (void*)0);
	glEnableVertexAttribArray(0);

	// colors
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 8, (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	// textures cooridnates
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 8, (void*)(6 * sizeof(float)));
	glEnableVertexAttribArray(2);

	// texture
	/*

		   Shder             texture units
								┌──────┐
								│      │
  uniform simple 2D tex_1 ──────┤► 0   ├──────►tex_1
								├──────┤
								│      │
  uniform simple 2D tex_2 ──────┼─►1   ├──────►tex_1
								├──────┤
								│  2   │
								└──────┘
	*/

	unsigned int texture_1, texture_2;

	glGenTextures(1, &texture_1);

	// 设置重复方式及纹理映射方式
	//	s --> x, t --> y, r --> z
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	// load image
	int width, height, channels;
	stbi_set_flip_vertically_on_load(true);
	unsigned char* image_1 = stbi_load("resources/tex_1.jpg", &width, &height, &channels, 0);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image_1);
	glGenerateMipmap(GL_TEXTURE_2D);
	stbi_image_free(image_1);

	// another texture
	glGenTextures(1, &texture_2);
	glBindTexture(GL_TEXTURE_2D, texture_2);
	unsigned char* image_2 = stbi_load("resources/tex_2.jpg", &width, &height, &channels, 0);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image_2);
	glGenerateMipmap(GL_TEXTURE_2D);
	stbi_image_free(image_2);

	shader.active();
	shader.setInt("tex_1", 0);
	shader.setInt("tex_2", 1);

	while (!glfwWindowShouldClose(windows))
	{
		// render here
		processInput(windows);

		glClear(GL_COLOR_BUFFER_BIT);

		// 注意 比如如此的书写 分别激活当前所使用的shader 然后 绑定视图
		// auto trans_matrix = glm::mat4(1.0f);
		// trans_matrix = glm::rotate(trans_matrix, glm::radians((float)glfwGetTime() / 100.0f), glm::vec3(0, 0, 1.0f));
		// first_trangle_shader.active();
		// first_trangle_shader.setMat4("transform", trans_matrix);
		// second_trangle_shader.active();
		// second_trangle_shader.setMat4("transform", trans_matrix);

		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, texture_1);

		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, texture_2);

		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, (void*)0);

		//second_trangle_shader.active();
		//glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, (void*)(sizeof(unsigned int) * 3));

		glfwSwapBuffers(windows);
		glfwPollEvents();
	}
	glfwTerminate();
	return 0;
}

void processInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
}
void framebufferSizeCB(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}