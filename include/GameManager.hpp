#pragma once

#include <windows.h>

#include "SceneObject.hpp"
#include "Plane.hpp"
#include "Character.hpp"
#include "Camera.hpp"
#include "Snow.hpp"
#include "ScoreText.hpp"
#include "Text.hpp"
#include "Skybox.h"
#include "Obstacle.h"
#include "Billboard.h"

#include <GL/gl.h>
#include <GL/glu.h>

class GameManager : public SceneObject
{
	public:
		GameManager();
		~GameManager();
    
    std::shared_ptr<Camera> getCam();
    std::shared_ptr<Character> getCharacter();
    std::shared_ptr<ScoreText> getScoreText();

  protected:
    virtual void privateInit();
		virtual void privateRender();
		virtual void privateUpdate();

	private:
    std::vector<std::shared_ptr<Plane>> landscape_;
    std::shared_ptr<Skybox> sb_;
    std::shared_ptr<Character> character_;
    std::vector<std::shared_ptr<Obstacle>> obstacles_;
    std::shared_ptr<Camera> cam_;
    std::shared_ptr<Snow> snow_;
    std::shared_ptr<ScoreText> scoreText_;
    std::shared_ptr<Text> highscoreText_;
    std::shared_ptr<Text> controlsText_;
    std::shared_ptr<Text> upgradeText1_;
    std::shared_ptr<Text> upgradeText2_;
    std::shared_ptr<Billboard> gameoverBillboard_;

    void checkCollisions();
    void handleCollision(std::shared_ptr<Obstacle> obs);
    void resetCharacterAfterCollision();

    unsigned int highscore_ = 0;
};

