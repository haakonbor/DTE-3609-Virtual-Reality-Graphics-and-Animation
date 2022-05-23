#include "../include/GameManager.hpp"

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

  ls1_.reset(new Landscape(glm::vec3(0.0f, -50.0f, 0.0f)));
  this->addSubObject(ls1_);
  ls2_.reset(new Landscape(glm::vec3(200.0f, -50.0f, 0.0f)));
  this->addSubObject(ls2_);
  ls3_.reset(new Landscape(glm::vec3(400.0f, -50.0f, 0.0f)));
  this->addSubObject(ls3_);
  ls4_.reset(new Landscape(glm::vec3(600.0f, -50.0f, 0.0f)));
  this->addSubObject(ls4_);

  character_.reset(new Character());
  this->addSubObject(character_);

  snow_.reset(new Snow());
  this->addSubObject(snow_);

  text_.reset(new Text());
  this->addSubObject(text_);

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


