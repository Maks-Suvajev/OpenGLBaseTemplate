// System access
#include <iostream>
#include <filesystem>
#define WIN32_LEAN_AND_MEAN
#include <windows.h>

// GL maths library
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>



// Custom modules
#include "Shader.h"
#include "GfxAssets.h"
#include "Window.h"
#include "Renderer.h"
#include "Cube.h"

int main()
{
	gfx::GfxAssets * gfxAssetsModule = new gfx::GfxAssets();

	std::vector<std::filesystem::path> texturePathsFound = gfxAssetsModule->getTexturePaths();

	for (auto path : texturePathsFound)
	{
		std::cout << "Path found: " << path.string() << std::endl;
	}

	gfx::Window * window = new gfx::Window("Da Window");

	std::cout << "Frag shader path = " << gfxAssetsModule->getFragShaderPath().string() << std::endl;
	std::cout << "Vert shader path = " << gfxAssetsModule->getVertShaderPath().string() << std::endl;


	gfx::Shader * shaderModule = new gfx::Shader(gfxAssetsModule->getFragShaderPath().string(), gfxAssetsModule->getVertShaderPath().string());

	// OBJECT MANAGER -----------------------------------
	glm::vec3 cubePositions[] = {
		glm::vec3(0.0f,  0.0f,  0.0f),
		glm::vec3(2.0f,  5.0f, -15.0f),
		glm::vec3(-1.5f, -2.2f, -2.5f),
		glm::vec3(-3.8f, -2.0f, -12.3f),
		glm::vec3(2.4f, -0.4f, -3.5f),
		glm::vec3(-1.7f,  3.0f, -7.5f),
		glm::vec3(1.3f, -2.0f, -2.5f),
		glm::vec3(1.5f,  2.0f, -2.5f),
		glm::vec3(1.5f,  0.2f, -1.5f),
		glm::vec3(-1.3f,  1.0f, -1.5f)
	};

	gfx::VAOGroupData<glm::vec3> initData;

	initData.vertices = std::vector<float>(std::begin(gfx::cubeVertices), std::end(gfx::cubeVertices));
	initData.indices = std::vector<unsigned int>(std::begin(gfx::cubeIndices), std::end(gfx::cubeIndices));

	for (const auto& cubePosition : cubePositions)
	{
		gfx::PositionAndTextureInstance newInstance(cubePosition, std::vector<uint32_t>({0, 1}));

		initData.instanceData.push_back(std::move(newInstance));
	}

	//VAO Init Data needs to be a vector (We're assuming we will usually be using more than one VAOGroup)

	auto VAOGroupDataVec = std::vector<gfx::VAOGroupData<glm::vec3>>{initData};

	gfx::Renderer<glm::vec3> * renderModule = new gfx::Renderer<glm::vec3>(std::move(VAOGroupDataVec), std::move(texturePathsFound), *shaderModule);


// 	// Send all of the transformations to shader uniform data

	// Render loop
	while (!glfwWindowShouldClose(window->getGlfwWindow()))
	{
		window->processKeyboardInput();

		glfwPollEvents();

		window->clearScreen();

		shaderModule->updateViewMatrixValue(window->getCameraInstance()->calculateViewMatrix());

		shaderModule->updateProjectionMatrixValue(window->getCameraInstance()->calculateProjectionMatrix());

		renderModule->drawScene(*shaderModule, *window);

		glfwSwapBuffers(window->getGlfwWindow());

	}

	glfwTerminate();

	return 0;

}



// 		// assetManager module
// 		for (uint8_t i = 0; i < 10; i++)
// 		{
// 			glm::mat4 model = glm::mat4(1.0f);

// 			model = glm::translate(model, cubePositions[i]);


// 			float angle = 0;

// 			if (i == 0 || i % 3 == 0)
// 			{

// 				angle = 20.0f * i * (float)glfwGetTime();


// 			}
// 			else
// 			{
// 				angle = 20.0f * i;

// 			}

// 			model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));

// 			shaderModule->updateModelMatrixValue(model);

// 			glDrawArrays(GL_TRIANGLES, 0, 36);

// 		}