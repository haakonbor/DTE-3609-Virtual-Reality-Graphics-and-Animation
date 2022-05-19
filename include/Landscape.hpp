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
#define POS_ARRAY_SIZE 4 * 4 * 3 //4 * 4 * (3 + 2)
#define IND_ARRAY_SIZE 4 * 4 //4 * 4

class Landscape : public SceneObject
{
public:
    Landscape();
    ~Landscape();

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

    float positions_[POS_ARRAY_SIZE] = {
//        -0.5f, -0.5f, 0.0f,
//        0.5f, -0.5f, 3.0f,
//        0.5f, 0.5f, 3.0f,
//        -0.5f, 0.5f, 0.0f
        // Left plane
        -100.0f, -50.0f, 100.0f, //0.0f, 0.0f,
        100.0f, -50.0f, 100.0f, //1.0f, 0.0f,
        100.0f, -50.0f, -100.0f, //1.0f, 1.0f,
        -100.0f, -50.0f, -100.0f, //0.0f, 1.0f,

        // Middle plane
        0.0f, -50.0f, 50.0f,
        100.0f, -50.0f, 50.0f,
        100.0f, -50.0f, -50.0f,
        0.0f, -50.0f, -50.0f,

        // Right plane
        100.0f, -50.0f, 50.0f,
        200.0f, -50.0f, 50.0f,
        200.0f, -50.0f, -50.0f,
        100.0f, -50.0f, -50.0f,

        // Background
        -1000.0f, -1000.0f, -500.0f,
        1000.0f, -1000.0f, -500.0f,
        1000.0f, 1000.0f, -500.0f,
        -1000.0f, 1000.0f, -500.0f
    };

    unsigned int indices_[IND_ARRAY_SIZE] = {
        0, 1, 2, 3,
        4, 5, 6, 7,
        8, 9, 10, 11,
        12, 13, 14, 15
    };

    VertexArray vao;
    VertexBuffer vbo = VertexBuffer(positions_, POS_ARRAY_SIZE * sizeof(float));
    VertexBufferLayout layout;
    IndexBuffer ibo = IndexBuffer(indices_, IND_ARRAY_SIZE);
    Shader shader = Shader("C:/dev/uni/DTE-3609_VR_graphics_animation/start_code/resources/shaders/Vertex.shader",
                           "C:/dev/uni/DTE-3609_VR_graphics_animation/start_code/resources/shaders/Fragment.shader");
    Texture texture = Texture("C:/dev/uni/DTE-3609_VR_graphics_animation/start_code/resources/textures/color.jpg");
};

