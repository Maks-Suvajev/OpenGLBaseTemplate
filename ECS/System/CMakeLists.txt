add_library(SystemLib INTERFACE)

add_subdirectory(Camera)
add_subdirectory(Lighting)
add_subdirectory(Movement)
add_subdirectory(Render)

target_link_libraries(SystemLib INTERFACE
    CameraLib
    LightingLib
    MovementLib
    RenderLib
)
