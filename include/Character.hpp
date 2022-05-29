#pragma once

#include <windows.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include "SceneObject.hpp"

enum characterStates {
    normal = 0,
    colliding = 1,
};

class Character : public SceneObject
{
    public:
        Character(glm::vec3 trans);
        ~Character();
        void increaseSpeed();
        void decreaseSpeed();

        glm::vec3 getPosition() { return position_; }
        float getSize() { return size_; }
        float getState() { return state_; }

        void setColor(float r, float g, float b) { color_[0] = r, color_[1] = g, color_[2] = b; }
        void setState(int newState) { state_ = newState; }

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
        std::vector< glm::vec3 > vertexArray_;
        std::vector< glm::vec3 > normalArray_;
        std::vector< glm::vec3 > sharedNormalArray_;
        std::vector< glm::vec3 > textureArray_;

        std::vector< glm::vec3 > healthbarVertexArray_;
        std::vector< glm::vec2 > healthbarTextureArray_;

        unsigned int texture;
        float color_[3] = {1.0f, 0.0f, 0.0f};

        glm::vec3 position_;
        float size_ = 50.0f;

        int state_ = characterStates::normal;

        int list_id_;
        float speed_ = 0;
        float life_;
        float armor_;


    
};

