#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

class Keyboard
{
public:
	// ket state call back
	static void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);

	// access

	static bool key(int key);
	static bool keyChanged(int key);
	static bool keyWentUp(int key);
	static bool keyWentDown(int key);

private:
	static bool keys[];
	static bool key_changed[];
};

