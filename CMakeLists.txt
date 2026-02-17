cmake_minimum_required(VERSION 3.16)
project(RenderingEngine LANGUAGES CXX C)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Set base paths
set(DEPS_INCLUDE_DIR ${CMAKE_SOURCE_DIR}/Dependencies/includes)
set(DEPS_LIB_DIR ${CMAKE_SOURCE_DIR}/Dependencies/libs)
set(DEPS_SRC_DIR ${CMAKE_SOURCE_DIR}/Dependencies/source)
set(SHADER_SRC_DIR ${CMAKE_SOURCE_DIR}/Shaders/class)
set(ASSETS_SRC_DIR ${CMAKE_SOURCE_DIR}/Assets/source)

# Add source files
set(SRC_FILES
    source/main.cpp
    source/Camera.cpp
	source/Mesh.cpp
	source/TextureManager.cpp
	source/Renderer.cpp
    source/RenderSystem.cpp
    source/LightingSystem.cpp
    source/Movement.cpp
	source/EntityManager.cpp
    source/MeshManager.cpp
    source/MaterialManager.cpp
    source/Material.cpp
    source/Test.cpp

    #QT stuff
    source/MainWindow.h
    source/MainWindow.cpp
    source/Viewport.cpp


    ${SHADER_SRC_DIR}/shader.cpp
	${SHADER_SRC_DIR}/shaderManager.cpp
	${ASSETS_SRC_DIR}/GfxAssetsManager.cpp
)

# QT INTEGRATION
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

find_package(Qt6 REQUIRED COMPONENTS Widgets OpenGLWidgets)

set_source_files_properties(${DEPS_SRC_DIR}/glad/glad.c PROPERTIES LANGUAGE C)

# Add executable
add_executable(${PROJECT_NAME} ${SRC_FILES})

# Modern include style
target_include_directories(${PROJECT_NAME} PRIVATE
    ${DEPS_INCLUDE_DIR}
    ${DEPS_INCLUDE_DIR}/glm
    ${DEPS_INCLUDE_DIR}/KHR
    ${DEPS_INCLUDE_DIR}/stb
	${SHADER_SRC_DIR}
	${ASSETS_SRC_DIR}

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
add_compile_definitions(TEXTURES_DEFAULT_PATH=\"${CMAKE_CURRENT_SOURCE_DIR}/Assets/textures\")
add_compile_definitions(SHADER_SOURCE_DEFAULT_PATH=\"${CMAKE_CURRENT_SOURCE_DIR}/Shaders/glsl\")