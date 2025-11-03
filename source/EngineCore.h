#ifndef ENGINE_CORE_H
#define ENGINE_CORE_H

// System includes
#include <memory> //For pointers
#include "GfxAssets.h"
#include "Window.h"
#include "Shader.h"
#include "Renderer.h"

// Vertices and test positions for cube
#include "Cube.h"

// use glm::vec3 for 3D and glm::vec2 for 2D
template<typename T>
class EngineCore
{

    public:
        EngineCore();
        void runLoop();

    private:

        std::unique_ptr<gfx::GfxAssets>     gfxAssetsModule;
        std::unique_ptr<gfx::Window>        windowModule;
        std::unique_ptr<gfx::Shader>        shaderModule;
        std::unique_ptr<gfx::Renderer<T>>   renderModule;
        std::unique_ptr<gfx::Movement<T>>   movementModule;

        std::vector<std::filesystem::path>  texturePaths;

        std::vector<gfx::VAOGroupData<T>> getVAOTestInitData();
};




template<typename T>
EngineCore<T>::EngineCore()
{
    windowModule = std::make_unique<gfx::Window>("Test Window");

    gfxAssetsModule = std::make_unique<gfx::GfxAssets>();

    texturePaths = gfxAssetsModule->getTexturePaths();

    #ifdef ENABLE_DEBUG_MESSAGES
        for (auto path : texturePaths)
        {
            std::cout << "DEBUG::Path found: " << path.string() << std::endl;
        }

        std::cout << "DEBUG::Frag shader path = " << gfxAssetsModule->getFragShaderPath().string() << std::endl;
        std::cout << "DEBUG::Vert shader path = " << gfxAssetsModule->getVertShaderPath().string() << std::endl;
    #endif

    shaderModule = std::make_unique<gfx::Shader>(gfxAssetsModule->getFragShaderPath().string(), gfxAssetsModule->getVertShaderPath().string());

    renderModule = std::make_unique<gfx::Renderer<T>>(getVAOTestInitData(), texturePaths, *shaderModule);

    movementModule = std::make_unique<gfx::Movement<T>>(renderModule->getMovableObjects());
}

template<typename T>
void EngineCore<T>::runLoop()
{
    // Render loop
	while (!glfwWindowShouldClose(windowModule->getGlfwWindow()))
	{
		windowModule->processKeyboardInput();

		glfwPollEvents();

		windowModule->clearScreen();

		shaderModule->updateViewMatrixValue(windowModule->getCameraInstance()->calculateViewMatrix());

		shaderModule->updateProjectionMatrixValue(windowModule->getCameraInstance()->calculateProjectionMatrix());

        movementModule->performTestAnimation();

		renderModule->drawScene(*shaderModule, *windowModule);

		glfwSwapBuffers(windowModule->getGlfwWindow());
	}

	glfwTerminate();
}

template<typename T>
std::vector<gfx::VAOGroupData<T>> EngineCore<T>::getVAOTestInitData()
{
    gfx::VAOGroupData<glm::vec3> initData;

	initData.vertices = std::vector<float>(std::begin(gfx::cubeVertices), std::end(gfx::cubeVertices));
	initData.indices = std::vector<unsigned int>(std::begin(gfx::cubeIndices), std::end(gfx::cubeIndices));

	for (const auto& cubePosition : gfx::cubePositions)
	{
		gfx::PositionAndTextureInstance newInstance(cubePosition, std::vector<uint32_t>({0, 1})); // Assign the two textures we have

		initData.instanceData.push_back(std::move(newInstance));
	}

	auto VAOGroupDataVec = std::vector<gfx::VAOGroupData<glm::vec3>>{initData};

    return VAOGroupDataVec;
}

#endif


