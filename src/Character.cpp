
#include "../include/Character.hpp"
#include "../../glm-master/glm/glm.hpp"
#include "../../glm-master/glm/gtc/matrix_transform.hpp"
#include "../include/Utils.hpp"
#include "../include/stb_image.h"

#include <iostream>
#include <fstream>

Character::Character()
{
    list_id_ = glGenLists(1);
}

Character::~Character()
{
}

void Character::privateInit()
{   
    speed_ = 1.0f;

    setUpVertices();

    createNormalLineList();

    setUpLighting();

    //setUpTextures();

    setUpHealthbar();


    GLenum err = glGetError();
    if (err != GL_NO_ERROR)
      std::cout<< "OpenGL error: " << gluErrorString(err) << std::endl;
    std::cout.flush();
}

void Character::privateRender()
{
    // Enable stuff
    //glEnable(GL_LIGHTING);
    //glEnable(GL_LIGHT0);
    //glEnable(GL_LIGHT1);
    //glEnable(GL_COLOR_MATERIAL);
    glEnable(GL_FOG);
    glFogi(GL_FOG_MODE, GL_LINEAR);
    glFogf(GL_FOG_START, 1.0f);
    glFogf(GL_FOG_END, 500.0f);
    GLfloat fog_color[4] = {0.5, 0.5, 0.5, 1.0};
    glFogfv(GL_FOG_COLOR, fog_color);

    // Draw cube
    renderCube();

    // Draw normal lines of cube
    renderNormals();

    // Draw healthbar
    renderHealthbar();

    // Disable stuff
    //glDisable(GL_LIGHT1);
    //glDisable(GL_LIGHTING);
    //glDisable(GL_LIGHT0);
    //glDisable(GL_COLOR_MATERIAL);
    glDisable(GL_FOG);

    GLenum err = glGetError();
    if (err != GL_NO_ERROR)
      std::cout<< "OpenGL error: " << gluErrorString(err) << std::endl;
    std::cout.flush();

}

void Character::renderCube()
{
    glColor3f(1.0f, 0.0f, 0.0f);
    glEnableClientState(GL_NORMAL_ARRAY);
    glNormalPointer(GL_FLOAT, 0, normalArray_.data());
    glDisableClientState(GL_NORMAL_ARRAY);

    glEnableClientState(GL_VERTEX_ARRAY);
    glVertexPointer(3, GL_FLOAT, 0, vertexArray_.data());
    glDrawArrays(GL_QUADS, 0, 24);
    glDisableClientState(GL_VERTEX_ARRAY);
}

void Character::renderNormals()
{
    glColor3f(0.0f, 0.0f, 1.0f);
    glCallList(list_id_);
}

void Character::renderHealthbar()
{
    glEnable(GL_TEXTURE_2D);

    glBindTexture(GL_TEXTURE_2D, texture);
    glEnableClientState(GL_TEXTURE_COORD_ARRAY);
    glTexCoordPointer(2, GL_FLOAT, 0, healthbarTextureArray_.data());

    glColor3f(1.0f, 1.0f, 1.0f);
    glEnableClientState(GL_VERTEX_ARRAY);
    glVertexPointer(3, GL_FLOAT, 0, healthbarVertexArray_.data());
    glDrawArrays(GL_QUADS, 0, 4);
    glDisableClientState(GL_VERTEX_ARRAY);

    glDisableClientState(GL_TEXTURE_COORD_ARRAY);
    glBindTexture(GL_TEXTURE_2D, 0);

    glDisable(GL_TEXTURE_2D);

}

