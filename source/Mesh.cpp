#include "Mesh.h"


namespace gfx
{

Mesh::Mesh(MeshData&& initData)
{

    #ifdef ENABLE_DEBUG_MESSAGES
        std::cout << "Vertices size = " << initData.vertices.size() << std::endl;
    #endif
    
    // VAO init and bind
    glGenVertexArrays(1, &gpuHandles.VAO);
    glBindVertexArray(gpuHandles.VAO);            

    // VBO init and bind
    glGenBuffers(1, &gpuHandles.VBO);
    glBindBuffer(GL_ARRAY_BUFFER, gpuHandles.VBO);
    glBufferData(GL_ARRAY_BUFFER, initData.vertices.size() * sizeof(float), initData.vertices.data(), GL_STATIC_DRAW);

    gpuHandles.useEBO = false;

    if (!initData.indices.empty())
    { 
        // EBO init bind
        glGenBuffers(1, &gpuHandles.EBO);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, gpuHandles.EBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, initData.indices.size() * sizeof(unsigned int), initData.indices.data(), GL_STATIC_DRAW);
        
        gpuHandles.useEBO = true;

        #ifdef ENABLE_DEBUG_MESSAGES
            std::cout << "DEBUG::No indices found - not populating EBO" << std::endl;
        #endif

    }
    // Define VAO attributes

    // Define position coords
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
    glEnableVertexAttribArray(2);

    // // Define texture coordinates
    // glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*) (3 * sizeof(float)));
    // glEnableVertexAttribArray(1);

    #ifdef ENABLE_DEBUG_MESSAGES
        std::cout << "DEBUG::Finished mesh init" << std::endl;
    #endif
}

// void Mesh::drawMesh()
// {
//     bindVAO();

//     glDrawArrays(GL_TRIANGLES, 0, 36);

// }

// void Mesh::bindVAO()
// {
//     glBindVertexArray(VAO);
// }

}