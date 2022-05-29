#pragma once

#include <windows.h>

#include "SceneObject.hpp"
#include "Plane.hpp"
#include "Character.hpp"
#include "Camera.hpp"
#include "Snow.hpp"
#include "Text.hpp"
#include "Minimap.hpp"
#include "Skybox.h"
#include "Obstacle.h"

#include <GL/gl.h>
#include <GL/glu.h>




class GameManager : public SceneObject
{
	public:
		GameManager();
		~GameManager();
    
    std::shared_ptr<Camera> getCam();
    std::shared_ptr<Character> getCharacter();

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
    std::shared_ptr<Text> text_;
    std::shared_ptr<Minimap> minimap_;

    void checkCollisions();
    void handleCollision(std::shared_ptr<Obstacle> obs);
    void resetCharacterAfterCollision();
};