void Character::setUpVertices()
{
    // Front Face
    vertexArray_.push_back(glm::vec3(-size_, -size_,  size_));
    vertexArray_.push_back(glm::vec3( size_, -size_,  size_));
    vertexArray_.push_back(glm::vec3( size_,  size_,  size_));
    vertexArray_.push_back(glm::vec3(-size_,  size_,  size_));

    // Right Face
    vertexArray_.push_back(glm::vec3( size_, -size_,  size_));
    vertexArray_.push_back(glm::vec3( size_, -size_, -size_));
    vertexArray_.push_back(glm::vec3( size_,  size_, -size_));
    vertexArray_.push_back(glm::vec3(size_,  size_,  size_));

    // Top Face
    vertexArray_.push_back(glm::vec3( -size_, size_,  size_));
    vertexArray_.push_back(glm::vec3( size_, size_, size_));
    vertexArray_.push_back(glm::vec3( size_,  size_, -size_));
    vertexArray_.push_back(glm::vec3(-size_,  size_, -size_));

    // Left Face
    vertexArray_.push_back(glm::vec3( -size_, -size_,  -size_));
    vertexArray_.push_back(glm::vec3( -size_, -size_, size_));
    vertexArray_.push_back(glm::vec3( -size_,  size_, size_));
    vertexArray_.push_back(glm::vec3(-size_,  size_, -size_));

    // Back Face
    vertexArray_.push_back(glm::vec3( size_, -size_,  -size_));
    vertexArray_.push_back(glm::vec3( -size_, -size_, -size_));
    vertexArray_.push_back(glm::vec3( -size_,  size_, -size_));
    vertexArray_.push_back(glm::vec3(size_,  size_, -size_));

    // Bottom Face
    vertexArray_.push_back(glm::vec3( -size_, -size_,  -size_));
    vertexArray_.push_back(glm::vec3( size_, -size_, -size_));
    vertexArray_.push_back(glm::vec3( size_,  -size_, size_));
    vertexArray_.push_back(glm::vec3(-size_,  -size_, size_));
}

