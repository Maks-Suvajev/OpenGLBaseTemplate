add_library(CameraLib 
    source/Camera.cpp
)

target_include_directories(CameraLib 
    PUBLIC source
    PUBLIC ${DEPS_INCLUDE_DIR}
)