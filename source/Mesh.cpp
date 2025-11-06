#include "Mesh.h"


namespace gfx
{

    Mesh::Mesh(MeshData initData)
    {
            // VAO init and bind
            glGenVertexArrays(1, &VAO);
            glBindVertexArray(VAO);            

            // VBO init and bind
            glGenBuffers(1, &VBO);
            glBindBuffer(GL_ARRAY_BUFFER, VBO);
            glBufferData(GL_ARRAY_BUFFER, initData.vertices.size() * sizeof(float), initData.vertices.data(), GL_STATIC_DRAW);

            // EBO init bind
            glGenBuffers(1, &EBO);
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
            glBufferData(GL_ELEMENT_ARRAY_BUFFER, initData.indices.size() * sizeof(unsigned int), initData.indices.data(), GL_STATIC_DRAW);

            // Define VAO attributes

            // Define position coords
            glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
            glEnableVertexAttribArray(0);

            // Define texture coordinates
            glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*) (3 * sizeof(float)));
            glEnableVertexAttribArray(1);
    }
































}