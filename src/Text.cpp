#include "../include/Text.hpp"

Text::Text() {

}

Text::~Text() {

}

void Text::privateInit() {
    string_ = "This is a test";
}

void Text::privateRender() {
    glEnable(GL_COLOR_MATERIAL);
    glColor3f(1.0f, 1.0f, 1.0f);

    glRasterPos3f(-100.0f, 200.0f, 0.0f);
    glLineWidth(100.0f);

    for (char& c : string_) {
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, c);
    }

    glLineWidth(1.0f);

    glDisable(GL_COLOR_MATERIAL);
}

void Text::privateUpdate() {

}
