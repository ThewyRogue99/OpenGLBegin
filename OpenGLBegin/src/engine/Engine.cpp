#include "Engine.h"

float Engine::deltaTime = 0.f;

float Engine::lastFrame = 0.f;

bool Engine::init()
{
	if (glfwInit() == GLFW_FALSE)
	{
		ConsoleLog(ConsoleError, "Failed to initialize GLFW");
		return false;
	}

	//Initialize GLFW
	//OpenGL version 3.3
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	//if using MacOS
#ifdef __APPLE__
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

	return true;
}

bool Engine::initScreen(int screenWidth, int screenHeight)
{
	mainScreen = Screen(screenWidth, screenHeight);

	//Create a new window
	if (!mainScreen.init("OpenGL Tutorial"))
	{
		ConsoleLog(ConsoleError, "Failed to initialize screen");
		glfwTerminate();
		return false;
	}

	return true;
}

bool Engine::setParams()
{
	//Initialize GLAD
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		ConsoleLog(ConsoleError, "Failed to initialize GLAD");
		glfwTerminate();
		return false;
	}

	mainScreen.setParameters();
	glEnable(GL_DEPTH_TEST);

	return true;
}

float Engine::calcDeltaTime()
{
	double startFrame = glfwGetTime();
	deltaTime = startFrame - lastFrame;
	lastFrame = startFrame;

	return deltaTime;
}
