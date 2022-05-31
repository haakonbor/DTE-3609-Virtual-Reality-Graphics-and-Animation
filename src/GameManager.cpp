#include "../include/GameManager.hpp"

#include <math.h>
#include <iostream>
#include <fstream>

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
  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

//  glEnable(GL_FOG);
//  glFogi(GL_FOG_MODE, GL_LINEAR);
//  glFogf(GL_FOG_START, 1.0f);
//  glFogf(GL_FOG_END, 500.0f);
//  GLfloat fog_color[4] = {0.5, 0.5, 0.5, 1.0};
//  glFogfv(GL_FOG_COLOR, fog_color);

  // Adding the camera to the scene
  cam_.reset(new Camera());

  // Landscape
  const auto landscapeSegments = 12;
  const auto landscapeSize = 200.0f;
  const auto landscapeScaling = 3.0f;
  const auto landscapeRealSize = landscapeSize * landscapeScaling;
  const auto landscapeRotationAxis = glm::vec3(0.0f, 0.0f, 1.0f);
  const auto landscapeRotationDegree = 30.0f;
  const auto landscapeX = landscapeRealSize * cos(glm::radians(landscapeRotationDegree));
  const auto landscapeY = landscapeRealSize * sin(glm::radians(landscapeRotationDegree));

  for (unsigned int i = 0; i < landscapeSegments; i++) {
      std::shared_ptr<Plane> current_segment;
        current_segment.reset(new Plane(glm::vec3(0.0f + landscapeX * i, -50.0f + landscapeY * i, 0.0f), landscapeRotationAxis,
                             landscapeRotationDegree, glm::vec3(landscapeScaling, landscapeScaling, landscapeScaling)));
        this->addSubObject(current_segment);
        landscape_.push_back(current_segment);
  }

  // Skybox
  sb_.reset(new Skybox());
  this->addSubObject(sb_);

  // Character
  character_.reset(new Character(glm::vec3(0.0f, 10.0f, 0.0f)));
  this->addSubObject(character_);

  // Obstacles
  const auto obstacleNumber = 6;
  const auto obstacleStartPosX = 1000.0f;
  const auto obstacleSpacing = 200.0f;
  srand(time(0));

  for (unsigned int i = 0; i < obstacleNumber; i++) {
      std::shared_ptr<Obstacle> obstacle;
        obstacle.reset(new Obstacle(glm::vec3(obstacleStartPosX + obstacleSpacing * i + landscapeX * i, tan(glm::radians(landscapeRotationDegree)) * (obstacleStartPosX + obstacleSpacing * i) + 10.0f + landscapeY * i, - 150.0f + (i % 3) * 150.0f),
                                    landscapeRotationAxis, landscapeRotationDegree));
        this->addSubObject(obstacle);
        obstacles_.push_back(obstacle);
  }


  // Snow
  snow_.reset(new Snow());
  this->addSubObject(snow_);

//  // Minimap
//  minimap_.reset(new Minimap());
//  this->addSubObject(minimap_);

  // Text
  scoreText_.reset(new Text("Score: ", -0.95f, - 0.9f, 0.0f));
  this->addSubObject(scoreText_);

  std::ifstream infile("C:/dev/uni/DTE-3609_VR_graphics_animation/start_code/resources/data/highscore.dat");
  if (infile){
      infile >> highscore_;
  }
  else {
      std::cout << "COULD NOT OPEN HIGHSCORE FILE!" << std::endl;
  }

  infile.close();

  highscoreText_.reset(new Text("Highscore: ", -0.95f, - 0.8f, 0.0f, true, highscore_));
  this->addSubObject(highscoreText_);
}

void GameManager::privateRender()
{
  // Nothing to render
}

void GameManager::privateUpdate()
{
  checkCollisions();
  // Instead of adding alle objects in the scene as subobject to the camera they are added as subobjects
  // to the game manager. Therefore, we set the game manager matrix equal to the camera matrix. 
  this->matrix_ = cam_->getMatrix();
}

void GameManager::checkCollisions()
{
    for (auto obs : obstacles_) {
        const auto obsPos = obs->getPosition();
        const auto obsSize = obs->getSize();
        const auto charPos = character_->getPosition();
        const auto charSize = character_->getSize();

        const bool collisionX = charPos.x - charSize <= obsPos.x + obsSize && charPos.x + charSize >= obsPos.x - obsSize;
        const bool collisionY = charPos.y - charSize <= obsPos.y + obsSize && charPos.y + charSize >= obsPos.y - obsSize;
        const bool collisionZ = charPos.z - charSize <= obsPos.z + obsSize && charPos.z + charSize >= obsPos.z - obsSize;

        if (collisionX && collisionY && collisionZ) {
            if (character_->getState() != characterStates::colliding) {
                handleCollision(obs);
            }
            return;
        }
    }

    if (character_->getState() == characterStates::colliding) {
        resetCharacterAfterCollision();
    }
}

void GameManager::handleCollision(std::shared_ptr<Obstacle> obs)
{
     character_->setColor(1.0f, 1.0f, 1.0f);
     character_->setState(characterStates::colliding);
     character_->reduceLife();
}

void GameManager::resetCharacterAfterCollision()
{
    auto life = character_->getCurrentLife();

    if (life > 0.5f) {
        character_->setColor(0.0f, 1.0f, 0.0f);
    }
    else if (life > 0.25f) {
        character_->setColor(1.0f, 1.0f, 0.0f);
    }
    else if (life > 0.0f){
        character_->setColor(1.0f, 0.0f, 0.0f);
    }
    else {
        unsigned int score = scoreText_->getScore();

        if (score > highscore_) {
            std::ofstream outfile("C:/dev/uni/DTE-3609_VR_graphics_animation/start_code/resources/data/highscore.dat", std::ios::trunc);
            if (outfile){
                outfile << score;
            }
            else {
                std::cout << "COULD NOT OPEN HIGHSCORE FILE!" << std::endl;
            }

            outfile.close();
        }

        exit(0);
    }

    character_->setState(characterStates::normal);
}


std::shared_ptr<Camera> GameManager::getCam()
{
  return cam_;
}

std::shared_ptr<Character> GameManager::getCharacter()
{
  return character_;
}


