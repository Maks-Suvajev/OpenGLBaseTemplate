#ifndef ENGINE_CORE_H
#define ENGINE_CORE_H

// STL
#include <memory> 
#include <vector>
#include <string>

// OS access 


// QT
#include <QOpenGLExtraFunctions>

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
        EngineCore(QOpenGLExtraFunctions* openGLFunctions);
        void runStep();
        void initTestModule(); // Pass resources to test module - required before GUI implmented.
        void updateResolution(float width, float height);

    private:

        // Window
        //std::unique_ptr<gfx::Window>            m_windowModule;
        std::unique_ptr<gfx::Camera>            m_cameraModule;
        
        // Asset management
        std::unique_ptr<gfx::GfxAssetsManager>  m_gfxAssetsManagerModule; // loads and stores paths for different assets
        std::unique_ptr<gfx::ShaderManager>     m_shaderManagerModule; // Manages compiling, storing and accessing shaders
        std::unique_ptr<gfx::TextureManager>    m_textureManagerModule; // Manages loading and storing textures
        std::unique_ptr<gfx::MeshManager>       m_meshManagerModule; // Manages loading and storing Meshes
        std::unique_ptr<gfx::MaterialManager>   m_materialManagerModule; // Manages storing different material configurations

        // Systems
        std::unique_ptr<gfx::Renderer>          m_renderModule; // Renders renderable components
        std::unique_ptr<gfx::RenderSystem>      m_renderSystemModule; // Syncs rendering, material, mesh and light 
        std::unique_ptr<gfx::Movement>          m_movementModule; // Controls movement of entities based on inputs and physics
        std::unique_ptr<gfx::LightingSystem>    m_lightingSystemModule;

        // Components and Entities
        std::unique_ptr<EntityManager>          m_entityManagerModule; // Manages entities. their components and lifetimes

        // Test - Will be replaced by GUI
        std::unique_ptr<Test>                   m_testModule;

        QOpenGLExtraFunctions*                  m_openGLFunctions;
};

template<typename T>
void EngineCore<T>::updateResolution(float width, float height)
{
    if (!m_cameraModule)
    {
        m_cameraModule = std::make_unique<gfx::Camera>(width, height);
    }
    else
    {
        m_cameraModule->updateScreenResolution(width, height);
    }
}

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
    testObjects.textureManager  = m_textureManagerModule.get();
    testObjects.shaderManager   = m_shaderManagerModule.get(); 
    testObjects.entityManager   = m_entityManagerModule.get();
    testObjects.materialManager = m_materialManagerModule.get();
    testObjects.meshManager     = m_meshManagerModule.get();
    testObjects.lightingSystem   = m_lightingSystemModule.get();

    m_testModule = std::make_unique<Test>(testObjects);
}

template<typename T>
EngineCore<T>::EngineCore(QOpenGLExtraFunctions* openGLFunctions)
    : m_openGLFunctions(openGLFunctions)
{
    // Create window
    //windowModule = std::make_unique<gfx::Window>("Render Window");

    // Detect and load asset paths
    m_gfxAssetsManagerModule = std::make_unique<gfx::GfxAssetsManager>();

    // Load up all the detected textures
    m_textureManagerModule = std::make_unique<gfx::TextureManager>(m_gfxAssetsManagerModule->getTexturePaths(), m_openGLFunctions);

    // Get the shader paths (from test data)
    std::vector<gfx::ShaderProgramFilePaths> shaderSources = m_gfxAssetsManagerModule->loadShaderPathSet(shaderFilenames);

    // Load and compile shaders
    m_shaderManagerModule = std::make_unique<gfx::ShaderManager>(shaderSources, m_openGLFunctions);
    
    // Init mesh manager
    m_meshManagerModule = std::make_unique<gfx::MeshManager>(m_openGLFunctions);

    // Init material manager
    m_materialManagerModule = std::make_unique<gfx::MaterialManager>();

    // Init entity manager
    m_entityManagerModule = std::make_unique<EntityManager>();

    // Init Lighting System
    m_lightingSystemModule = std::make_unique<gfx::LightingSystem>();

    initTestModule();

    m_testModule->initTestData();

    m_renderModule = std::make_unique<gfx::Renderer>(openGLFunctions);
    m_renderSystemModule = std::make_unique<gfx::RenderSystem>();


    m_movementModule = std::make_unique<gfx::Movement>();
}

template<typename T>
void EngineCore<T>::runStep()
{
    //m_windowModule->processKeyboardInput(); //TODO: Replaced by QT

    //glfwPollEvents(); //TODO: Replaced by QT

    //m_windowModule->clearScreen(); //

    m_renderSystemModule->runRender(m_cameraModule.get(), m_renderModule.get(), m_entityManagerModule.get(), m_lightingSystemModule.get(), m_shaderManagerModule.get());

    //glfwSwapBuffers(windowModule->getGlfwWindow()); //TODO: Replaced by QT
}

#endif


