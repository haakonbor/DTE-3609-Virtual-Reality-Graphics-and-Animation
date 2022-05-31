#pragma once

#include <windows.h>
//#include <GL/gl.h>
//#include <GL/glu.h>
#include "SceneObject.hpp"
#include "../include/VertexArray.h"
#include "../include/VertexBuffer.h"
#include "../include/VertexBufferLayout.h"
#include "../include/IndexBuffer.h"
#include "../include/Shader.h"

enum characterStates {
    normal = 0,
    colliding = 1,
};

#define CH_POS_ARRAY_SIZE 6 * 4 * (3 + 3)
#define CH_IND_ARRAY_SIZE 6 * 4

class Character : public SceneObject
{
    public:
        Character(glm::vec3 trans);
        ~Character();
        void moveLeft();
        void moveRight();

        glm::vec3 getPosition() { return position_; }
        float getSize() { return size_; }
        int getState() { return state_; }
        float getCurrentLife() { return life_; }
        float getMaxLife() { return maxLife_; }

        void setColor(float r, float g, float b) { color_[0] = r, color_[1] = g, color_[2] = b; }
        void setState(int newState) { state_ = newState; }
        void reduceLife() { life_ -= 0.3f; }
        void upgradeAndHeal();

    protected:
        void privateInit();
        void privateRender();
        void privateUpdate();

        void setUpVertices();
        void setUpNormals();
        void createNormalLineList();
        void setUpLighting();
        void setUpTextures();

        void setUpHealthbar();
        void setUpHBVertices();
        void setUpHBTextures();

        void renderCube();
        void renderNormals();
        void renderHealthbar();

	private:
        const float size_ = 30.0f;

        float positions_[CH_POS_ARRAY_SIZE] = {
            // Right face
            size_, -size_,  size_, 1.0f, 0.0f, 0.0f,
            size_, -size_, -size_, 1.0f, 0.0f, 0.0f,
            size_,  size_, -size_, 1.0f, 0.0f, 0.0f,
            size_,  size_,  size_, 1.0f, 0.0f, 0.0f,

            // Left face
            -size_, -size_, -size_, -1.0f, 0.0f, 0.0f,
            -size_, -size_, size_, -1.0f, 0.0f, 0.0f,
            -size_,  size_, size_, -1.0f, 0.0f, 0.0f,
            -size_,  size_, -size_, -1.0f, 0.0f, 0.0f,

            // Top face
            -size_, size_,  size_, 0.0f, 1.0f, 0.0f,
            size_, size_, size_, 0.0f, 1.0f, 0.0f,
            size_,  size_, -size_, 0.0f, 1.0f, 0.0f,
            -size_,  size_, -size_, 0.0f, 1.0f, 0.0f,

            // Bottom face
            -size_, -size_,  -size_, 0.0f, -1.0f, 0.0f,
            size_, -size_, -size_,  0.0f, -1.0f, 0.0f,
            size_,  -size_, size_,  0.0f, -1.0f, 0.0f,
            -size_,  -size_, size_,  0.0f, -1.0f, 0.0f,

            // North face
            size_, -size_,  -size_,  0.0f, 0.0f, -1.0f,
            -size_, -size_, -size_, 0.0f, 0.0f, -1.0f,
            -size_,  size_, -size_, 0.0f, 0.0f, -1.0f,
            size_,  size_, -size_, 0.0f, 0.0f, -1.0f,

            // South Face
            -size_, -size_,  size_, 0.0f, 0.0f, 1.0f,
            size_, -size_,  size_, 0.0f, 0.0f, 1.0f,
            size_,  size_,  size_, 0.0f, 0.0f, 1.0f,
            -size_,  size_,  size_, 0.0f, 0.0f, 1.0f,
        };

        unsigned int indices_[CH_IND_ARRAY_SIZE] = {
            0, 1, 2, 3,
            4, 5, 6, 7,
            8, 9, 10, 11,
            12, 13, 14, 15,
            16, 17, 18, 19,
            20, 21, 22, 23
        };

        VertexArray vao;
        VertexBuffer vbo = VertexBuffer(positions_, CH_POS_ARRAY_SIZE * sizeof(float));
        VertexBufferLayout layout;
        IndexBuffer ibo = IndexBuffer(indices_, CH_IND_ARRAY_SIZE);
        Shader shader = Shader("C:/dev/uni/DTE-3609_VR_graphics_animation/start_code/resources/shaders/Character_vertex.shader",
                               "C:/dev/uni/DTE-3609_VR_graphics_animation/start_code/resources/shaders/Character_fragment.shader");

        std::vector< glm::vec3 > vertexArray_;
        std::vector< glm::vec3 > normalArray_;
        std::vector< glm::vec3 > sharedNormalArray_;
        std::vector< glm::vec3 > textureArray_;

        std::vector< glm::vec3 > healthbarVertexArray_;
        std::vector< glm::vec2 > healthbarTextureArray_;

        unsigned int texture;

        glm::vec3 position_;

        int state_ = characterStates::normal;

        int list_id_;
        float speed_ = 0;
        float life_ = 1.0f;
        float maxLife_ = 1.0f;
        float color_[3] = {0.0f, 1.0f, 0.0f};
};

