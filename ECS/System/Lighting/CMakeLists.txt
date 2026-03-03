add_library(LightingLib 
    source/LightingSystem.cpp
)

target_include_directories(LightingLib 
    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/source
)

target_link_libraries(LightingLib
    PUBLIC ShaderLib
    PUBLIC ComponentLib
    PUBLIC EntityLib
)