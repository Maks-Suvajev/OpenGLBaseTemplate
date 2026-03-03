add_library(TextureLib 
    source/TextureManager.cpp
)

find_package(Qt6 REQUIRED COMPONENTS OpenGL)

target_link_libraries(TextureLib 
    PUBLIC Qt6::OpenGL
    PUBLIC TypeLib
    PUBLIC AssetsLib
)

target_include_directories(TextureLib 
    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/source
    PUBLIC ${DEPS_INCLUDE_DIR}/stb    
)