void Character::setUpNormals()
{
    // Normals
    for (size_t current_offset = 0; current_offset < vertexArray_.size(); current_offset += 4) {
        normalArray_.push_back(glm::cross(
                    vertexArray_[BOTTOMRIGHT + current_offset] - vertexArray_[BOTTOMLEFT + current_offset],
                    vertexArray_[TOPLEFT + current_offset] - vertexArray_[BOTTOMLEFT + current_offset]
                    ));
        normalArray_[BOTTOMLEFT + current_offset] =
                normalArray_[BOTTOMLEFT + current_offset] / glm::length(normalArray_[BOTTOMLEFT + current_offset]);

        normalArray_.push_back(glm::cross(
                    vertexArray_[TOPRIGHT + current_offset] - vertexArray_[BOTTOMRIGHT + current_offset],
                    vertexArray_[BOTTOMLEFT + current_offset] - vertexArray_[BOTTOMRIGHT + current_offset]));
        normalArray_[BOTTOMRIGHT + current_offset] =
                normalArray_[BOTTOMRIGHT + current_offset] / glm::length(normalArray_[BOTTOMRIGHT + current_offset]);

        normalArray_.push_back(glm::cross(
                    vertexArray_[TOPLEFT + current_offset] - vertexArray_[TOPRIGHT + current_offset],
                    vertexArray_[BOTTOMRIGHT + current_offset] - vertexArray_[TOPRIGHT + current_offset]
                    ));
        normalArray_[TOPRIGHT + current_offset] =
                normalArray_[TOPRIGHT + current_offset] / glm::length(normalArray_[TOPRIGHT + current_offset]);

        normalArray_.push_back(glm::cross(
                    vertexArray_[BOTTOMLEFT + current_offset] - vertexArray_[TOPLEFT + current_offset],
                    vertexArray_[TOPRIGHT + current_offset] - vertexArray_[TOPLEFT + current_offset]
                    ));
        normalArray_[TOPLEFT + current_offset] =
                normalArray_[TOPLEFT + current_offset] / glm::length(normalArray_[TOPLEFT + current_offset]);
    }

    // Shared normals
    auto normalFrontBottomLeft = normalArray_[BOTTOMLEFT + FRONT] + normalArray_[BOTTOMRIGHT + LEFT] + normalArray_[TOPLEFT + BOTTOM];
    normalFrontBottomLeft = normalFrontBottomLeft / glm::length(normalFrontBottomLeft);
    sharedNormalArray_.push_back(normalFrontBottomLeft);

    auto normalFrontBottomRight = normalArray_[BOTTOMRIGHT + FRONT] + normalArray_[BOTTOMLEFT + RIGHT] + normalArray_[TOPRIGHT + BOTTOM];
    normalFrontBottomRight = normalFrontBottomRight / glm::length(normalFrontBottomRight);
    sharedNormalArray_.push_back(normalFrontBottomRight);

    auto normalFrontTopRight = normalArray_[TOPRIGHT + FRONT] + normalArray_[BOTTOMRIGHT + TOP] + normalArray_[TOPLEFT + RIGHT];
    normalFrontTopRight = normalFrontTopRight / glm::length(normalFrontTopRight);
    sharedNormalArray_.push_back(normalFrontTopRight);

    auto normalFrontTopLeft = normalArray_[TOPLEFT + FRONT] + normalArray_[TOPRIGHT + LEFT] + normalArray_[BOTTOMLEFT + TOP];
    normalFrontTopLeft = normalFrontTopLeft / glm::length(normalFrontTopLeft);
    sharedNormalArray_.push_back(normalFrontTopLeft);

    auto normalRightBottomLeft = normalFrontBottomRight;
    sharedNormalArray_.push_back(normalRightBottomLeft);

    auto normalRightBottomRight = normalArray_[BOTTOMRIGHT + RIGHT] + normalArray_[BOTTOMRIGHT + BOTTOM] + normalArray_[BOTTOMLEFT + BACK];
    normalRightBottomRight = normalRightBottomRight / glm::length(normalRightBottomRight);
    sharedNormalArray_.push_back(normalRightBottomRight);

    auto normalRightTopRight = normalArray_[TOPRIGHT + RIGHT] + normalArray_[TOPRIGHT + TOP] + normalArray_[TOPLEFT + BACK];
    normalRightTopRight = normalRightTopRight / glm::length(normalRightTopRight);
    sharedNormalArray_.push_back(normalRightTopRight);

    auto normalRightTopLeft = normalFrontTopRight;
    sharedNormalArray_.push_back(normalRightTopLeft);

    auto normalTopBottomLeft = normalFrontTopLeft;
    sharedNormalArray_.push_back(normalTopBottomLeft);

    auto normalTopBottomRight = normalFrontTopRight;
    sharedNormalArray_.push_back(normalTopBottomRight);

    auto normalTopTopRight = normalRightTopRight;
    sharedNormalArray_.push_back(normalTopTopRight);

    auto normalTopTopLeft = normalArray_[TOPLEFT + TOP] + normalArray_[TOPLEFT + LEFT] + normalArray_[TOPRIGHT + BACK];
    normalTopTopLeft = normalTopTopLeft / glm::length(normalTopTopLeft);
    sharedNormalArray_.push_back(normalTopTopLeft);

    auto normalLeftBottomLeft = normalArray_[BOTTOMLEFT + LEFT] + normalArray_[BOTTOMRIGHT + BACK] + normalArray_[BOTTOMLEFT + BOTTOM];
    normalLeftBottomLeft = normalLeftBottomLeft / glm::length(normalLeftBottomLeft);
    sharedNormalArray_.push_back(normalLeftBottomLeft);

    auto normalLeftBottomRight = normalFrontBottomLeft;
    sharedNormalArray_.push_back(normalLeftBottomRight);

    auto normalLeftTopRight = normalFrontTopLeft;
    sharedNormalArray_.push_back(normalLeftTopRight);

    auto normalLeftTopLeft = normalTopTopLeft;
    sharedNormalArray_.push_back(normalLeftTopLeft);

    auto normalBackBottomLeft = normalRightBottomRight;
    sharedNormalArray_.push_back(normalBackBottomLeft);

    auto normalBackBottomRight = normalLeftBottomLeft;
    sharedNormalArray_.push_back(normalBackBottomRight);

    auto normalBackTopRight = normalLeftTopLeft;
    sharedNormalArray_.push_back(normalBackTopRight);

    auto normalBackTopLeft = normalRightTopRight;
    sharedNormalArray_.push_back(normalBackTopLeft);

    auto normalBottomBottomLeft = normalBackBottomRight;
    sharedNormalArray_.push_back(normalBottomBottomLeft);

    auto normalBottomBottomRight = normalBackBottomLeft;
    sharedNormalArray_.push_back(normalBottomBottomRight);

    auto normalBottomTopRight = normalFrontBottomRight;
    sharedNormalArray_.push_back(normalBottomTopRight);

    auto normalBottomTopLeft = normalFrontBottomLeft;
    sharedNormalArray_.push_back(normalBottomTopLeft);
}

