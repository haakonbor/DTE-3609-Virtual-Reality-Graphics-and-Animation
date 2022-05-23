#pragma once

#include <windows.h>

#include "SceneObject.hpp"
#include "Landscape.hpp"
#include "Character.hpp"
#include "Camera.hpp"
#include "Snow.hpp"
#include "Text.hpp"
#include "Minimap.hpp"

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
    std::shared_ptr<Landscape> ls1_;
    std::shared_ptr<Landscape> ls2_;
    std::shared_ptr<Landscape> ls3_;
    std::shared_ptr<Landscape> ls4_;
    std::shared_ptr<Character> character_;
    std::shared_ptr<Camera> cam_;
    std::shared_ptr<Snow> snow_;
    std::shared_ptr<Text> text_;
    std::shared_ptr<Minimap> minimap_;
};

