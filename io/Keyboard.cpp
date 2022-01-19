#include "Keyboard.h"
bool Keyboard::keys[GLFW_KEY_LAST] = {0};
bool Keyboard::key_changed[GLFW_KEY_LAST] = { 0 };


void Keyboard::keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (action != GLFW_RELEASE) // action == GLFW_PRESS | action == GLFW_REPEAT
	{
		if (!keys[key])
		{
			keys[key] = true;
		}
	}
	else // action == GLFW_RELEASE --> release
	{
		keys[key] = false;
	}
	key_changed[key] = action != GLFW_REPEAT;
}

bool Keyboard::key(int key)
{
	return keys[key];
}

bool Keyboard::keyChanged(int key)
{
	auto ret = key_changed[key];
	key_changed[key] = false;

	return ret;
}

bool Keyboard::keyWentUp(int key)
{
	return !keys[key] && keyChanged(key);
}

bool Keyboard::keyWentDown(int key)
{
	return keys[key] && keyChanged(key);
}
