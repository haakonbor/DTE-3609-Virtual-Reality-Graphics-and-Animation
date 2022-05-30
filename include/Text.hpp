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
        Text(std::string string);
        ~Text();

        unsigned int getScore() { return score_; }

        void setScore(unsigned int newScore) { score_ = newScore; }

    protected:
        void privateInit();
        void privateRender();
        void privateUpdate();


    private:
        std::string string_;
        unsigned int score_ = 0;
};


