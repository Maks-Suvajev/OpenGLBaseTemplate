cmake_minimum_required(VERSION 3.16)
project(RenderingEngine LANGUAGES CXX C)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Set base paths
set(DEPS_INCLUDE_DIR ${CMAKE_SOURCE_DIR}/Dependencies/includes)
set(DEPS_LIB_DIR ${CMAKE_SOURCE_DIR}/Dependencies/libs)
set(DEPS_SRC_DIR ${CMAKE_SOURCE_DIR}/Dependencies/source)
set(CODE_SRC_DIR ${CMAKE_SOURCE_DIR}/source)

set(ASSETS_SRC_DIR ${CODE_SRC_DIR}/Assets/source)
set(CORE_SRC_DIR ${CODE_SRC_DIR}/Core)
set(ECS_SRC_DIR ${CODE_SRC_DIR}/ECS)

set(ENTITY_SRC_DIR ${ECS_SRC_DIR}/Entity)
set(COMPONENT_SRC_DIR ${ECS_SRC_DIR}/Component)
set(TYPES_SRC_DIR ${COMPONENT_SRC_DIR}/Types)
set(SYSTEMS_SRC_DIR ${ECS_SRC_DIR}/System)
set(CAMERA_SRC_DIR ${SYSTEMS_SRC_DIR}/Camera)
set(LIGHTING_SRC_DIR ${SYSTEMS_SRC_DIR}/Lighting)
set(MOVEMENT_SRC_DIR ${SYSTEMS_SRC_DIR}/Movement)
set(RENDER_SRC_DIR ${SYSTEMS_SRC_DIR}/Render)

set(FRONTEND_SRC_DIR ${CODE_SRC_DIR}/Frontend)
set(DISPLAYS_SRC_DIR ${FRONTEND_SRC_DIR}/Displays)
set(MODELS_SRC_DIR ${FRONTEND_SRC_DIR}/Models)

set(RESOURCE_MANAGERS_SRC_DIR ${CODE_SRC_DIR}/ResourceManagers)
set(MATERIAL_SRC_DIR ${RESOURCE_MANAGERS_SRC_DIR}/Material)
set(MESH_SRC_DIR ${RESOURCE_MANAGERS_SRC_DIR}/Mesh)
set(TEXTURE_SRC_DIR ${RESOURCE_MANAGERS_SRC_DIR}/Texture)

set(SHADER_SRC_DIR ${CODE_SRC_DIR}/Shaders/class)



# Add source files
set(SRC_FILES

    ${CORE_SRC_DIR}/main.cpp
    ${CORE_SRC_DIR}/EngineCore.cpp
    ${CORE_SRC_DIR}/Test.cpp

    ${ASSETS_SRC_DIR}/GfxAssetRegistry.cpp

    ${SHADER_SRC_DIR}/Shader.cpp
	${SHADER_SRC_DIR}/ShaderManager.cpp

    ${ENTITY_SRC_DIR}/EntityManager.cpp
    ${CAMERA_SRC_DIR}/Camera.cpp
    ${LIGHTING_SRC_DIR}/LightingSystem.cpp
    ${MOVEMENT_SRC_DIR}/MovementSystem.cpp
	${RENDER_SRC_DIR}/Renderer.cpp
    ${RENDER_SRC_DIR}/RenderSystem.cpp

    ${MATERIAL_SRC_DIR}/MaterialManager.cpp
    ${MATERIAL_SRC_DIR}/Material.cpp

    ${MESH_SRC_DIR}/MeshManager.cpp
	${MESH_SRC_DIR}/Mesh.cpp

    ${TEXTURE_SRC_DIR}/TextureManager.cpp

    #QT stuff
    ${FRONTEND_SRC_DIR}/MainWindow.h
    ${FRONTEND_SRC_DIR}/MainWindow.cpp
    ${FRONTEND_SRC_DIR}/Viewport.cpp
    ${MODELS_SRC_DIR}/TextureModel.cpp
    ${DISPLAYS_SRC_DIR}/TextureDisplay.cpp
)

# QT INTEGRATION
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

find_package(Qt6 REQUIRED COMPONENTS Widgets OpenGLWidgets)

set_source_files_properties(${DEPS_SRC_DIR}/glad/glad.c PROPERTIES LANGUAGE C)

# Add executable
add_executable(${PROJECT_NAME} ${SRC_FILES})

target_include_directories(${PROJECT_NAME} PRIVATE
    ${DEPS_INCLUDE_DIR}
    ${DEPS_INCLUDE_DIR}/glm
    ${DEPS_INCLUDE_DIR}/KHR
    ${DEPS_INCLUDE_DIR}/stb
	${SHADER_SRC_DIR}
	${ASSETS_SRC_DIR}
    ${CORE_SRC_DIR}
    ${COMPONENT_SRC_DIR}
    ${TYPES_SRC_DIR}
    ${ENTITY_SRC_DIR}
    ${CAMERA_SRC_DIR}
    ${LIGHTING_SRC_DIR}
    ${MOVEMENT_SRC_DIR}
    ${RENDER_SRC_DIR}
    ${FRONTEND_SRC_DIR}
    ${DISPLAYS_SRC_DIR}
    ${MODELS_SRC_DIR}
    ${MATERIAL_SRC_DIR}
    ${MESH_SRC_DIR}
    ${TEXTURE_SRC_DIR}
)

target_compile_definitions(${PROJECT_NAME} PRIVATE PROJECT_NAME="\"${PROJECT_NAME}\"")

target_compile_definitions(${PROJECT_NAME} PRIVATE GLAD_GL_IMPLEMENTATION)

if(MSVC)
    add_compile_options(/permissive-)
endif()

#target_compile_options(RenderingEngine PRIVATE /showIncludes) // Debugging



set_target_properties(${PROJECT_NAME} PROPERTIES
    CXX_STANDARD 20
    CXX_STANDARD_REQUIRED ON
    CXX_EXTENSIONS OFF
)

# Link the precompiled GLFW and Windows OpenGL lib
target_link_libraries(${PROJECT_NAME}
    Qt6::Widgets
    Qt6::OpenGL
    Qt6::OpenGLWidgets
)

# Set output directory
set_target_properties(${PROJECT_NAME} PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin
)

# --------------------------------------- Debug message toggle ---------------------------------------
add_compile_definitions(ENABLE_DEBUG_MESSAGES)
add_compile_definitions(TEXTURES_DEFAULT_PATH=\"${CMAKE_CURRENT_SOURCE_DIR}/source/Assets/textures\")
add_compile_definitions(SHADER_SOURCE_DEFAULT_PATH=\"${CMAKE_CURRENT_SOURCE_DIR}/source/Shaders/glsl\")