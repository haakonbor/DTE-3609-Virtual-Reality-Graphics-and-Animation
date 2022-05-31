#include "../include/Obstacle.h"
#include "../../glm-master/glm/glm.hpp"
#include "../../glm-master/glm/gtc/type_ptr.hpp"



Obstacle::Obstacle(glm::vec3 trans, glm::vec3 rotationAxis, float rotationAngle)
    :position_(trans)
{
    translation_ = glm::translate(glm::mat4(1.0f), trans);

    rotation_ = glm::rotate(glm::mat4(1.0f), glm::radians(rotationAngle), rotationAxis);

    matrix_ = translation_ * rotation_ * scaling_;
}

Obstacle::~Obstacle()
{
}

void Obstacle::privateInit()
{
  /* VERTEX BUFFER */
  // Is set up in initialization of object attribute

  /* LAYOUT */
  // 3 floats for world position
  layout.Push<float>(3);
  // 2 floats for texture position
//  layout.Push<float>(2);

  /* VERTEX ARRAY */
  vao.AddBuffer(vbo, layout);

  /* INDEX BUFFER */
  // Is set up in initialization of object attribute

  /* SHADER */
  shader.Bind();
//  shader.SetUniform4f("u_Color", 0.0f, 0.0f, 1.0f, 1.0f);

  /* TEXTURE */
  texture.BindCubemap(textureSlot);
  shader.SetUniform1i("u_Texture", textureSlot);

  /* UNBINDING */
  texture.UnbindCubemap();
  vao.Unbind();
  vbo.Unbind();
  ibo.Unbind();
  shader.Unbind();
}

void Obstacle::privateRender()
{
    shader.Bind();
    vao.Bind();
    ibo.Bind();
    texture.BindCubemap(textureSlot);

    shader.SetUniformMat4f("u_ViewMatrix", viewMatrix_);
    shader.SetUniformMat4f("u_ProjectionMatrix", projMatrix_);
    shader.SetUniformMat4f("u_ModelMatrix", matrix_);

    GLCall(glDrawElements(GL_QUADS, ibo.GetCount(), GL_UNSIGNED_INT, nullptr));

    texture.UnbindCubemap();
    ibo.Unbind();
    vao.Unbind();
    shader.Unbind();
}

void Obstacle::privateUpdate()
{
    glm::vec3 trans;
    float resetDistance = 4000.0f;

    if (position_.x < - 1.5 * 200 * 3) {

        trans = glm::vec3(resetDistance, tan(glm::radians(30.0f)) * resetDistance, -200.0f + float(rand() % 400));
        translation_ = glm::translate(glm::mat4(1.0f), trans);
        position_ = trans;
    }
    else {
        trans = glm::vec3(speed_, tan(glm::radians(30.0f)) * speed_, 0.0f);
        translation_ = glm::translate(translation_, trans);
        position_ += trans;
    }

    rotation_ = glm::rotate(rotation_, 0.05f - speed_ / 1000, glm::vec3(0.0f, 0.0f, 1.0f));
    matrix_ = translation_ * rotation_ * scaling_;

    speed_ -= 0.001f;
}

