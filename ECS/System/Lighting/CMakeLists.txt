add_library(LightingLib 
    source/LightingSystem.cpp
)

target_include_directories(LightingLib PUBLIC source)

target_link_libraries(LightingLib
    PUBLIC ShaderLib
    PUBLIC ComponentLib
    PUBLIC EntityLib
)