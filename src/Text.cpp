#include "../include/Text.hpp"

Text::Text(std::string string)
    :string_(string)
{

}

Text::~Text() {

}

void Text::privateInit()
{
    string_ += std::to_string(score_);
}

void Text::privateRender() {
    glEnable(GL_COLOR_MATERIAL);
    glColor3f(1.0f, 1.0f, 1.0f);

//    glRasterPos3f(-100.0f, 200.0f, 0.0f);
    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();

    glRasterPos3f(-0.9f, -0.9f, 0.0f);

    glLineWidth(1.0f);

    for (char& c : string_) {
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, c);
    }

    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
    glMatrixMode(GL_MODELVIEW);
    glPopMatrix();

    glLineWidth(1.0f);

    glDisable(GL_COLOR_MATERIAL);
}

void Text::privateUpdate() {
    score_++;
    string_.resize(7);
    string_ += std::to_string(score_);
}
