#ifndef TEXTURE_LOADER_H
#define TEXTURE_LOADER_H

#include <glad/glad.h>
#include <filesystem>


namespace gfx {

    GLuint loadTexture(const std::filesystem::path& texturePath);

};

#endif