void Character::createNormalLineList()
{
    glNewList(list_id_, GL_COMPILE);
        glBegin(GL_LINES);

        for (size_t i = 0; i < vertexArray_.size() && i < sharedNormalArray_.size(); i++) {
            glVertex3f(vertexArray_[i].x,
                       vertexArray_[i].y,
                       vertexArray_[i].z);
            glVertex3f(vertexArray_[i].x + sharedNormalArray_[i].x * 10,
                       vertexArray_[i].y + sharedNormalArray_[i].y * 10,
                       vertexArray_[i].z + sharedNormalArray_[i].z * 10);
        }

        glEnd();
    glEndList();
}

void Character::setUpLighting()
{
    GLfloat lightPosition[] = {100.0f, 100.0f, 0.0f, 1.0f};
    GLfloat lightAmbient[] = {0.0f, 0.0f, 1.0f, 1.0f};
    GLfloat lightDiffuse[] = {1.0f, 1.0f, 1.0f};
    GLfloat materialAmbient[] = {0.5f, 0.5f, 0.5f, 1.0f};
    GLfloat materialDiffuse[] = {1.0f, 0.0f, 0.0f, 1.0f};

//    glLightfv(GL_LIGHT0, GL_POSITION, lightPosition);
//    glLightfv(GL_LIGHT0, GL_AMBIENT, lightAmbient);
//    glMaterialfv(GL_FRONT, GL_AMBIENT, materialAmbient);
    glLightfv(GL_LIGHT1, GL_POSITION, lightPosition);
    glLightfv(GL_LIGHT1, GL_DIFFUSE, lightDiffuse);
    //glMaterialfv(GL_FRONT, GL_DIFFUSE, materialDiffuse);
}

void Character::setUpTextures()
{

}

void Character::setUpHealthbar()
{
    life_ = 100.0f;
    armor_ = 50.0f;

    setUpHBVertices();
    setUpHBTextures();
}

void Character::setUpHBVertices()
{
    healthbarVertexArray_.push_back(glm::vec3(2 * -size_, 2 * size_,  0));
    healthbarVertexArray_.push_back(glm::vec3(2 * size_, 2 * size_,  0));
    healthbarVertexArray_.push_back(glm::vec3(2 * size_, 3 * size_,  0));
    healthbarVertexArray_.push_back(glm::vec3(2 * -size_,  3 * size_,  0));
}

void Character::setUpHBTextures()
{
    healthbarTextureArray_.push_back(glm::vec2(0.0f, 1.0f));
    healthbarTextureArray_.push_back(glm::vec2(1.0f, 1.0f));
    healthbarTextureArray_.push_back(glm::vec2(1.0f, 0.0f));
    healthbarTextureArray_.push_back(glm::vec2(0.0f, 0.0f));

    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

    int width, height, nrChannels;
    unsigned char *data = stbi_load("C:/dev/DTE-3609/start_code/resources/HP.jpg", &width, &height, &nrChannels, 0);
    if (data)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
    }
    else
    {
        std::cout << "FAILED TO LOAD TEXTURE: " << stbi_failure_reason() << std::endl;
    }
    glBindTexture(GL_TEXTURE_2D, 0);
    stbi_image_free(data);
}

void Character::privateUpdate()
{
//    auto translation = glm::translate(glm::mat4(1.0f), glm::vec3(0.2f * speed_, 0.0f, 0.0f));
//    auto rotation = glm::rotate(matrix_, 0.01f, glm::vec3(0.0f,1.0f,0.0f));
//    matrix_ = translation * rotation;
}

void Character::increaseSpeed()
{
    speed_ = speed_ + 0.2f;
}

void Character::decreaseSpeed()
{
    speed_ = speed_ - 0.2f;
}

