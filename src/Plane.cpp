#include "../include/Plane.hpp"
#include "../../glm-master/glm/glm.hpp"
#include "../../glm-master/glm/gtc/type_ptr.hpp"

#include "../include/Projection.h"

Plane::Plane(glm::vec3 trans, std::string texturePath, glm::vec3 rotationAxis, float rotationAngle, glm::vec3 scale, bool isFixed, bool isTilted)
    : texture(Texture(texturePath)), fixed(isFixed), scaling(scale[0])
{
    auto translation = glm::translate(glm::mat4(1.0f), trans);

    auto rotation = glm::mat4(1.0);

    if (rotationAngle != 0.0f) {
        rotation *= glm::rotate(glm::mat4(1.0f), glm::radians(rotationAngle), rotationAxis);
    }
    if (isTilted) {
//        rotation *= glm::rotate(glm::mat4(1.0f), glm::radians(-30.0f), glm::vec3(0.0f, 0.0f, 1.0f));
        rotation *= glm::rotate(glm::mat4(1.0f), glm::radians(90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
    }

    auto scaling = glm::scale(glm::mat4(1.0f), scale);

    matrix_ = translation * rotation * scaling;
}

Plane::~Plane()
{
}

void Plane::privateInit()
{
  /* VERTEX BUFFER */
  // Is set up in initialization of object attribute

  /* LAYOUT */
  // 3 floats for world position
  layout.Push<float>(3);
  // 2 floats for texture position
  layout.Push<float>(2);

  /* VERTEX ARRAY */
  vao.AddBuffer(vbo, layout);

  /* INDEX BUFFER */
  // Is set up in initialization of object attribute

  /* SHADER */
  shader.Bind();
//  shader.SetUniform4f("u_Color", 0.0f, 0.0f, 1.0f, 1.0f);

  /* TEXTURE */
  texture.Bind(textureSlot);
  shader.SetUniform1i("u_Texture", textureSlot);

  /* UNBINDING */
  texture.Unbind();
  vao.Unbind();
  vbo.Unbind();
  ibo.Unbind();
  shader.Unbind();
}

void Plane::privateRender()
{
    shader.Bind();
    vao.Bind();
    ibo.Bind();
    texture.Bind(textureSlot);

    glm::mat4 projectionMatrix = glm::perspective(glm::radians(proj::PoV), proj::aspectRatio, proj::nearClip, proj::farClip);
    glm::mat4 mvp = projectionMatrix * viewMatrix_ * matrix_;

    shader.SetUniformMat4f("u_MVP", mvp);

    GLCall(glDrawElements(GL_QUADS, ibo.GetCount(), GL_UNSIGNED_INT, nullptr));

    texture.Unbind();
    ibo.Unbind();
    vao.Unbind();
    shader.Unbind();

//    // Draw filled polygons
//    glColor3f(0.0f, 1.0f, 0.0f);
//    glEnableClientState(GL_VERTEX_ARRAY);
//    glVertexPointer(3, GL_FLOAT, 0, vertexArray_.data());
//    glDrawArrays(GL_QUADS, 0, 4);
//    glDisableClientState(GL_VERTEX_ARRAY);

//    glColor3f(0.0f, 0.0f, 1.0f);
//    glEnableClientState(GL_VERTEX_ARRAY);
//    glVertexPointer(3, GL_FLOAT, 0, vertexArray_.data());
//    glDrawArrays(GL_QUADS, 4, 4);
//    glDisableClientState(GL_VERTEX_ARRAY);

//    glColor3f(1.0f, 1.0f, 0.0f);
//    glEnableClientState(GL_VERTEX_ARRAY);
//    glVertexPointer(3, GL_FLOAT, 0, vertexArray_.data());
//    glDrawArrays(GL_QUADS, 8, 4);
//    glDisableClientState(GL_VERTEX_ARRAY);

//    glColor3f(0.2f, 0.2f, 0.2f);
//    glEnableClientState(GL_VERTEX_ARRAY);
//    glVertexPointer(3, GL_FLOAT, 0, vertexArray_.data());
//    glDrawArrays(GL_QUADS, 12, 4);
//    glDisableClientState(GL_VERTEX_ARRAY);

//    // Drawing wireframe of polygons
//    glEnable(GL_POLYGON_OFFSET_LINE);
//    glPolygonOffset(-1.0, -1.0);
//    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

//    glColor3f(1.0f, 0.0f, 0.0f);
//    glEnableClientState(GL_VERTEX_ARRAY);
//    glVertexPointer(3, GL_FLOAT, 0, vertexArray_.data());
//    glDrawArrays(GL_QUADS, 0, 4);
//    glDisableClientState(GL_VERTEX_ARRAY);

//    glColor3f(1.0f, 0.0f, 0.0f);
//    glEnableClientState(GL_VERTEX_ARRAY);
//    glVertexPointer(3, GL_FLOAT, 0, vertexArray_.data());
//    glDrawArrays(GL_QUADS, 4, 4);
//    glDisableClientState(GL_VERTEX_ARRAY);

//    glColor3f(1.0f, 0.0f, 0.0f);
//    glEnableClientState(GL_VERTEX_ARRAY);
//    glVertexPointer(3, GL_FLOAT, 0, vertexArray_.data());
//    glDrawArrays(GL_QUADS, 8, 4);
//    glDisableClientState(GL_VERTEX_ARRAY);

//    glColor3f(1.0f, 0.0f, 0.0f);
//    glEnableClientState(GL_VERTEX_ARRAY);
//    glVertexPointer(3, GL_FLOAT, 0, vertexArray_.data());
//    glDrawArrays(GL_QUADS, 12, 4);
//    glDisableClientState(GL_VERTEX_ARRAY);

//    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
//    glDisable(GL_POLYGON_OFFSET_LINE);

}

void Plane::privateUpdate()
{
    if (fixed)
        return;

    if (matrix_[3].x < - 1.5 * 200 * scaling) {
        matrix_ = glm::translate(matrix_, glm::vec3(1.5 * 200 * scaling - 2, 0.0f, 0.0f));
    }
    else {
        matrix_ = glm::translate(matrix_, glm::vec3(-1.0f, 0.0f, 0.0f));
    }
}

