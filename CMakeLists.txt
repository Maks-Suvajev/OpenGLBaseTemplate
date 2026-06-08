cmake_minimum_required(VERSION 3.16)
project(RenderingEngine LANGUAGES CXX C)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(DEPS_ASSIMP_DIR ${CMAKE_SOURCE_DIR}/Dependencies/assimp)
set(DEPS_INCLUDE_DIR ${CMAKE_SOURCE_DIR}/Dependencies/includes)

add_compile_options(-fdiagnostics-color=always)

# --------------------------------------- Debug message toggle ---------------------------------------
add_compile_definitions(ENABLE_DEBUG_MESSAGES)

add_compile_definitions(TEXTURES_DEFAULT_PATH=\"${CMAKE_CURRENT_SOURCE_DIR}/Assets/resources/textures\")
add_compile_definitions(SHADER_SOURCE_DEFAULT_PATH=\"${CMAKE_CURRENT_SOURCE_DIR}/Assets/resources/glsl/source\")

## SUBMODULES
set(BUILD_SHARED_LIBS OFF)

# Include ASSIMP
add_subdirectory(${DEPS_ASSIMP_DIR}
                 ${CMAKE_BINARY_DIR}/Dependencies/assimp
)

# Assets
add_subdirectory(Assets)

# Resource 
add_subdirectory(ResourceManagers)

# Core
add_subdirectory(Core)

# ECS
add_subdirectory(ECS)

# Frontend
add_subdirectory(Frontend)

# Top level source
set(SRC_FILES
    ${CMAKE_SOURCE_DIR}/source/main.cpp
)

# Add executable
add_executable(${PROJECT_NAME} ${SRC_FILES})

target_compile_definitions(${PROJECT_NAME} PRIVATE PROJECT_NAME="\"${PROJECT_NAME}\"")

# Link all required libs
target_link_libraries(${PROJECT_NAME}
    AssetsLib
    ECSLib
    CoreLib
    FrontendLib
    ResourceManagersLib
    ShaderLib
    SceneModelLib
)

# Set output directory
set_target_properties(${PROJECT_NAME} PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin
)

add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/ResourceManagers/Texture/defaults
        ${CMAKE_SOURCE_DIR}/bin/defaults
)