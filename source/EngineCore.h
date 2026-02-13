#ifndef ENGINE_CORE_H
#define ENGINE_CORE_H

// STL
#include <memory> 
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
#include "RenderSystem.h" 
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
        void initTestModule(); // Pass resources to test module - required before GUI implmented.

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
        std::unique_ptr<gfx::RenderSystem>      renderSystemModule; // Syncs rendering, material, mesh and light 
        std::unique_ptr<gfx::Movement>          movementModule; // Controls movement of entities based on inputs and physics
        std::unique_ptr<gfx::LightingSystem>    lightingSystemModule;

        // Components and Entities
        std::unique_ptr<EntityManager>          entityManagerModule; // Manages entities. their components and lifetimes

        // Test - Will be replaced by GUI
        std::unique_ptr<Test>                   testModule;
};

// Preset shaders for testing - GUI will make it more flexible
static const std::vector<gfx::ShaderProgramFilenameStrings> shaderFilenames
{
    {"lightSource", "vertexShaderLightTest.vs", "fragmentShaderLightSource.fs"},
    {"normalObject", "vertexShaderLightTest.vs", "fragmentShaderLightTest.fs"}
};

template<typename T>
void EngineCore<T>::initTestModule()
{
    TestObjects testObjects;
    testObjects.textureManager  = textureManagerModule.get();
    testObjects.shaderManager   = shaderManagerModule.get(); 
    testObjects.entityManager   = entityManagerModule.get();
    testObjects.materialManager = materialManagerModule.get();
    testObjects.meshManager     = meshManagerModule.get();
    testObjects.lightingSystem   = lightingSystemModule.get();

    testModule = std::make_unique<Test>(testObjects);
}

template<typename T>
EngineCore<T>::EngineCore()
{
    // Create window
    windowModule = std::make_unique<gfx::Window>("Render Window");

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

    // Init Lighting System
    lightingSystemModule = std::make_unique<gfx::LightingSystem>();

    initTestModule();

    testModule->initTestData();

    renderModule = std::make_unique<gfx::Renderer>();
    renderSystemModule = std::make_unique<gfx::RenderSystem>();


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

        renderSystemModule->runRender(windowModule.get(), renderModule.get(), entityManagerModule.get(), lightingSystemModule.get(), shaderManagerModule.get());

		glfwSwapBuffers(windowModule->getGlfwWindow());
	}

	glfwTerminate();
}

#endif


