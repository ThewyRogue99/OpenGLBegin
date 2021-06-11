#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

class Screen
{
public:
	static unsigned int width;
	static unsigned int height;

	Screen() { window = nullptr; }
	Screen(unsigned int width, unsigned int height);

	void setup(unsigned int _width, unsigned int _height);

	bool init(const char* title = "Screen");

	void setParameters();

	void update();
	void newFrame();

	bool shouldClose();
	void setShouldClose(bool shouldClose);

protected:
	GLFWwindow* window;

	static void framebuffer_size_callback(GLFWwindow* window, int _width, int _height);
};

