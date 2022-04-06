#pragma once

#include <windows.h>
#include <GL/gl.h>
#include <GL/glu.h>

#include "SceneObject.hpp"
#include "Landscape.hpp"
#include "Character.hpp"
#include "Camera.hpp"

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
    std::shared_ptr<Landscape> ls_;
    std::shared_ptr<Character> character_;
    std::shared_ptr<Camera> cam_;
};

