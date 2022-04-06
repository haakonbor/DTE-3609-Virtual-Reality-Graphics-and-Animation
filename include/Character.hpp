#pragma once

#include <windows.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include "SceneObject.hpp"

class Character : public SceneObject
{
    public:
        Character();
        ~Character();
        void increaseSpeed();
        void decreaseSpeed();

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

        float size_ = 50.0f;

        int list_id_;
        float speed_;
        float life_;
        float armor_;
    
};

