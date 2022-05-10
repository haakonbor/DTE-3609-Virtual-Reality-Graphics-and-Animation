#include "../include/Landscape.hpp"

Landscape::Landscape()
{
}

Landscape::~Landscape()
{
}

void Landscape::privateInit()
{
  // 3 floats for position
  layout.Push<float>(3);
  // 2 floats for texture position
  layout.Push<float>(2);

  vao.AddBuffer(vbo, layout);

  shader.Bind();
  shader.SetUniform4f("u_Color", 0.1f, 0.5f, 0.5f, 1.0f);

  unsigned int textureSlot = 0;
  texture.Bind(textureSlot);
  shader.SetUniform1i("u_Texture", textureSlot);

  vao.Unbind();
  vbo.Unbind();
  ibo.Unbind();
}

void Landscape::privateRender()
{
    vao.Bind();
    ibo.Bind();

    GLCall(glDrawElements(GL_QUADS, ibo.GetCount(), GL_UNSIGNED_INT, nullptr));

    vao.Unbind();
    ibo.Unbind();

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

