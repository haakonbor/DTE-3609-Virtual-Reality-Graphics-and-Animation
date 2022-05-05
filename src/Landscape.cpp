#include "../include/Landscape.hpp"

Landscape::Landscape()
{
}

Landscape::~Landscape()
{
}

void Landscape::privateInit()
{
  // Left plane
  vertexArray_.push_back(glm::vec3(-100.0f, -50.0f, 50.0f));
  vertexArray_.push_back(glm::vec3(0.0f, -50.0f, 50.0f));
  vertexArray_.push_back(glm::vec3(0.0f, -50.0f, -50.0f));
  vertexArray_.push_back(glm::vec3(-100.0f, -50.0f, -50.0f));

  // Middle plane
  vertexArray_.push_back(glm::vec3(0.0f, -50.0f, 50.0f));
  vertexArray_.push_back(glm::vec3(100.0f, -50.0f, 50.0f));
  vertexArray_.push_back(glm::vec3(100.0f, -50.0f, -50.0f));
  vertexArray_.push_back(glm::vec3(0.0f, -50.0f, -50.0f));

  // Right plane
  vertexArray_.push_back(glm::vec3(100.0f, -50.0f, 50.0f));
  vertexArray_.push_back(glm::vec3(200.0f, -50.0f, 50.0f));
  vertexArray_.push_back(glm::vec3(200.0f, -50.0f, -50.0f));
  vertexArray_.push_back(glm::vec3(100.0f, -50.0f, -50.0f));

  // Background
  vertexArray_.push_back(glm::vec3(-1000.0f, -1000.0f, -500.0f));
  vertexArray_.push_back(glm::vec3(1000.0f, -1000.0f, -500.0f));
  vertexArray_.push_back(glm::vec3(1000.0f, 1000.0f, -500.0f));
  vertexArray_.push_back(glm::vec3(-1000.0f, 1000.0f, -500.0f));

  vbo = VertexBuffer(vertexArray_.data(), vertexArray_.size() * 3 * sizeof(float));
  layout.Push<float>(3);

  vao.AddBuffer(vbo, layout);

  // 4 points in a quad, 3 quads in total
  ibo = IndexBuffer(indices_, 4 * 3);
}

void Landscape::privateRender()
{
    // Draw filled polygons
    glColor3f(0.0f, 1.0f, 0.0f);
    glEnableClientState(GL_VERTEX_ARRAY);
    glVertexPointer(3, GL_FLOAT, 0, vertexArray_.data());
    glDrawArrays(GL_QUADS, 0, 4);
    glDisableClientState(GL_VERTEX_ARRAY);

    glColor3f(0.0f, 0.0f, 1.0f);
    glEnableClientState(GL_VERTEX_ARRAY);
    glVertexPointer(3, GL_FLOAT, 0, vertexArray_.data());
    glDrawArrays(GL_QUADS, 4, 4);
    glDisableClientState(GL_VERTEX_ARRAY);

    glColor3f(1.0f, 1.0f, 0.0f);
    glEnableClientState(GL_VERTEX_ARRAY);
    glVertexPointer(3, GL_FLOAT, 0, vertexArray_.data());
    glDrawArrays(GL_QUADS, 8, 4);
    glDisableClientState(GL_VERTEX_ARRAY);

    glColor3f(0.2f, 0.2f, 0.2f);
    glEnableClientState(GL_VERTEX_ARRAY);
    glVertexPointer(3, GL_FLOAT, 0, vertexArray_.data());
    glDrawArrays(GL_QUADS, 12, 4);
    glDisableClientState(GL_VERTEX_ARRAY);

    // Drawing wireframe of polygons
    glEnable(GL_POLYGON_OFFSET_LINE);
    glPolygonOffset(-1.0, -1.0);
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    glColor3f(1.0f, 0.0f, 0.0f);
    glEnableClientState(GL_VERTEX_ARRAY);
    glVertexPointer(3, GL_FLOAT, 0, vertexArray_.data());
    glDrawArrays(GL_QUADS, 0, 4);
    glDisableClientState(GL_VERTEX_ARRAY);

    glColor3f(1.0f, 0.0f, 0.0f);
    glEnableClientState(GL_VERTEX_ARRAY);
    glVertexPointer(3, GL_FLOAT, 0, vertexArray_.data());
    glDrawArrays(GL_QUADS, 4, 4);
    glDisableClientState(GL_VERTEX_ARRAY);

    glColor3f(1.0f, 0.0f, 0.0f);
    glEnableClientState(GL_VERTEX_ARRAY);
    glVertexPointer(3, GL_FLOAT, 0, vertexArray_.data());
    glDrawArrays(GL_QUADS, 8, 4);
    glDisableClientState(GL_VERTEX_ARRAY);

    glColor3f(1.0f, 0.0f, 0.0f);
    glEnableClientState(GL_VERTEX_ARRAY);
    glVertexPointer(3, GL_FLOAT, 0, vertexArray_.data());
    glDrawArrays(GL_QUADS, 12, 4);
    glDisableClientState(GL_VERTEX_ARRAY);

    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    glDisable(GL_POLYGON_OFFSET_LINE);

}

void Landscape::privateUpdate()
{

}

