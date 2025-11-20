#ifndef ENGINE_CORE_H
#define ENGINE_CORE_H

// System includes
#include <memory> //For pointers
#include "Window.h"
#include "Renderer.h"
#include "ShaderManager.h"
#include "GfxAssetsManager.h"
#include "Model.h"
#include "TextureManager.h"
#include "deque"


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

        std::unique_ptr<gfx::GfxAssetsManager>  gfxAssetsManagerModule;
        std::unique_ptr<gfx::Window>            windowModule;
        std::unique_ptr<gfx::ShaderManager>     shaderManagerModule;
        std::unique_ptr<gfx::TextureManager>    textureManagerModule;
        std::unique_ptr<gfx::Renderer>          renderModule;

        //std::unique_ptr<gfx::Movement<T>>   movementModule;

        std::vector<std::filesystem::path>  texturePaths;
        
        std::deque<gfx::Transform> objectTransforms;

        std::vector<gfx::ModelInitData> populateRenderInitVector(); //TODO: replace with entity handler
};



// TESTING DATA - WILL BE REPLACED BY ENTITY MANAGER --------------------------------

struct testObjectInitData
{
    glm::vec3 position;
    glm::vec3 rotation;
    glm::vec3 scale;
    std::string shaderName;
    bool isLightSource;
};

// Object specific data
static const std::vector<testObjectInitData> testData
{
    {{1.2f, 1.0, 2.0f}, {0.0f, 0.0f, 0.0f}, {0.2f, 0.2f, 0.2f}, "lightSource", true},
    {{0.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 0.0f}, {1.0f, 1.0f, 1.0f}, "normalObject", false}
};

// Shader file names with specific set name.
static const std::vector<gfx::ShaderFilenameStrings> shaderFilenames
{
    {"lightSource", "vertexShaderLightTest.vs", "fragmentShaderLightSource.fs"},
    {"normalObject", "vertexShaderLightTest.vs", "fragmentShaderLightTest.fs"}
};

template<typename T>
std::vector<gfx::ModelInitData> EngineCore<T>::populateRenderInitVector()
{
    std::vector<gfx::ModelInitData>     renderInitVector;

    for (const auto& testObject : testData)
    {
        gfx::ModelInitData                  renderInstance;
        std::vector<gfx::MaterialMeshPair>  matMeshPairs;

        gfx::Transform transform { testObject.position, testObject.rotation, testObject.scale };

        objectTransforms.push_back(transform);
        renderInstance.transform = &objectTransforms.back();

        gfx::Material material { shaderManagerModule->getShaderPtr(testObject.shaderName), static_cast<GLuint>(0), testObject.isLightSource };

        gfx::MeshData mesh;

        size_t sizeOfCubeData = sizeof(gfx::cubeVertices) / sizeof(gfx::cubeVertices[0]);

        mesh.vertices.assign(gfx::cubeVertices, gfx::cubeVertices + sizeOfCubeData);

        gfx::MaterialMeshPair matMeshPair { material, mesh };

        std::vector<gfx::MaterialMeshPair> materialMeshVector { matMeshPair };

        renderInstance.materialMeshPairs = materialMeshVector;

        renderInitVector.push_back(renderInstance);

    }

    return renderInitVector;
}

// --------------------------------------------------------------------------------------------


template<typename T>
EngineCore<T>::EngineCore()
{
    windowModule = std::make_unique<gfx::Window>("Test Window");

    gfxAssetsManagerModule = std::make_unique<gfx::GfxAssetsManager>();

    texturePaths = gfxAssetsManagerModule->getTexturePaths();

    #ifdef ENABLE_DEBUG_MESSAGES
        for (auto path : texturePaths)
        {
            std::cout << "DEBUG::Path found: " << path.string() << std::endl;
        }
    #endif

    std::vector<gfx::ShaderPaths> shaderSources = gfxAssetsManagerModule->loadShaderPathSet(shaderFilenames);

    shaderManagerModule = std::make_unique<gfx::ShaderManager>(shaderSources);
    
    std::vector<gfx::ModelInitData> renderInitVector = populateRenderInitVector();

    renderModule = std::make_unique<gfx::Renderer>(renderInitVector);

    //movementModule = std::make_unique<gfx::Movement<T>>(renderModule->getMovableObjects());
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

        std::vector<gfx::Shader*> shadersToUpdate = shaderManagerModule->getRawShaderPointers();

        for (auto const& shader : shadersToUpdate)
        {
            shader->useProgram();
	        shader->updateViewMatrixValue(windowModule->getCameraInstance()->calculateViewMatrix());
		    shader->updateProjectionMatrixValue(windowModule->getCameraInstance()->calculateProjectionMatrix());
        }
	
        //movementModule->performTestAnimation();

		renderModule->drawScene();

		glfwSwapBuffers(windowModule->getGlfwWindow());
	}

	glfwTerminate();
}

#endif


