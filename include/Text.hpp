#pragma once

#include <windows.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <string>
#include "SceneObject.hpp"

class Text : public SceneObject
{
    public:
        Text();
        ~Text();

    protected:
        void privateInit();
        void privateRender();
        void privateUpdate();


    private:
        std::string string_;
};


