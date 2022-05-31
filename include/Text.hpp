#pragma once

#include <windows.h>
//#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <string>
#include "SceneObject.hpp"

class Text : public SceneObject
{
    public:
        Text(std::string string, float x, float y, float z);
        ~Text();

    protected:
        void privateInit();
        void privateRender();
        void privateUpdate();


    private:
        float pos_x;
        float pos_y;
        float pos_z;
        std::string string_;
};


