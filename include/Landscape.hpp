#pragma once

#include "../include/VertexArray.h"
#include "../include/VertexBuffer.h"
#include "../include/VertexBufferLayout.h"
#include "../include/IndexBuffer.h"

#include <windows.h>
#include <GL/freeglut.h>
//#include <GL/gl.h>
#include <GL/glu.h>

#include "SceneObject.hpp"
#include "../../glm-master/glm/glm.hpp"

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

    float positions_[3 * 4 * 4] = {
        // Left plane
        -100.0f, -50.0f, 50.0f,
        0.0f, -50.0f, 50.0f,
        0.0f, -50.0f, -50.0f,
        -100.0f, -50.0f, -50.0f,

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

    unsigned int indices_[4 * 3] = {
        0, 1, 2, 3,
        4, 5, 6, 7,
        8, 9, 10, 11
    };

    VertexArray vao;
    VertexBuffer vbo;
    VertexBufferLayout layout;
    IndexBuffer ibo;
};

