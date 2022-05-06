#pragma once

#include <windows.h>
#include <GL/freeglut.h>
//#include <GL/gl.h>
#include <GL/glu.h>

#include "SceneObject.hpp"
#include "../../glm-master/glm/glm.hpp"

#define MAX_PARTICLES 2000

typedef struct						// Create A Structure For Particle
{
    bool	active;					// Active (Yes/No)
    float	life;					// Particle Life
    float	fade;					// Fade Speed
    float	r;						// Red Value
    float	g;						// Green Value
    float	b;						// Blue Value
    float	x;						// X Position
    float	y;						// Y Position
    float	z;						// Z Position
    float	xi;						// X Direction
    float	yi;						// Y Direction
    float	zi;						// Z Direction
    float	xg;						// X Gravity
    float	yg;						// Y Gravity
    float	zg;						// Z Gravity
}
particle;							// Particle Structure

class Snow : public SceneObject
{
    public:
        Snow();
        ~Snow();

    protected:
    void privateInit();
    void privateRender();
    void privateUpdate();
    void setUpTexture();

    private:
    unsigned int texture;
    particle particles[MAX_PARTICLES];
    float slowdown = 2.0f;
    float zoom = -40.0f;
    GLuint loop;
};

