#include "Mouse.h"

double Mouse::x = 0;
double Mouse::y = 0;

double Mouse::lastX = 0;
double Mouse::lastY = 0;

double Mouse::dx = 0;
double Mouse::dy = 0;

double Mouse::scrollDX = 0;
double Mouse::scrollDY = 0;


bool Mouse::first_mouse = true;

bool Mouse::buttons[GLFW_MOUSE_BUTTON_LAST] = {0};

bool Mouse::button_changed[GLFW_MOUSE_BUTTON_LAST] = { 0 };



void Mouse::cursorPosCallback(GLFWwindow* window, double _x, double _y)
{
	x = _x;
	y = _y;

	if (first_mouse)
	{
		lastX = x;
		lastY = y;

		first_mouse = false;
	}

	dx = x - lastX;
	dy = y - lastY;

	lastX = x;
	lastY = y;
}

void Mouse::mouseButtonCallback(GLFWwindow* window, int button, int action, int mods)
{
	if (action != GLFW_RELEASE)
	{
		if (!buttons[button])
		{
			buttons[button] = true;
		}
	}
	else
	{
		buttons[button] = false;
	}

	button_changed[button] = action != GLFW_REPEAT;
}

void Mouse::mouseWheelCallback(GLFWwindow* window, double dx, double dy)
{
	scrollDX = dx;
	scrollDY = dy;
}

double Mouse::getMouseX()
{
	return x;
}

double Mouse::getMouseY()
{
	return y;
}

double Mouse::getDX()
{
	double _dx = dx;
	dx = 0;

	return _dx;
}

double Mouse::getDY()
{
	double _dy = dy;
	dy = 0;

	return _dy;
}

double Mouse::getScrollX()
{
	double _dx = scrollDX;
	scrollDX = 0;

	return _dx;
}

double Mouse::getScrollY()
{
	double _dy = scrollDY;
	scrollDY = 0;

	return _dy;
}

bool Mouse::button(int button)
{
	return buttons[button];
}

bool Mouse::buttonChanged(int button)
{
	bool ret = button_changed[button];
	button_changed[button] = false;

	return ret;
}

bool Mouse::buttonWentUp(int button)
{
	return !buttons[button] && buttonChanged(button);
}

bool Mouse::buttonWentDown(int button)
{
	return buttons[button] && buttonChanged(button);
}

