#include "../include/Text.hpp"

Text::Text(std::string string, float x, float y, float z)
    :pos_x(x), pos_y(y), pos_z(z), string_(string)
{

}

Text::~Text() {

}

void Text::privateInit()
{

}

void Text::privateRender() {
    glEnable(GL_COLOR_MATERIAL);
    glColor3f(1.0f, 1.0f, 1.0f);

    // Save and reset matrices
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

    // Load matrices
    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
    glMatrixMode(GL_MODELVIEW);
    glPopMatrix();

    glLineWidth(1.0f);

    glDisable(GL_COLOR_MATERIAL);
}

void Text::privateUpdate() {

}
