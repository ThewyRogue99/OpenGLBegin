#include <glad/glad.h>
#include <iostream>
#include <GLFW/glfw3.h>
#include "debug/debug.h"

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

#include "graphics/Object.h"
#include "graphics/Shader.h"
#include "graphics/Model.h"
#include "graphics/textures/Texture.h"
#include "graphics/models/Cube.hpp"
#include "graphics/models/Sphere.hpp"
#include "graphics/textures/TextureAtlas.h"
#include "graphics/models/Lamp.hpp"
#include "graphics/Light.h"

void processInput();

double deltaTime = 0;

unsigned int SCREEN_WIDTH = 800, SCREEN_HEIGHT = 600;

Camera camera(glm::vec3(0.f, 1.f, 5.f));

Screen screen(1024, 720);

//How to do: Go to project properties->linker->system->subsystem and change it to windows then

/*int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)*/

//Uncomment this and remove main to run the app without console

int main()
{
	std::cout << "Hello again" << std::endl;

	if (glfwInit() == GLFW_FALSE)
	{
		printError("Failed to initialize GLFW");
		return -1;
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

	//Create a new window
	screen.init("OpenGL Tutorial");

	//Initialize GLAD
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		printError("Failed to initialize GLAD");
		glfwTerminate();
		return -1;
	}

	screen.setParameters();
	glEnable(GL_DEPTH_TEST);

	/* Shaders */

	Shader mainShader("assets/object.vs", "assets/object.fs");

	/* Objects */

	Cube ground(glm::vec3(0.f, -0.5f, 0.f), glm::vec3(100.f, 1.f, 100.f));
	ground.init(Material::green_plastic);
	ground.SpawnObject();

	Model tank(glm::vec3(0.f, 0.f, 10.f));
	tank.loadModel("assets/models/t90/scene.gltf");
	tank.SpawnObject();

	Model m4a1(glm::vec3(5.f, 0.15f, -5.f), glm::vec3(0.005f), glm::vec3(-90.f, 0.f, 0.f), true);
	m4a1.loadModel("assets/models/m4a1/scene.gltf");
	m4a1.SpawnObject();

	Cube container(glm::vec3(10.f, 0.6f, -5.f));
	container.init("assets/textures/container2.png", "assets/textures/container2_specular.png");
	container.SpawnObject();

	Model troll(glm::vec3(-5.f, 1.3f, -5.f), glm::vec3(0.01f), glm::vec3(0.f));
	troll.loadModel("assets/models/lotr_troll/scene.gltf");
	troll.SpawnObject();

	Sphere sphere(glm::vec3(0.f, 5.f, 0.f), glm::vec3(0.02f));
	sphere.init();
	sphere.SpawnObject();

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

	/*Lamp lamp(
		glm::vec4(1.f), glm::vec4(1.f),
		1.f, 0.07f, 0.032f,
		glm::vec3(0.f, 1.f, 0.f), glm::vec3(0.25f)
	);
	lamp.init();*/
	
	double lastFrame = 0;
	int i = 0;

	/* Main Loop */
	while (!screen.shouldClose())
	{
		double startFrame = glfwGetTime();
		deltaTime = startFrame - lastFrame;
		lastFrame = startFrame;

		//Process incoming key inputs
		processInput();

		//Render frame
		screen.update();

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

		if (Keyboard::key(GLFW_KEY_RIGHT))
			container.rotation.y -= 20 * (float)deltaTime;
		if(Keyboard::key(GLFW_KEY_LEFT))
			container.rotation.y += 20 * (float)deltaTime;
		if (Keyboard::key(GLFW_KEY_UP))
			container.rotation.x += 20 * (float)deltaTime;
		if (Keyboard::key(GLFW_KEY_DOWN))
			container.rotation.x -= 20 * (float)deltaTime;

		Object::RenderAllObjects(mainShader);
		Object::UpdateAllObjects((float)deltaTime);

		screen.newFrame();

		printf("FPS: %i\r", (int)(1.0 / deltaTime));
	}

	Object::DestroyAllObjects();

	glfwTerminate();
	return 0;
}

void processInput()
{
	if (Keyboard::key(GLFW_KEY_ESCAPE))
		screen.setShouldClose(true);

	if (Keyboard::key(GLFW_KEY_W))
		camera.updateCameraPos(CameraDirection::FORWARD, deltaTime);
	if (Keyboard::key(GLFW_KEY_S))
		camera.updateCameraPos(CameraDirection::BACKWARD, deltaTime);
	if (Keyboard::key(GLFW_KEY_A))
		camera.updateCameraPos(CameraDirection::LEFT, deltaTime);
	if (Keyboard::key(GLFW_KEY_D))
		camera.updateCameraPos(CameraDirection::RIGHT, deltaTime);

	if (Keyboard::key(GLFW_KEY_SPACE))
		camera.updateCameraPos(CameraDirection::UP, deltaTime);
	if (Keyboard::key(GLFW_KEY_LEFT_SHIFT))
		camera.updateCameraPos(CameraDirection::DOWN, deltaTime);

	double dx = Mouse::getDX(), dy = Mouse::getDY();
	if (dx != 0 || dy != 0)
		camera.updateCameraDirection(dx * deltaTime, dy * deltaTime);

	double scrollDY = Mouse::getScrollDY();
	if (scrollDY != 0)
		camera.updateCameraZoom(scrollDY);
}