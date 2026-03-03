add_library(MaterialLib 
    source/Material.cpp
    source/MaterialManager.cpp
)

target_link_libraries(MaterialLib
    PRIVATE TypeLib
)

target_include_directories(MaterialLib 
    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/source
)