#pragma once

#include <windows.h>

#include "SceneObject.hpp"
#include "Plane.hpp"
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
    std::shared_ptr<Plane> ls1_;
    std::shared_ptr<Plane> ls2_;
    std::shared_ptr<Plane> ls3_;
    std::shared_ptr<Plane> ls4_;
    std::shared_ptr<Plane> ls5_;

    std::shared_ptr<Plane> sbw_;
    std::shared_ptr<Plane> sbn_;
    std::shared_ptr<Plane> sbe_;
    std::shared_ptr<Plane> sbs_;
    std::shared_ptr<Plane> sbu_;
    std::shared_ptr<Plane> sbd_;
    std::shared_ptr<Character> character_;
    std::shared_ptr<Camera> cam_;
    std::shared_ptr<Snow> snow_;
    std::shared_ptr<Text> text_;
    std::shared_ptr<Minimap> minimap_;
};

