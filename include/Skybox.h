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
#include <vector>

#include "SceneObject.hpp"
#include "../../glm-master/glm/glm.hpp"

#define SB_POS_ARRAY_SIZE 6 * 6 * 3
#define SB_IND_ARRAY_SIZE 6 * 6

class Skybox : public SceneObject
{
public:
    Skybox();
    ~Skybox();

protected:
    virtual void privateInit();
    virtual void privateRender();
    virtual void privateUpdate();

private:
    float positions_[SB_POS_ARRAY_SIZE] = {
        // Right face
         1.0f, -1.0f, -1.0f,
         1.0f, -1.0f,  1.0f,
         1.0f,  1.0f,  1.0f,
         1.0f,  1.0f,  1.0f,
         1.0f,  1.0f, -1.0f,
         1.0f, -1.0f, -1.0f,

        // Left face
        -1.0f, -1.0f,  1.0f,
        -1.0f, -1.0f, -1.0f,
        -1.0f,  1.0f, -1.0f,
        -1.0f,  1.0f, -1.0f,
        -1.0f,  1.0f,  1.0f,
        -1.0f, -1.0f,  1.0f,

        // Top face
        -1.0f,  1.0f, -1.0f,
         1.0f,  1.0f, -1.0f,
         1.0f,  1.0f,  1.0f,
         1.0f,  1.0f,  1.0f,
        -1.0f,  1.0f,  1.0f,
        -1.0f,  1.0f, -1.0f,

        // Bottom face
        -1.0f, -1.0f, -1.0f,
        -1.0f, -1.0f,  1.0f,
         1.0f, -1.0f, -1.0f,
         1.0f, -1.0f, -1.0f,
        -1.0f, -1.0f,  1.0f,
         1.0f, -1.0f,  1.0f,

        // North face
        -1.0f,  1.0f, -1.0f,
        -1.0f, -1.0f, -1.0f,
         1.0f, -1.0f, -1.0f,
         1.0f, -1.0f, -1.0f,
         1.0f,  1.0f, -1.0f,
        -1.0f,  1.0f, -1.0f,

        // South face
        -1.0f, -1.0f,  1.0f,
        -1.0f,  1.0f,  1.0f,
         1.0f,  1.0f,  1.0f,
         1.0f,  1.0f,  1.0f,
         1.0f, -1.0f,  1.0f,
        -1.0f, -1.0f,  1.0f,


    };

    unsigned int indices_[SB_IND_ARRAY_SIZE] = {
        0, 1, 2, 3, 4, 5,
        6, 7, 8, 9, 10, 11,
        12, 13, 14, 15, 16, 17,
        18, 19, 20, 21, 22, 23,
        24, 25, 26, 27, 28, 29,
        30, 31, 32, 33, 34, 35
    };

    VertexArray vao;
    VertexBuffer vbo = VertexBuffer(positions_, SB_POS_ARRAY_SIZE * sizeof(float));
    VertexBufferLayout layout;
    IndexBuffer ibo = IndexBuffer(indices_, SB_IND_ARRAY_SIZE);
    Shader shader = Shader("C:/dev/uni/DTE-3609_VR_graphics_animation/start_code/resources/shaders/Skybox_vertex.shader",
                           "C:/dev/uni/DTE-3609_VR_graphics_animation/start_code/resources/shaders/Skybox_fragment.shader");
    std::vector<std::string> faceTextures{
        "C:/dev/uni/DTE-3609_VR_graphics_animation/start_code/resources/textures/skybox_east.bmp",
        "C:/dev/uni/DTE-3609_VR_graphics_animation/start_code/resources/textures/skybox_west.bmp",
        "C:/dev/uni/DTE-3609_VR_graphics_animation/start_code/resources/textures/skybox_up.bmp",
        "C:/dev/uni/DTE-3609_VR_graphics_animation/start_code/resources/textures/skybox_down.bmp",
        "C:/dev/uni/DTE-3609_VR_graphics_animation/start_code/resources/textures/skybox_north.bmp",
        "C:/dev/uni/DTE-3609_VR_graphics_animation/start_code/resources/textures/skybox_south.bmp"
    };
    Texture texture = Texture(faceTextures);
    unsigned int textureSlot = 0;
};

