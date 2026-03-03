add_library(MovementLib 
    source/MovementSystem.cpp
)

target_include_directories(MovementLib 
    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/source
)