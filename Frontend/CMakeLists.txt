set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

add_library(FrontendLib
    source/MainWindow.cpp
    source/MainWindow.h
    source/Viewport.cpp
    source/Viewport.h
    ${CORE_MOC_FILES}
)

add_subdirectory(Displays)
add_subdirectory(Models)

find_package(Qt6 REQUIRED COMPONENTS Widgets OpenGLWidgets)

target_link_libraries(FrontendLib 
    PUBLIC 
        CoreLib
        DisplaysLib
        Qt6::OpenGLWidgets
        Qt6::Widgets
        ModelsLib
)

target_include_directories(FrontendLib 
    PUBLIC source
)

