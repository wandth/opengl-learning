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

#include "io/Keyboard.h"
#include "io/Mouse.h"
#include "io/JoyStick.h"


unsigned int SCREEN_WIDTH = 800;
unsigned int SCREEN_HEIGHT = 600;

float x, y, z;

void processInput(GLFWwindow* window);
void framebufferSizeCB(GLFWwindow* window, int width, int height);

float mix_value = 1.0f;

auto transform = glm::mat4(1.0f);
//Joystick main_joy_stick(0);

int main()
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	auto window = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "trangle", NULL, NULL);

	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebufferSizeCB);

	glfwSetKeyCallback(window, Keyboard::keyCallback);
	glfwSetCursorPosCallback(window, Mouse::cursorPosCallback);
	glfwSetMouseButtonCallback(window, Mouse::mouseButtonCallback);
	glfwSetScrollCallback(window, Mouse::mouseWheelCallback);
	gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);


	glViewport(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);

	glEnable(GL_DEPTH_TEST);

	// shader
	Shader shader = { "shader/vertex_shader.glsl", "shader/fragment_shader.glsl" };
	//Shader second_trangle_shader = { "shader/vertex_shader.glsl", "shader/fragment_shader_2.glsl" };

	//float vertices[] = {
	//	// position					 colors					texture coordinates
	//	-0.5f,	 -0.5f,	 0.0f,		1.0f,	 1.0f,	 0.5f,	0.0f, 0.0f, // buttom left
	//	-0.5f,	 0.5f,	 0.0f,		0.5f,	 1.0f,	 0.4f,	0.0f, 1.0f, // top left
	//	0.5f,	 -0.5f,	 0.0f,		0.8f,	 1.0f,	0.0f,	1.0f, 0.0f, // buttom right
	//	0.5f,	 0.5f,	 0.0f,		1.0f,	1.0f,	0.5f,	1.0f, 1.0f// top right
	//};
	float vertices[] = {
	// position				// uv
	-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
	 0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
	 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

	-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
	 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
	 0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
	 0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
	-0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
	-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

	-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
	-0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
	-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

	 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
	 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	 0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	 0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	 0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
	 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

	-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	 0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
	 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
	 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
	-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

	-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
	 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
	 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
	-0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
	-0.5f,  0.5f, -0.5f,  0.0f, 1.0f
	};

	unsigned int vertex_array_object, vertex_buffer_object;

	glGenVertexArrays(1, &vertex_array_object);
	glGenBuffers(1, &vertex_buffer_object);
	//glGenBuffers(1, &element_buffer_object);

	// bind vao	
	glBindVertexArray(vertex_array_object);

	// bind vbo and assign data
	glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer_object);

	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	// setup ebo
	//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, element_buffer_object);
	//glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indeices), indeices, GL_STATIC_DRAW);

	// set attribute  pointer
	// positions
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 5, (void*)0);
	glEnableVertexAttribArray(0);

	// colors
	//glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 8, (void*)(3 * sizeof(float)));
	//glEnableVertexAttribArray(1);

	// textures cooridnates
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 5, (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	// texture

	unsigned int texture_1, texture_2;

	glGenTextures(1, &texture_1);
	glBindTexture(GL_TEXTURE_2D, texture_1);
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


	auto trans_matrix = glm::mat4(1.0f);
	trans_matrix = glm::rotate(trans_matrix, glm::radians(45.0f), glm::vec3(1.0f, 0.0f, 0.0f));
	trans_matrix = glm::rotate(trans_matrix, glm::radians(45.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	shader.active();
	shader.setMat4("transform", trans_matrix);


	// 此项更改的是相机的位置 也就是物体始终在原地自旋转，，但是我们更改了相机的位置
	x = 0.0f;
	y = 0.0f;
	z = 3.0f;

	while (!glfwWindowShouldClose(window))
	{
		// render here
		processInput(window);
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// 注意 比如如此的书写 分别激活当前所使用的shader 然后 绑定视图
		shader.active();
		shader.setInt("tex_1", 0);
		shader.setInt("tex_2", 1);

		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, texture_1);
		
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, texture_2);

		// create transform for screen
		glm::mat4 model = glm::mat4(1.0f);
		glm::mat4 view = glm::mat4(1.0f);
		glm::mat4 projection = glm::mat4(1.0f);


		model = glm::rotate(model, (float)glfwGetTime() * glm::radians(-55.0f), glm::vec3(0.5f, 0.5f, 0.5f));
		view = glm::translate(view, glm::vec3(-x, -y, -z));
		projection = glm::perspective(glm::radians(45.0f), (float)SCREEN_WIDTH / (float)SCREEN_HEIGHT,0.1f,  100.0f);


		shader.active();
		shader.setMat4("model", model);
		shader.setMat4("view", view);
		shader.setMat4("projection", projection);

		shader.setFloat("mix_value", mix_value);

		glDrawArrays(GL_TRIANGLES, 0, 36);


		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	glfwTerminate();
	return 0;
}

void processInput(GLFWwindow* window)
{
	if (Keyboard::key(GLFW_KEY_ESCAPE))
		glfwSetWindowShouldClose(window, true);

	// change mix value
	//if (Keyboard::key(GLFW_KEY_UP))
	//{
	//	mix_value += 0.01f;
	//	if (mix_value > 1)
	//	{
	//		mix_value = 1.0f;
	//	}
	//}
	//if (Keyboard::key(GLFW_KEY_DOWN))
	//{
	//	mix_value -= 0.01f;
	//	if (mix_value < 0)
	//	{
	//		mix_value = 0.0f;
	//	}
	//}
	if (Keyboard::key(GLFW_KEY_W))
	{
		y -= 0.01f;
	}
	if (Keyboard::key(GLFW_KEY_S))
	{
		y += 0.01f;
	}
	if (Keyboard::key(GLFW_KEY_A))
	{
		x += 0.01f;
	}
	if (Keyboard::key(GLFW_KEY_D))
	{
		x -= 0.01f;
	}
	if (Keyboard::key(GLFW_KEY_UP))
	{
		z -= 0.01f;
	}
	if (Keyboard::key(GLFW_KEY_DOWN))
	{
		z += 0.01f;
	}
}
void framebufferSizeCB(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);

	SCREEN_WIDTH = width;
	SCREEN_HEIGHT = height;

}