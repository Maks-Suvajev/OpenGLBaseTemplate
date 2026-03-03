add_library(ECSLib INTERFACE)

add_subdirectory(Component)
add_subdirectory(Entity)
add_subdirectory(System)

target_link_libraries(ECSLib INTERFACE
    EntityLib
    ComponentLib
    SystemLib
)
