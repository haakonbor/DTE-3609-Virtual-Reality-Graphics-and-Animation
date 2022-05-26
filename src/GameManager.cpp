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
  auto landscapeTexturePath = "C:/dev/uni/DTE-3609_VR_graphics_animation/start_code/resources/textures/road.jpg";
  auto landscapeSize = 200.0f;
  auto landscapeScaling = 3.0f;
  auto landscapeRealSize = landscapeSize * landscapeScaling;

  ls1_.reset(new Plane(glm::vec3(0.0f, -50.0f, 0.0f), landscapeTexturePath, glm::vec3(0.0f, 0.0f, 1.0f),
                       30.0f, glm::vec3(landscapeScaling, landscapeScaling, landscapeScaling)));
  this->addSubObject(ls1_);
  ls2_.reset(new Plane(glm::vec3(landscapeRealSize * cos(glm::radians(30.0f)), -50.0f + landscapeRealSize * sin(glm::radians(30.0f)), 0.0f), landscapeTexturePath, glm::vec3(0.0f, 0.0f, 1.0f),
                       30.0f, glm::vec3(landscapeScaling, landscapeScaling, landscapeScaling)));
  this->addSubObject(ls2_);
  ls3_.reset(new Plane(glm::vec3(2 * landscapeRealSize * cos(glm::radians(30.0f)), -50.0f + 2 * landscapeRealSize * sin(glm::radians(30.0f)), 0.0f), landscapeTexturePath, glm::vec3(0.0f, 0.0f, 1.0f),
                       30.0f,glm::vec3(landscapeScaling, landscapeScaling, landscapeScaling)));
  this->addSubObject(ls3_);
  ls4_.reset(new Plane(glm::vec3(3 * landscapeRealSize * cos(glm::radians(30.0f)), -50.0f + 3 * landscapeRealSize * sin(glm::radians(30.0f)), 0.0f),landscapeTexturePath, glm::vec3(0.0f, 0.0f, 1.0f),
                       30.0f, glm::vec3(landscapeScaling, landscapeScaling, landscapeScaling)));
  this->addSubObject(ls4_);
  ls5_.reset(new Plane(glm::vec3(4 * landscapeRealSize * cos(glm::radians(30.0f)), -50.0f + 4 * landscapeRealSize * sin(glm::radians(30.0f)), 0.0f),landscapeTexturePath, glm::vec3(0.0f, 0.0f, 1.0f),
                       30.0f, glm::vec3(landscapeScaling, landscapeScaling, landscapeScaling)));
  this->addSubObject(ls5_);

  // Skybox
  float skyboxSize = 10000.0f;
  std::string skyboxTexturePathPrefix = "C:/dev/uni/DTE-3609_VR_graphics_animation/start_code/resources/textures/skybox_";

  sbw_.reset(new Plane(glm::vec3(-skyboxSize / 2, 0, 0.0f), skyboxTexturePathPrefix + "west.bmp", glm::vec3(0.0f, 1.0f, 0.0f),
                       90.0f, glm::vec3(skyboxSize / 200, skyboxSize / 200, skyboxSize / 200), true, true));
  this->addSubObject(sbw_);
  sbn_.reset(new Plane(glm::vec3(0.0f, 0.0f, -skyboxSize / 2), skyboxTexturePathPrefix + "north.bmp", glm::vec3(0.0f, 0.0f, 0.0f),
                       0.0f, glm::vec3(skyboxSize / 200, skyboxSize / 200, skyboxSize / 200), true, true));
  this->addSubObject(sbn_);
  sbe_.reset(new Plane(glm::vec3(skyboxSize / 2, 0.0f, 0.0f), skyboxTexturePathPrefix + "east.bmp", glm::vec3(0.0f, 1.0f, 0.0f),
                       270.0f, glm::vec3(skyboxSize / 200, skyboxSize / 200, skyboxSize / 200), true, true));
  this->addSubObject(sbe_);
  sbs_.reset(new Plane(glm::vec3(0.0f, 0.0f, skyboxSize / 2),skyboxTexturePathPrefix + "south.bmp", glm::vec3(0.0f, 1.0f, 0.0f),
                       180.0f, glm::vec3(skyboxSize / 200, skyboxSize / 200, skyboxSize / 200), true, true));
  this->addSubObject(sbs_);
  sbu_.reset(new Plane(glm::vec3(0.0f, skyboxSize / 2, 0.0f), skyboxTexturePathPrefix + "up.bmp", glm::vec3(1.0f, 0.0f, 0.0f),
                       90.0f, glm::vec3(skyboxSize / 200, skyboxSize / 200, skyboxSize / 200), true, true));
  this->addSubObject(sbu_);
  sbd_.reset(new Plane(glm::vec3(0.0f, -skyboxSize / 2, 0.0f), skyboxTexturePathPrefix + "down.bmp", glm::vec3(0.0f, 0.0f, 0.0f),
                       0.0f, glm::vec3(skyboxSize / 200, skyboxSize / 200, skyboxSize / 200), true, false));
  this->addSubObject(sbd_);

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


