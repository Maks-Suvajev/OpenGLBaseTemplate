#ifndef ENGINE_CORE_H
#define ENGINE_CORE_H

// STL
#include <memory> //For pointers
#include <deque>
#include <vector>
#include <string>

// OS access 
#include "Window.h"

// Resource managers
#include "ShaderManager.h"
#include "GfxAssetsManager.h"
#include "TextureManager.h"
#include "MeshManager.h"
#include "MaterialManager.h"

// Entities
#include "EntityManager.h"

// Components
#include "ComponentManager.h"

// Systems
#include "Renderer.h"
#include "Movement.h"

// Test data loader
#include "Test.h"


// use glm::vec3 for 3D and glm::vec2 for 2D
template<typename T>
class EngineCore
{

    public:
        EngineCore();
        void runLoop();
        void initTestModule();

    private:

        // Window
        std::unique_ptr<gfx::Window>            windowModule;

        // Asset management
        std::unique_ptr<gfx::GfxAssetsManager>  gfxAssetsManagerModule; // loads and stores paths for different assets
        std::unique_ptr<gfx::ShaderManager>     shaderManagerModule; // Manages compiling, storing and accessing shaders
        std::unique_ptr<gfx::TextureManager>    textureManagerModule; // Manages loading and storing textures
        std::unique_ptr<gfx::MeshManager>       meshManagerModule; // Manages loading and storing Meshes
        std::unique_ptr<gfx::MaterialManager>   materialManagerModule; // Manages storing different material configurations

        // Systems
        std::unique_ptr<gfx::Renderer>          renderModule; // Renders renderable components
        std::unique_ptr<gfx::Movement>          movementModule; // Controls movement of entities based on inputs and physics

        // Components and Entities
        std::unique_ptr<EntityManager>          entityManagerModule; // Manages entities. their components and lifetimes

        // Test
        std::unique_ptr<Test>                   testModule;
};

template<typename T>
void EngineCore<T>::initTestModule()
{
    TestObjects testObjects;
    testObjects.entityManager   = entityManagerModule.get();
    testObjects.materialManager = materialManagerModule.get();
    testObjects.meshManager     = meshManagerModule.get();

    testModule = std::make_unique<Test>(testObjects);
}


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
static const std::vector<gfx::ShaderProgramFilenameStrings> shaderFilenames
{
    {"lightSource", "vertexShaderLightTest.vs", "fragmentShaderLightSource.fs"},
    {"normalObject", "vertexShaderLightTest.vs", "fragmentShaderLightTest.fs"}
};

// template<typename T>
// std::vector<gfx::ModelInitData> EngineCore<T>::populateRenderInitVector()
// {
//     std::vector<gfx::ModelInitData>     renderInitVector;

//     for (const auto& testObject : testData)
//     {
//         gfx::ModelInitData                  renderInstance;
//         std::vector<gfx::MaterialMeshPair>  matMeshPairs;

//         // Load initial transform data 
//         gfx::Transform transform { testObject.position, testObject.rotation, testObject.scale };

//         objectTransforms.push_back(transform);
//         renderInstance.transform = &objectTransforms.back();

//         // Configure the material properties
//         gfx::MaterialProperties materialProperties;
//         materialProperties.diffuse = textureManagerModule->getTexture(testObject.diffuseTexture);
//         materialProperties.specular = textureManagerModule->getTexture(testObject.specularTexture);
//         materialProperties.shininess = testObject.shininess;

//         gfx::Material material {
//              shaderManagerModule->getShaderPtr(testObject.shaderName), 
//              materialProperties, 
//              testObject.isLightSource 
//             };

//         gfx::MeshData mesh;

//         size_t sizeOfCubeData = sizeof(gfx::cubeVertices) / sizeof(gfx::cubeVertices[0]);

//         mesh.vertices.assign(gfx::cubeVertices, gfx::cubeVertices + sizeOfCubeData);

//         gfx::MaterialMeshPair matMeshPair { material, mesh };

//         std::vector<gfx::MaterialMeshPair> materialMeshVector { matMeshPair };

//         renderInstance.materialMeshPairs = materialMeshVector;

//         renderInitVector.push_back(renderInstance);

//     }

//     return renderInitVector;
// }

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
    std::vector<gfx::ShaderProgramFilePaths> shaderSources = gfxAssetsManagerModule->loadShaderPathSet(shaderFilenames);

    // Load and compile shaders
    shaderManagerModule = std::make_unique<gfx::ShaderManager>(shaderSources);
    
    // Init mesh manager
    meshManagerModule = std::make_unique<gfx::MeshManager>();

    // Init material manager
    materialManagerModule = std::make_unique<gfx::MaterialManager>();

    // Init entity manager
    entityManagerModule = std::make_unique<EntityManager>();

    initTestModule();

    testModule->initTestData();

    // Initialise renderer with test data
    renderModule = std::make_unique<gfx::Renderer>();

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

            // For SpotLight
            //std::cout << "Shader name: " << shader->getShaderName() << std::endl;

            if (shader->getShaderName() == "normalObject")
            {
                shader->updateUniformValue("spotLight.position", windowModule->getCameraInstance()->getCameraPosition());
                shader->updateUniformValue("spotLight.direction", windowModule->getCameraInstance()->getCameraFront());
                shader->updateUniformValue("spotLight.cutOff", glm::cos(glm::radians(12.5f)));
                shader->updateUniformValue("spotLight.outerCutOff", glm::cos(glm::radians(17.5f)));
            }



	        //shader->updateViewMatrixValue(windowModule->getCameraInstance()->calculateViewMatrix());
		    //shader->updateProjectionMatrixValue(windowModule->getCameraInstance()->calculateProjectionMatrix());
            
        }
	
        //movementModule->performTestAnimation(objectTransforms);
        //renderModule->updateViewPosForSpecularLight(windowModule->getCameraInstance()->getCameraPosition());
		//renderModule->drawScene();

		glfwSwapBuffers(windowModule->getGlfwWindow());
	}

	glfwTerminate();
}

#endif


