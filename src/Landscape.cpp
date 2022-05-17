#include "../include/Landscape.hpp"
#include "../../glm-master/glm/glm.hpp"
#include "../../glm-master/glm/gtc/type_ptr.hpp"

Landscape::Landscape()
{
}

Landscape::~Landscape()
{
}

void Landscape::privateInit()
{
  /* VERTEX BUFFER */
  // Is set up in initialization of object attribute

  /* LAYOUT */
  // 3 floats for world position
  layout.Push<float>(3);
//  // 2 floats for texture position
//  layout.Push<float>(2);

  /* VERTEX ARRAY */
  vao.AddBuffer(vbo, layout);

  /* INDEX BUFFER */
  // Is set up in initialization of object attribute

  /* SHADER */
  shader.Bind();
  shader.SetUniform4f("u_Color", 0.0f, 0.0f, 1.0f, 1.0f);

  /* TEXTURE */
//  unsigned int textureSlot = 0;
//  texture.Bind(textureSlot);
//  shader.SetUniform1i("u_Texture", textureSlot);

  /* UNBINDING */
  vao.Unbind();
  vbo.Unbind();
  ibo.Unbind();
  shader.Unbind();

}

void Landscape::privateRender()
{
    shader.Bind();
    vao.Bind();
    ibo.Bind();
//    shader.SetUniformMat4f("u_MVP", matrix_);

    glm::mat4 trans = glm::mat4(1.0f);
//    trans = glm::translate(trans, glm::vec3(0.5f, -0.5f, 0.0f));
//    trans = glm::rotate(trans, 45.0f, glm::vec3(0.0f, 0.0f, 1.0f));
    matrix_ = matrix_ * trans;
    shader.SetUniformMat4f("u_MVP", matrix_);


    GLCall(glDrawElements(GL_QUADS, ibo.GetCount(), GL_UNSIGNED_INT, nullptr));

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

void Landscape::privateUpdate()
{

}

