cmake_minimum_required(VERSION 3.10)
project(OpenGLProject LANGUAGES CXX C)

set(CMAKE_CXX_STANDARD 17)

# Set base paths
set(DEPS_INCLUDE_DIR ${CMAKE_SOURCE_DIR}/dependencies/includes)
set(DEPS_LIB_DIR ${CMAKE_SOURCE_DIR}/dependencies/libs)
set(DEPS_SRC_DIR ${CMAKE_SOURCE_DIR}/dependencies/source)


#target_compile_definitions(${PROJECT_NAME} PRIVATE GLAD_GL_IMPLEMENTATION)

# Add source files
set(SRC_FILES
    source/main.cpp
    source/shader.cpp
    ${DEPS_SRC_DIR}/glad/glad.c
)

set_source_files_properties(${DEPS_SRC_DIR}/glad/glad.c PROPERTIES LANGUAGE C)

# Add executable
add_executable(${PROJECT_NAME} ${SRC_FILES})

# Modern include style
target_include_directories(${PROJECT_NAME} PRIVATE
    ${DEPS_INCLUDE_DIR}
    ${DEPS_INCLUDE_DIR}/glad
    ${DEPS_INCLUDE_DIR}/GLFW
    ${DEPS_INCLUDE_DIR}/glm
    ${DEPS_INCLUDE_DIR}/KHR
    ${DEPS_INCLUDE_DIR}/stb
)

target_compile_definitions(${PROJECT_NAME} PRIVATE GLAD_GL_IMPLEMENTATION)

# Link the precompiled GLFW and Windows OpenGL lib
target_link_libraries(${PROJECT_NAME}
    ${DEPS_LIB_DIR}/GLFW/glfw3.lib
    opengl32
)

# Set output directory
set_target_properties(${PROJECT_NAME} PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin
)