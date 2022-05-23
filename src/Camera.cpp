#include "../include/Camera.hpp"
#include "../../glm-master/glm/glm.hpp"
#include "../../glm-master/glm/gtc/matrix_transform.hpp"

#include <iostream>

#define PIOVER180 0.0174532925199

Camera::Camera()
{
  auto translation = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, -300.0f));
  auto rotation = glm::rotate(glm::mat4(1.0f), glm::radians(30.0f), glm::vec3(0.0f,0.0f,1.0f));
  matrix_ = translation * rotation;
}

Camera::~Camera()
{
}

void Camera::privateInit()
{

}


void Camera::privateRender()
{
  // not drawing any camera geometry
}

void Camera::privateUpdate()
{

}

void Camera::moveRight()
{
  matrix_ = glm::translate(matrix_, glm::vec3(-5.0f, 0.0f, 0.0f));
}
void Camera::moveLeft()
{
  matrix_ = glm::translate(matrix_, glm::vec3(5.0f, 0.0f, 0.0f));
}
void Camera::moveUp()
{
  matrix_ = glm::translate(matrix_, glm::vec3(0.0f, -5.0f, 0.0f));
}
void Camera::moveDown()
{
  matrix_ = glm::translate(matrix_, glm::vec3(0.0f, 5.0f, 0.0f));
}
void Camera::moveForward()
{
  matrix_ = glm::translate(matrix_, glm::vec3(0.0f, 0.0f, 5.0f));
}
void Camera::moveBackward()
{
  matrix_ = glm::translate(matrix_, glm::vec3(0.0f, 0.0f, -5.0f));
}

void Camera::rotateLeft()
{
    matrix_ = glm::rotate(matrix_, .01f, glm::vec3(0.0f, 1.0f, 0.0f));
}

void Camera::rotateRight()
{
    matrix_ = glm::rotate(matrix_, -.01f, glm::vec3(0.0f, 1.0f, 0.0f));
}

