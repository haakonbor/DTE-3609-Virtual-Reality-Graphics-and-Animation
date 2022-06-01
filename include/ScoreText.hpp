#pragma once

#include <windows.h>
//#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <string>
#include "SceneObject.hpp"

class ScoreText : public SceneObject
{
    public:
        ScoreText(std::string string, float x, float y, float z, bool constant = false, unsigned int score = 0);
        ~ScoreText();

        unsigned int getScore() { return score_; }

        void setScore(unsigned int newScore) { score_ = newScore; }
        void setIncrement(unsigned int newIncrement) { increment_ = newIncrement; }

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
        unsigned int increment_ = 1;
};


