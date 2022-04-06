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
}

void Landscape::privateRender()
{
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
}

void Landscape::privateUpdate()
{
    //glMatrixMode(GL_MODELVIEW);
    //glPushMatrix();
    //glLoadIdentity();
    //glTranslatef(10.0f, 0.0f, 0.0f);
    //glRotatef(1.0f, 0.0f, 1.0f, 0.0f);
    //glPopMatrix();
}

