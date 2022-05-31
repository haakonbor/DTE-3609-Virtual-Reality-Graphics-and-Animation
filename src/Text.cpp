#include "../include/Text.hpp"

Text::Text(std::string string, float x, float y, float z, bool constant, unsigned int score)
    :pos_x(x), pos_y(y), pos_z(z), string_(string), stringLength_(string.length()), constant_(constant), score_(score)
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

    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();

    glRasterPos3f(pos_x, pos_y, pos_z);

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
    if (!constant_) {
        score_++;
        string_.resize(stringLength_);
        string_ += std::to_string(score_);
    }
}
