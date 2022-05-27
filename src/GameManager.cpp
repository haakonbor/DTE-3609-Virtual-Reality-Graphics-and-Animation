#include "../include/GameManager.hpp"

#include <math.h>

GameManager::GameManager()
{
}

GameManager::~GameManager()
{
}

void GameManager::privateInit()
{
  // Set default OpenGL states
  glEnable(GL_CULL_FACE);

//  glEnable(GL_FOG);
//  glFogi(GL_FOG_MODE, GL_LINEAR);
//  glFogf(GL_FOG_START, 1.0f);
//  glFogf(GL_FOG_END, 500.0f);
//  GLfloat fog_color[4] = {0.5, 0.5, 0.5, 1.0};
//  glFogfv(GL_FOG_COLOR, fog_color);

  // Adding the camera to the scene
  cam_.reset(new Camera());

  // Landscape
  const auto landscapeSize = 200.0f;
  const auto landscapeScaling = 3.0f;
  const auto landscapeRealSize = landscapeSize * landscapeScaling;
  const auto landscapeRotationAxis = glm::vec3(0.0f, 0.0f, 1.0f);
  const auto landscapeRotationDegree = 30.0f;
  const auto landscapeX = landscapeRealSize * cos(glm::radians(landscapeRotationDegree));
  const auto landscapeY = landscapeRealSize * sin(glm::radians(landscapeRotationDegree));

  ls1_.reset(new Plane(glm::vec3(0.0f, -50.0f, 0.0f), landscapeRotationAxis,
                       landscapeRotationDegree, glm::vec3(landscapeScaling, landscapeScaling, landscapeScaling)));
  this->addSubObject(ls1_);
  ls2_.reset(new Plane(glm::vec3(landscapeX, -50.0f + landscapeY, 0.0f), landscapeRotationAxis,
                       landscapeRotationDegree, glm::vec3(landscapeScaling, landscapeScaling, landscapeScaling)));
  this->addSubObject(ls2_);
  ls3_.reset(new Plane(glm::vec3(2 * landscapeX, -50.0f + 2 * landscapeY, 0.0f), landscapeRotationAxis,
                       landscapeRotationDegree, glm::vec3(landscapeScaling, landscapeScaling, landscapeScaling)));
  this->addSubObject(ls3_);
  ls4_.reset(new Plane(glm::vec3(3 * landscapeX, -50.0f + 3 * landscapeY, 0.0f), landscapeRotationAxis,
                       landscapeRotationDegree, glm::vec3(landscapeScaling, landscapeScaling, landscapeScaling)));
  this->addSubObject(ls4_);
  ls5_.reset(new Plane(glm::vec3(4 * landscapeX, -50.0f + 4 * landscapeY, 0.0f), landscapeRotationAxis,
                       landscapeRotationDegree, glm::vec3(landscapeScaling, landscapeScaling, landscapeScaling)));
  this->addSubObject(ls5_);

  // Skybox
  sb_.reset(new Skybox());
  this->addSubObject(sb_);

  // Character
  character_.reset(new Character());
  this->addSubObject(character_);

  // Snow
  snow_.reset(new Snow());
  this->addSubObject(snow_);

  // Text
  text_.reset(new Text());
  this->addSubObject(text_);

  // Minimap
  minimap_.reset(new Minimap());
  this->addSubObject(minimap_);

}

void GameManager::privateRender()
{
  // Nothing to render
}

void GameManager::privateUpdate()
{
  // Instead of adding alle objects in the scene as subobject to the camera they are added as subobjects
  // to the game manager. Therefore, we set the game manager matrix equal to the camera matrix. 
  this->matrix_ = cam_->getMatrix();
}

std::shared_ptr<Camera> GameManager::getCam()
{
  return cam_;
}

std::shared_ptr<Character> GameManager::getCharacter()
{
  return character_;
}


