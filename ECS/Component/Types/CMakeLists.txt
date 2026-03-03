add_library(TypeLib INTERFACE)

find_package(Qt6 REQUIRED COMPONENTS OpenGL)

target_link_libraries(TypeLib INTERFACE
    Qt6::OpenGL
)

target_include_directories(TypeLib INTERFACE 
    "${CMAKE_CURRENT_SOURCE_DIR}/source"
)

