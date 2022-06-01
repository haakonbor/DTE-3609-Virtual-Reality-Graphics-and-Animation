#pragma once

#include "../include/VertexArray.h"
#include "../include/VertexBuffer.h"
#include "../include/VertexBufferLayout.h"
#include "../include/IndexBuffer.h"
#include "../include/Shader.h"
#include "../include/Texture.h"

#include <windows.h>
#include <GL/freeglut.h>
#include <GL/glu.h>

#include "SceneObject.hpp"
#include "../../glm-master/glm/glm.hpp"

// 4 points with 3D position and 2D texture position
#define LS_POS_ARRAY_SIZE 4 * (3 + 3 + 2)
#define LS_IND_ARRAY_SIZE 4

class Plane : public SceneObject
{
public:
    Plane(glm::vec3 trans, glm::vec3 rotationAxis = glm::vec3(0.0f, 0.0f, 0.0f),
          float rotationAngle = 0.0f, glm::vec3 scale = glm::vec3(1.0f, 1.0f, 1.0f));
    ~Plane();

protected:
    virtual void privateInit();
    virtual void privateRender();
    virtual void privateUpdate();

private:
    // vertex array
    std::vector< glm::vec3 > vertexArray_;
    // normal array.
    std::vector< glm::vec3 > normalArray_;
    // texture coord array
    std::vector< glm::vec3 > textureArray_;

    float positions_[LS_POS_ARRAY_SIZE] = {
        -100.0f,0.0f, 100.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f,
        100.0f, 0.0f, 100.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f,
        100.0f, 0.0f, -100.0f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f,
        -100.0f,0.0f, -100.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
    };

    unsigned int indices_[LS_IND_ARRAY_SIZE] = {
        0, 1, 2, 3,
    };

    VertexArray vao;
    VertexBuffer vbo = VertexBuffer(positions_, LS_POS_ARRAY_SIZE * sizeof(float));
    VertexBufferLayout layout;
    IndexBuffer ibo = IndexBuffer(indices_, LS_IND_ARRAY_SIZE);
    Shader shader = Shader("C:/dev/uni/DTE-3609_VR_graphics_animation/start_code/resources/shaders/Plane_vertex.shader",
                           "C:/dev/uni/DTE-3609_VR_graphics_animation/start_code/resources/shaders/Plane_fragment.shader");
    Texture texture1 = Texture("C:/dev/uni/DTE-3609_VR_graphics_animation/start_code/resources/textures/road.jpg");
    Texture texture2 = Texture("C:/dev/uni/DTE-3609_VR_graphics_animation/start_code/resources/textures/dirt.jpg");
    unsigned int textureSlot1 = 0;
    unsigned int textureSlot2 = 1;
    float scaling;
};

