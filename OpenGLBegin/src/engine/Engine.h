#pragma once
#include "../io/Screen.h"
#include "../graphics/Shader.h"
#include "../io/Camera.h"

class Engine
{
public:
	Engine() { }

	bool init();

	bool initScreen(int screenWidth, int screenHeight);

	bool setParams();

	float calcDeltaTime();

	static float GetDeltaTime() { return deltaTime; }

	Screen mainScreen;
	Shader mainShader;
	Camera mainCamera;

private:
	static float deltaTime;

	static float lastFrame;
};