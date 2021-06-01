#pragma once

#include <GLFW/glfw3.h>

class Keyboard
{
public:

	static void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);

	static bool key(int key);
	static bool keyChanged(int key);
	static bool keyWentUp(int key);
	static bool keyWentDown(int key);
	static bool keyToggle(int key);

private:
	static bool keys[];
	static bool keysChanged[];
	static bool toggleKeys[];
};