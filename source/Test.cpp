#include "Test.h"

Test::Test(TestObjects testInitObjects)
{
    testObjects.entityManager   = nullptr;
    testObjects.materialManager = nullptr;
    testObjects.textureManager  = nullptr;
    testObjects.shaderManager   = nullptr;
    testObjects.meshManager     = nullptr;

    testObjects.entityManager   = testInitObjects.entityManager;
    testObjects.materialManager = testInitObjects.materialManager;
    testObjects.textureManager  = testInitObjects.textureManager;
    testObjects.shaderManager   = testInitObjects.shaderManager;
    testObjects.meshManager     = testInitObjects.meshManager;

    printTestInput();
}

void Test::createEntity()
{
    Entity newEntity = testObjects.entityManager->generateNewEntity();

    testObjects.entityManager->printActiveEntityIDs();

    initMeshComponent(newEntity);
    initMaterialComponent(newEntity);
    initTransformComponent(newEntity);

    testObjects.entityManager->printActiveEntityIDs();
    testObjects.entityManager->printActiveEntityComponents(newEntity);

}

void Test::initTestData()
{
    printCurrentAssets();

    // Populate mesh manager and material manager
    initMeshData();
    initMaterialData();

    createEntity();
}

void Test::initMeshData()
{
    gfx::MeshData newMesh;
    newMesh.vertices = std::vector<float>(std::begin(gfx::cubeVertices), std::end(gfx::cubeVertices));

    testObjects.meshManager->addMesh("cube", std::move(newMesh));

}

gfx::MaterialProperties Test::initLightCubeMaterial()
{
    gfx::MaterialProperties initProperties;

    // shader
    initProperties.shader = testObjects.shaderManager->getShaderID("lightSource");

    initProperties.shininess = 0.0f;
    initProperties.isLightSource = true;

    return initProperties;
}

gfx::MaterialProperties Test::initGenericCubeMaterial()
{
    gfx::MaterialProperties initProperties;

    // shader
    initProperties.shader = testObjects.shaderManager->getShaderID("normalObject");

    // lighting texture
    initProperties.lightingTextures.diffuse = testObjects.textureManager->getTexture("container2.png");
    initProperties.lightingTextures.specular = testObjects.textureManager->getTexture("container2_specular.png");

    initProperties.shininess = 1024.0f;
    initProperties.isLightSource = false;

    return initProperties;
}


void Test::initMaterialData()
{
    testObjects.materialManager->addMaterial("generic cube", std::move(initGenericCubeMaterial()));
    testObjects.materialManager->addMaterial("light cube", std::move(initLightCubeMaterial()));

}

void Test::initMeshComponent(Entity entity)
{
    auto meshPtr = testObjects.meshManager->getMesh("cube");   
    
    if (meshPtr.has_value())
    {
        testObjects.entityManager->addComponentData<gfx::GpuHandles>(entity, meshPtr.value()->getGPUHandles());
    }

}

void Test::initMaterialComponent(Entity entity)
{
    auto materialPtr = testObjects.materialManager->getMaterial("generic cube");

    if (materialPtr.has_value())
    {
        testObjects.entityManager->addComponentData<gfx::MaterialProperties>(entity, materialPtr.value()->getMaterialProperties());
    }
   
}

gfx::Transform Test::initCubeTransform()
{
    gfx::Transform newTransform;

    newTransform.position = glm::vec3{0.0f, 0.0f, 0.0f};
    newTransform.rotation = glm::vec3{0.0f, 0.0f, 0.0f};
    newTransform.scaleFactors = glm::vec3{1.0f, 1.0f, 1.0f};

    return newTransform;
}

void Test::initTransformComponent(Entity entity)
{
    testObjects.entityManager->addComponentData<gfx::Transform>(entity, initCubeTransform());
}

void Test::printCurrentAssets()
{
    if (testObjects.textureManager != nullptr)
    {
        testObjects.textureManager->printAllTextures();
    }
    else
    {
        std::cout << "Can't print textures, pointer is null." << std::endl;
    }

    if (testObjects.shaderManager != nullptr)
    {
        testObjects.shaderManager->printAllShaderPrograms();
    }
    else
    {
        std::cout << "Can't print shaders, pointer is null." << std::endl;
    }
}

void Test::printTestInput()
{
    if (testObjects.entityManager == nullptr)
    {
        std::cout << "ERROR::Entity manager is nullptr." << std::endl;
    }

    if (testObjects.materialManager == nullptr)
    {
        std::cout << "ERROR::Material manager is nullptr." << std::endl;
    }

    if (testObjects.textureManager == nullptr)
    {
        std::cout << "ERROR::Texture manager is nullptr." << std::endl;
    }

    if (testObjects.shaderManager == nullptr)
    {
        std::cout << "ERROR::Shader manager is nullptr." << std::endl;
    }

    if (testObjects.meshManager == nullptr)
    {
        std::cout << "ERROR::Mesh manager is nullptr." << std::endl;
    }

    std::cout << "If no errors above, all pointers are valid." << std::endl;
}
