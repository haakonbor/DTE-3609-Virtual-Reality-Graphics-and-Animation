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

// 4 points with 2D position and 2D texture position
#define BB_POS_ARRAY_SIZE 4 * (3+2) //(2 + 2)
#define BB_IND_ARRAY_SIZE 4

class Billboard : public SceneObject
{
public:
    Billboard();
    ~Billboard();

    void setState(bool toDraw) { draw_ = toDraw; }

protected:
    virtual void privateInit();
    virtual void privateRender();
    virtual void privateUpdate();

private:
//    const float size_ = 50.0f;

    float positions_[BB_POS_ARRAY_SIZE] = {
        -1.0f, -1.0f, 0.0f, 0.0f, 0.0f,
        1.0f, -1.0f, 0.0f, 1.0f, 0.0f,
        1.0f, 1.0f, 0.0f, 1.0f, 1.0f,
        -1.0f, 1.0f, 0.0f, 0.0f, 1.0f
    };

    unsigned int indices_[BB_IND_ARRAY_SIZE] = {
        0, 1, 2, 3,
    };

    VertexArray vao;
    VertexBuffer vbo = VertexBuffer(positions_, BB_POS_ARRAY_SIZE * sizeof(float));
    VertexBufferLayout layout;
    IndexBuffer ibo = IndexBuffer(indices_, BB_IND_ARRAY_SIZE);
    Shader shader = Shader("C:/dev/uni/DTE-3609_VR_graphics_animation/start_code/resources/shaders/Billboard_vertex.shader",
                           "C:/dev/uni/DTE-3609_VR_graphics_animation/start_code/resources/shaders/Billboard_fragment.shader");

    Texture texture = Texture("C:/dev/uni/DTE-3609_VR_graphics_animation/start_code/resources/textures/gameover.jpg");
    unsigned int textureSlot = 0;
    bool draw_ = false;
};

