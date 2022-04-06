#pragma once

#include <windows.h>
#include <GL/freeglut.h>
#include <GL/gl.h>
#include <GL/glu.h>

#include "SceneObject.hpp"
#include "../../glm-master/glm/glm.hpp"

class Landscape : public SceneObject
{
	public:
        Landscape();
        ~Landscape();

  protected:
    virtual void privateInit();
		virtual void privateRender();
		virtual void privateUpdate();

	private:
    std::vector< glm::vec3 > vertexArray_; // Maybe two-dim vector and several arrays
    // normal array.
    std::vector< glm::vec3 > normalArray_;
    // texture coord array
    std::vector< glm::vec3 > textureArray_;
};

