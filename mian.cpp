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


int width = 800;
int height = 600;

void processInput(GLFWwindow* window);
void framebufferSizeCB(GLFWwindow* window, int width, int height);


int main()
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	auto windows = glfwCreateWindow(width, height, "trangle", NULL, NULL);

	glfwMakeContextCurrent(windows);
	glfwSetFramebufferSizeCallback(windows, framebufferSizeCB);
	gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);

	// shader

	Shader shader = { "shader/vertex_shader.glsl", "shader/fragment_shader.glsl" };

	float vertices[] = {
		// position				// colors
		-0.25f,	 -0.5f,	 0.0f,		1.0f,	 1.0f,	 0.5f,
		0.15f,	 0.0f,	 0.0f,		0.5f,	 1.0f,	 0.4f,
		0.0f,	 0.5f,	 0.0f,		0.8f,	 1.0f,	0.0f,
		0.5f,	 -0.4f,	 0.0f,		1.0f,	1.0f,	0.5f
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
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 6, (void*)0);
	glEnableVertexAttribArray(0);

	// colors
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 6, (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	auto trans_matrix = glm::mat4(1.0f);


	while (!glfwWindowShouldClose(windows))
	{
		// render here
		processInput(windows);

		glClear(GL_COLOR_BUFFER_BIT);

		trans_matrix = glm::rotate(trans_matrix, glm::radians((float)glfwGetTime() / 100.0f), glm::vec3(0, 0, 1.0f));
		shader.active();
		shader.setMat4("transform", trans_matrix);

		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

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