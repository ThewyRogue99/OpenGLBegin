#include "Screen.h"

#include "Keyboard.h"
#include "Mouse.h"

unsigned int Screen::width = 0;
unsigned int Screen::height = 0;

void Screen::framebuffer_size_callback(GLFWwindow* window, int _width, int _height)
{
	glViewport(0, 0, _width, _height);
	width = _width;
	height = _height;
}

Screen::Screen(unsigned int _width, unsigned int _height)
{
	setup(_width, _height);
}

void Screen::setup(unsigned int _width, unsigned int _height)
{
	width = _width;
	height = _height;
	window = nullptr;
}

bool Screen::init(const char* title)
{
	window = glfwCreateWindow(width, height, title, NULL, NULL);
	if (!window) { return false; }

	glfwMakeContextCurrent(window);
	return true;
}

void Screen::setParameters()
{
	glViewport(0, 0, width, height);

	//Register callbacks
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	glfwSetKeyCallback(window, Keyboard::keyCallback);

	glfwSetCursorPosCallback(window, Mouse::cursorPosCallback);
	glfwSetMouseButtonCallback(window, Mouse::mouseButtonCallback);
	glfwSetScrollCallback(window, Mouse::mouseWheelCallback);

	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
}

void Screen::update()
{
	// 0.2f, 0.3f, 0.3f
	glClearColor(0.7f, 0.7f, 0.7f, 1.f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Screen::newFrame()
{
	glfwSwapBuffers(window);
	glfwPollEvents();
}

bool Screen::shouldClose()
{
	return glfwWindowShouldClose(window);
}

void Screen::setShouldClose(bool shouldClose)
{
	glfwSetWindowShouldClose(window, shouldClose);
}