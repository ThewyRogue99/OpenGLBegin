#include <glad/glad.h>
#include <iostream>
#include <GLFW/glfw3.h>
#include "io/debug.h"

#include <fstream>
#include <string>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <stb/stb_image.h>

#include "io/Keyboard.h"
#include "io/Mouse.h"
#include "io/Camera.h"
#include "io/Screen.h"

#include "graphics/Shader.h"
#include "graphics/Model.h"
#include "graphics/textures/Texture.h"
#include "graphics/models/Cube.hpp"
#include "graphics/models/Sphere.hpp"
#include "graphics/textures/TextureAtlas.h"
#include "graphics/models/Lamp.hpp"
#include "graphics/Light.h"

#include "engine/Object.h"
#include "engine/Engine.h"

void processInput();

unsigned int SCREEN_WIDTH = 1024, SCREEN_HEIGHT = 720;

Camera camera(glm::vec3(0.f, 0.f, 5.f));

//How to do: Go to project properties->linker->system->subsystem and change it to windows then

/*int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)*/

//Uncomment this and remove main to run the app without console

Engine engine;

int main()
{
	engine.init();

	engine.initScreen(SCREEN_WIDTH, SCREEN_HEIGHT);

	engine.setParams();

	/* Shaders */

	Shader mainShader("assets/object.vs", "assets/object.fs");

	/* Objects */

	SpotLight spotLight = SpotLight(
		camera.cameraPos, camera.cameraFront,
		20.f,
		1.f, 0.07f, 0.032f,
		glm::vec4(0.f, 0.f, 0.f, 1.f), glm::vec4(1.f), glm::vec4(0.f, 0.f, 0.f, 1.f)
	);
	spotLight.SpawnObject();

	Lamp sun(
		glm::vec4(1.f), glm::vec4(1.f),
		1.f, 0.0f, 0.0f,
		glm::vec3(0.f, 100.f, 100.f), glm::vec3(0.25f)
	);
	sun.init();
	sun.SpawnObject();

	/* Main Loop */
	while (!engine.mainScreen.shouldClose())
	{
		engine.calcDeltaTime();

		//Process incoming key inputs
		processInput();

		//Render frame
		engine.mainScreen.update();

		mainShader.Activate();
		mainShader.set3Float("viewPos", camera.cameraPos);

		//Create transformations
		glm::mat4 view = camera.getViewMatrix();
		glm::mat4 projection = glm::perspective(glm::radians(camera.zoom), (float)SCREEN_WIDTH / (float)SCREEN_HEIGHT, 0.1f, 100.f);

		mainShader.setMat4("view", view);
		mainShader.setMat4("projection", projection);

		// Render objects

		if (Keyboard::keyToggle(GLFW_KEY_F))
		{
			if (Mouse::button(GLFW_MOUSE_BUTTON_RIGHT))
				spotLight.width = 10.f;
			else
				spotLight.width = 20.f;

			spotLight.diffuse = glm::vec4(1.f);
			spotLight.specular = glm::vec4(1.f);
		}
		else
		{
			spotLight.diffuse = glm::vec4(0.f, 0.f, 0.f, 1.f);
			spotLight.specular = glm::vec4(0.f, 0.f, 0.f, 1.f);
		}

		spotLight.position = camera.cameraPos;
		spotLight.direction = camera.cameraFront;

		Object::RenderAllObjects(mainShader);

		engine.mainScreen.newFrame();

		//printf("FPS: %i\r", (int)(1.0 / deltaTime));
	}

	Object::DestroyAllObjects();

	glfwTerminate();
	return 0;
}

void processInput()
{
	// Screen should close
	if (Keyboard::key(GLFW_KEY_ESCAPE))
		engine.mainScreen.setShouldClose(true);

	// Camera Movement
	if (Keyboard::key(GLFW_KEY_W))
		camera.updateCameraPos(CameraDirection::FORWARD);
	if (Keyboard::key(GLFW_KEY_S))
		camera.updateCameraPos(CameraDirection::BACKWARD);
	if (Keyboard::key(GLFW_KEY_A))
		camera.updateCameraPos(CameraDirection::LEFT);
	if (Keyboard::key(GLFW_KEY_D))
		camera.updateCameraPos(CameraDirection::RIGHT);

	if (Keyboard::key(GLFW_KEY_SPACE))
		camera.updateCameraPos(CameraDirection::UP);
	if (Keyboard::key(GLFW_KEY_LEFT_SHIFT))
		camera.updateCameraPos(CameraDirection::DOWN);

	// Camera view movement
	double dx = Mouse::getDX(), dy = Mouse::getDY();
	if (dx != 0 || dy != 0)
		camera.updateCameraDirection(dx, dy);

	double scrollDY = Mouse::getScrollDY();
	if (scrollDY != 0)
		camera.updateCameraZoom(scrollDY);

	if (Keyboard::keyWentDown(GLFW_KEY_L))
	{
		Cube* cube = new Cube(Camera::defaultCamera->cameraFront);
		cube->init("assets/textures/container2.png");
		cube->SpawnObject();
		cube->rigidbody.ApplyImpulse(Camera::defaultCamera->cameraFront, 1000.f);
	}
}