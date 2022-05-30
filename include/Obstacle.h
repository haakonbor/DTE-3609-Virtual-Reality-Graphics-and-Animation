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
#define OB_POS_ARRAY_SIZE 6 * 4 * 3
#define OB_IND_ARRAY_SIZE 6 * 4

class Obstacle : public SceneObject
{
public:
    Obstacle(glm::vec3 trans, glm::vec3 rotationAxis, float rotationAngle);
    ~Obstacle();

    glm::vec3 getPosition() { return position_; }
    float getSize() { return size_; }

protected:
    virtual void privateInit();
    virtual void privateRender();
    virtual void privateUpdate();

private:
    const float size_ = 50.0f;

    float positions_[OB_POS_ARRAY_SIZE] = {
        // Right face
        size_, -size_,  size_,
        size_, -size_, -size_,
        size_,  size_, -size_,
        size_,  size_,  size_,

        // Left face
        -size_, -size_, -size_,
        -size_, -size_, size_,
        -size_,  size_, size_,
        -size_,  size_, -size_,

        // Top face
        -size_, size_,  size_,
        size_, size_, size_,
        size_,  size_, -size_,
        -size_,  size_, -size_,

        // Bottom face
        -size_, -size_,  -size_,
        size_, -size_, -size_,
        size_,  -size_, size_,
        -size_,  -size_, size_,

        // North face
        size_, -size_,  -size_,
        -size_, -size_, -size_,
        -size_,  size_, -size_,
        size_,  size_, -size_,

        // South Face
        -size_, -size_,  size_,
        size_, -size_,  size_,
        size_,  size_,  size_,
        -size_,  size_,  size_,
    };

    unsigned int indices_[OB_IND_ARRAY_SIZE] = {
        0, 1, 2, 3,
        4, 5, 6, 7,
        8, 9, 10, 11,
        12, 13, 14, 15,
        16, 17, 18, 19,
        20, 21, 22, 23
    };

    VertexArray vao;
    VertexBuffer vbo = VertexBuffer(positions_, OB_POS_ARRAY_SIZE * sizeof(float));
    VertexBufferLayout layout;
    IndexBuffer ibo = IndexBuffer(indices_, OB_IND_ARRAY_SIZE);
    Shader shader = Shader("C:/dev/uni/DTE-3609_VR_graphics_animation/start_code/resources/shaders/Obstacle_vertex.shader",
                           "C:/dev/uni/DTE-3609_VR_graphics_animation/start_code/resources/shaders/Obstacle_fragment.shader");
    std::vector<std::string> faceTextures{
        "C:/dev/uni/DTE-3609_VR_graphics_animation/start_code/resources/textures/rock.png",
        "C:/dev/uni/DTE-3609_VR_graphics_animation/start_code/resources/textures/rock.png",
        "C:/dev/uni/DTE-3609_VR_graphics_animation/start_code/resources/textures/rock.png",
        "C:/dev/uni/DTE-3609_VR_graphics_animation/start_code/resources/textures/rock.png",
        "C:/dev/uni/DTE-3609_VR_graphics_animation/start_code/resources/textures/rock.png",
        "C:/dev/uni/DTE-3609_VR_graphics_animation/start_code/resources/textures/rock.png"
    };
    Texture texture = Texture(faceTextures);
    unsigned int textureSlot = 0;
    float scaling;

    glm::vec3 position_;
    float speed_ = -3.0f;
};

