#ifndef VAO_GROUP_H
#define VAO_GROUP_H

#include <vector>

#include "RenderObject.h"
#include "Shader.h"
#include "Window.h"

namespace gfx {

template<typename T>
struct PositionAndTextureInstance
{
    T position;
    std::vector<uint32_t> textureIndices; 
};

template<typename T>
struct VAOGroupData
{   
    std::vector<float> vertices;
    std::vector<unsigned int> indices;
    std::vector<PositionAndTextureInstance<T>> instanceData;
};

template<typename T>
class VAOGroup
{
    public:

        VAOGroup(VAOGroupData<T>&& initGroup)
        {
            // VAO init and bind
            glGenVertexArrays(1, &VAO);
            glBindVertexArray(VAO);            

            // VBO init and bind
            glGenBuffers(1, &VBO);
            glBindBuffer(GL_ARRAY_BUFFER, VBO);
            glBufferData(GL_ARRAY_BUFFER, initGroup.vertices.size() * sizeof(float), initGroup.vertices.data(), GL_STATIC_DRAW);

            // EBO init bind
            glGenBuffers(1, &EBO);
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
            glBufferData(GL_ELEMENT_ARRAY_BUFFER, initGroup.indices.size() * sizeof(unsigned int), initGroup.indices.data(), GL_STATIC_DRAW);

            // Define VAO attributes

            // Define position coords
            glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
            glEnableVertexAttribArray(0);

            // Define texture coordinates
            glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*) (3 * sizeof(float)));
            glEnableVertexAttribArray(1);

            for (const auto& instance : initGroup.instanceData)
            {
                // make unique ptr
                RenderObject<T> * newInstance = new RenderObject<T>(instance);
                instanceList.push_back(newInstance);
            }
        }


        static std::unique_ptr<VAOGroup<T>> create(VAOGroupData<T>&& initGroup)
        {
            return std::make_unique<VAOGroup<T>>(std::move(initGroup));
        }

        void bindVAO();
        void drawGroup(Shader& shaderInstance, Window& windowInstance);


    private:
        GLuint VAO;
        GLuint VBO;
        GLuint EBO;

        std::vector<RenderObject<T>*> instanceList;
};

template<typename T>
void VAOGroup<T>::bindVAO()
{
    glBindVertexArray(VAO);
}

template<typename T>
void VAOGroup<T>::drawGroup(Shader& shaderInstance, Window& windowInstance)
{
    bindVAO();

    uint16_t instanceRotation = 0;
    float rotationAngle = 0;

    for (auto& instance : instanceList)
    {
        glm::mat4 model = glm::mat4(1.0f);

        model = glm::translate(model, instance->getPosition());

        if (instanceRotation == 0 || instanceRotation % 3 == 0)
        {
            rotationAngle = 20.0f * instanceRotation * static_cast<float>(glfwGetTime());
        }
        else
        {
            rotationAngle = 20.0f * instanceRotation;
        }

        ++instanceRotation;

        model = glm::rotate(model, glm::radians(rotationAngle), glm::vec3(1.0f, 0.3f, 0.5f));

        shaderInstance.updateModelMatrixValue(model);

        glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0); // TODO: Inefficient - need to batch render in future
    }
}

}


#endif