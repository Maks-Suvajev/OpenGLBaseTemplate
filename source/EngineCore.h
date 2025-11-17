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

        std::vector<gfx::ModelInitData> generateRenderInitData();
};

template<typename T>
std::vector<gfx::ModelInitData> EngineCore<T>::generateRenderInitData()
{
    std::vector<gfx::ModelInitData>     renderInitVector;
    gfx::ModelInitData                  renderInitInstance1;
    gfx::ModelInitData                  renderInitInstance2;
    std::vector<gfx::MaterialMeshPair>  matMeshPairs1;
    gfx::MaterialMeshPair               matMeshPair1;
    std::vector<gfx::MaterialMeshPair>  matMeshPairs2;
    gfx::MaterialMeshPair               matMeshPair2;

    gfx::Transform object1;

    object1.position.x = 1.2f;
    object1.position.y = 1.0f;
    object1.position.z = 2.0f;

    // object1.position.x = 0.0f;
    // object1.position.y = 0.0f;
    // object1.position.z = 0.0f;

    object1.rotation.x = 0.0f;
    object1.rotation.y = 0.0f;
    object1.rotation.z = 0.0f;

    object1.scaleFactors.x = 0.2f;
    object1.scaleFactors.y = 0.2f;
    object1.scaleFactors.z = 0.2f;

    objectTransforms.push_back(object1);

    renderInitInstance1.transform = &objectTransforms.back();


    gfx::Material material1;

    material1.shader = shaderManagerModule->getShaderPtr("lightSource");
    material1.texture = static_cast<GLuint>(0); // No texture for now
    material1.isLightSource = true;

    gfx::MeshData mesh1;

    size_t sizeOfCubeData = sizeof(gfx::cubeVertices) / sizeof(gfx::cubeVertices[0]);

    mesh1.vertices.assign(gfx::cubeVertices, gfx::cubeVertices + sizeOfCubeData);

    matMeshPair1.meshData = mesh1;
    matMeshPair1.material = material1;

    matMeshPairs1.push_back(matMeshPair1);

    renderInitInstance1.materialMeshPairs = matMeshPairs1;

    renderInitVector.push_back(renderInitInstance1);


    gfx::Transform object2;

    object2.position.x = 0.0f;
    object2.position.y = 0.0f;
    object2.position.z = 0.0f;


    object2.rotation.x = 0.0f;
    object2.rotation.y = 0.0f;
    object2.rotation.z = 0.0f;

    object2.scaleFactors.x = 1.0f;
    object2.scaleFactors.y = 1.0f;
    object2.scaleFactors.z = 1.0f;

    objectTransforms.push_back(object2);

    renderInitInstance2.transform = &objectTransforms.back();


    gfx::Material material2;

    material2.shader = shaderManagerModule->getShaderPtr("normalObject");
    material2.texture = static_cast<GLuint>(0); // No texture for now
    material2.isLightSource = false;


    gfx::MeshData mesh2;

    mesh2.vertices.assign(gfx::cubeVertices, gfx::cubeVertices + sizeOfCubeData);

    matMeshPair2.meshData = mesh2;
    matMeshPair2.material = material2;

    matMeshPairs2.push_back(matMeshPair2);

    renderInitInstance2.materialMeshPairs = matMeshPairs2;


    renderInitVector.push_back(renderInitInstance2);


    return renderInitVector;

}


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

        //std::cout << "DEBUG::Frag shader path = " << gfxAssetsManagerModule->getFragShaderPath().string() << std::endl;
        //std::cout << "DEBUG::Vert shader path = " << gfxAssetsManagerModule->getVertShaderPath().string() << std::endl;
    #endif

    std::vector<gfx::ShaderFilenameStrings> shaderFilenames;

    gfx::ShaderFilenameStrings lightSourceShader;

    lightSourceShader.setName = "lightSource";
    lightSourceShader.vertexShader = "vertexShaderLightTest.vs";
    lightSourceShader.fragmentShader = "fragmentShaderLightSource.fs";

    shaderFilenames.push_back(lightSourceShader);

    gfx::ShaderFilenameStrings lightAffectedObject;

    lightAffectedObject.setName = "normalObject";
    lightAffectedObject.vertexShader = "vertexShaderLightTest.vs";
    lightAffectedObject.fragmentShader = "fragmentShaderLightTest.fs";

    shaderFilenames.push_back(lightAffectedObject);

    std::vector<gfx::ShaderPaths> shaderSources = gfxAssetsManagerModule->loadShaderPathSet(shaderFilenames);

    shaderManagerModule = std::make_unique<gfx::ShaderManager>(shaderSources);

    
    std::vector<gfx::ModelInitData> renderInitVector = generateRenderInitData();

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


        //shaderManagerModule->getShaderPtr("normalObject")->useProgram();
        //shaderManagerModule->getShaderPtr("normalObject")->updateUniformValue("objectColor", glm::vec3{1.0f, 0.5f, 0.31f});
        //shaderManagerModule->getShaderPtr("normalObject")->updateUniformValue("lightColor",  glm::vec3{1.0f, 1.0f, 1.0f});
        
        
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

// template<typename T>
// std::vector<gfx::VAOGroupData<T>> EngineCore<T>::getVAOTestInitData()
// {
//     gfx::VAOGroupData<glm::vec3> initData;

// 	initData.vertices = std::vector<float>(std::begin(gfx::cubeVertices), std::end(gfx::cubeVertices));
// 	initData.indices = std::vector<unsigned int>(std::begin(gfx::cubeIndices), std::end(gfx::cubeIndices));

// 	for (const auto& cubePosition : gfx::cubePositions)
// 	{
// 		gfx::PositionAndTextureInstance newInstance(cubePosition, std::vector<uint32_t>({0, 1})); // Assign the two textures we have

// 		initData.instanceData.push_back(std::move(newInstance));
// 	}

// 	auto VAOGroupDataVec = std::vector<gfx::VAOGroupData<glm::vec3>>{initData};

//     return VAOGroupDataVec;
// }

#endif


