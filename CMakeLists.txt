cmake_minimum_required(VERSION 3.16)
project(RenderingEngine LANGUAGES CXX C)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(DEPS_INCLUDE_DIR ${CMAKE_SOURCE_DIR}/Dependencies/includes)
set(CODE_SRC_DIR ${CMAKE_SOURCE_DIR}/source)

# --------------------------------------- Debug message toggle ---------------------------------------
add_compile_definitions(ENABLE_DEBUG_MESSAGES)
add_compile_definitions(TEXTURES_DEFAULT_PATH=\"${CMAKE_CURRENT_SOURCE_DIR}/Assets/resources/textures\")
add_compile_definitions(SHADER_SOURCE_DEFAULT_PATH=\"${CMAKE_CURRENT_SOURCE_DIR}/Assets/resources/glsl\")

## SUBMODULES
# Assets
add_subdirectory(Assets)

# Core
add_subdirectory(Core)

# ECS
add_subdirectory(ECS)

# Frontend
add_subdirectory(Frontend)

# Resource 
add_subdirectory(ResourceManagers)

# Top level source
set(SRC_FILES
    ${CODE_SRC_DIR}/main.cpp
    ${CORE_MOC_FILES}
)

# Add executable
add_executable(${PROJECT_NAME} ${SRC_FILES})

target_include_directories(${PROJECT_NAME} PRIVATE
    ${DEPS_INCLUDE_DIR}
    ${DEPS_INCLUDE_DIR}/glm
    ${DEPS_INCLUDE_DIR}/stb
)

target_compile_definitions(${PROJECT_NAME} PRIVATE PROJECT_NAME="\"${PROJECT_NAME}\"")

#target_compile_definitions(${PROJECT_NAME} PRIVATE GLAD_GL_IMPLEMENTATION)

if(MSVC)
    add_compile_options(/permissive-)
endif()

#target_compile_options(RenderingEngine PRIVATE /showIncludes) // Debugging

set_target_properties(${PROJECT_NAME} PROPERTIES
    CXX_STANDARD 20
    CXX_STANDARD_REQUIRED ON
    CXX_EXTENSIONS OFF
)

# QT
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

find_package(Qt6 REQUIRED COMPONENTS Widgets OpenGLWidgets)

# Link the precompiled GLFW and Windows OpenGL lib
target_link_libraries(${PROJECT_NAME}
    Qt6::OpenGLWidgets
    Qt6::Widgets
    AssetsLib
    ECSLib
    CoreLib
    FrontendLib
    ResourceManagersLib
    ShaderLib
)

# Set output directory
set_target_properties(${PROJECT_NAME} PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin
)

