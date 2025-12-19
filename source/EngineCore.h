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
#include "Movement.h"
#include <deque>
#include <vector>
#include <string>


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

        std::unique_ptr<gfx::Movement>          movementModule;

        
        std::deque<gfx::Transform> objectTransforms; //TODO: temporary store for transforms. For entity handler

        std::vector<gfx::ModelInitData> populateRenderInitVector(); //TODO: replace with entity handler
};


struct testObjectInitData
{
    glm::vec3 position;
    glm::vec3 rotation;
    glm::vec3 scale;
    std::string shaderName;
    std::string diffuseTexture;
    std::string specularTexture;
    float shininess;

    bool isLightSource;
};

// Object specific data
static const std::vector<testObjectInitData> testData
{
    {{1.2f, 1.0, 2.0f}, {0.0f, 0.0f, 0.0f}, {0.2f, 0.2f, 0.2f}, "lightSource", "", "", 0.0f, true},
    {{2.0f, 5.0f, -15.0f}, {0.0f, 0.0f, 0.0f}, {1.0f, 1.0f, 1.0f}, "normalObject", "container2.png", "container2_specular.png", 1024.0f, false},
    {{0.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 0.0f}, {1.0f, 1.0f, 1.0f}, "normalObject", "container2.png", "container2_specular.png", 1024.0f, false},
    {{-1.5f, -2.2f, -2.5f}, {0.0f, 0.0f, 0.0f}, {1.0f, 1.0f, 1.0f}, "normalObject", "container2.png", "container2_specular.png", 1024.0f, false},
    {{-3.8f, -2.0f, -12.3f}, {0.0f, 0.0f, 0.0f}, {1.0f, 1.0f, 1.0f}, "normalObject", "container2.png", "container2_specular.png", 1024.0f, false},
    {{2.4f, -0.4f, -3.5f}, {0.0f, 0.0f, 0.0f}, {1.0f, 1.0f, 1.0f}, "normalObject", "container2.png", "container2_specular.png", 1024.0f, false},
    {{-1.7f, 3.0f, -7.5f}, {0.0f, 0.0f, 0.0f}, {1.0f, 1.0f, 1.0f}, "normalObject", "container2.png", "container2_specular.png", 1024.0f, false},
    {{1.3f, -2.0f, -2.5f}, {0.0f, 0.0f, 0.0f}, {1.0f, 1.0f, 1.0f}, "normalObject", "container2.png", "container2_specular.png", 1024.0f, false},
    {{1.5f, 2.0f, -2.5f}, {0.0f, 0.0f, 0.0f}, {1.0f, 1.0f, 1.0f}, "normalObject", "container2.png", "container2_specular.png", 1024.0f, false},
    {{1.5f, 0.2f, -1.5f}, {0.0f, 0.0f, 0.0f}, {1.0f, 1.0f, 1.0f}, "normalObject", "container2.png", "container2_specular.png", 1024.0f, false},
    {{-1.3f, 1.0f, -1.5f}, {0.0f, 0.0f, 0.0f}, {1.0f, 1.0f, 1.0f}, "normalObject", "container2.png", "container2_specular.png", 1024.0f, false},
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

        // Load initial transform data 
        gfx::Transform transform { testObject.position, testObject.rotation, testObject.scale };

        objectTransforms.push_back(transform);
        renderInstance.transform = &objectTransforms.back();

        // Configure the material properties
        gfx::MaterialProperties materialProperties;
        materialProperties.diffuse = textureManagerModule->getTexture(testObject.diffuseTexture);
        materialProperties.specular = textureManagerModule->getTexture(testObject.specularTexture);
        materialProperties.shininess = testObject.shininess;

        gfx::Material material {
             shaderManagerModule->getShaderPtr(testObject.shaderName), 
             materialProperties, 
             testObject.isLightSource 
            };

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
    // Create window
    windowModule = std::make_unique<gfx::Window>("Test Window");

    // Detect and load asset paths
    gfxAssetsManagerModule = std::make_unique<gfx::GfxAssetsManager>();

    // Load up all the detected textures
    textureManagerModule = std::make_unique<gfx::TextureManager>(gfxAssetsManagerModule->getTexturePaths());

    // Get the shader paths (from test data)
    std::vector<gfx::ShaderPaths> shaderSources = gfxAssetsManagerModule->loadShaderPathSet(shaderFilenames);

    // Load and compile shaders
    shaderManagerModule = std::make_unique<gfx::ShaderManager>(shaderSources);
    
    // Populate test data
    std::vector<gfx::ModelInitData> renderInitVector = populateRenderInitVector();

    // Initialise renderer with test data
    renderModule = std::make_unique<gfx::Renderer>(renderInitVector);

    movementModule = std::make_unique<gfx::Movement>();
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
	
        movementModule->performTestAnimation(objectTransforms);
        renderModule->updateViewPosForSpecularLight(windowModule->getCameraInstance()->getCameraPosition());
		renderModule->drawScene();

		glfwSwapBuffers(windowModule->getGlfwWindow());
	}

	glfwTerminate();
}

#endif


