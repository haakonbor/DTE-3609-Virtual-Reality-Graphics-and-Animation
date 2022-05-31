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
        Text(std::string string, float x, float y, float z, bool constant = false, unsigned int score = 0);
        ~Text();

        unsigned int getScore() { return score_; }

        void setScore(unsigned int newScore) { score_ = newScore; }

    protected:
        void privateInit();
        void privateRender();
        void privateUpdate();


    private:
        float pos_x;
        float pos_y;
        float pos_z;
        std::string string_;
        unsigned int stringLength_;
        bool constant_;
        unsigned int score_ = 0;
};


