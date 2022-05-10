//#include <windows.h>
//#include "GL/glew.h"
//#include <GL/glut.h>
//#include <GL/gl.h>


#include "../include/Minimap.hpp"
//#include "../include/GLErrorHandler.h"

//GLuint g_fbo;				// frame buffer object
//GLuint g_pbo;				// pixel buffer object
//GLuint g_texture;			// texture object
//int g_iTexWidth  = 512;		// texture width
//int g_iTexHeight = 512;		// texture height

Minimap::Minimap() {

}

Minimap::~Minimap() {
    glDeleteFramebuffersEXT(1, &g_fbo);
    glDeleteBuffers(1, &g_pbo);
}

void Minimap::privateInit() {
    // Create FBO
    glGenFramebuffers(1, &g_fbo);
    glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, g_fbo);

    // Initialize Texture
    glGenTextures(1, &g_texture);
    glBindTexture(GL_TEXTURE_2D, g_texture);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, g_iTexWidth, g_iTexHeight, 0, GL_BGRA, GL_UNSIGNED_BYTE, NULL);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

    // Attach Texture to Framebuffer Color Buffer
    glFramebufferTexture2DEXT(GL_FRAMEBUFFER_EXT, GL_COLOR_ATTACHMENT0_EXT, GL_TEXTURE_2D, g_texture, 0);
}

void Minimap::privateRender() {
//    glMatrixMode(GL_MODELVIEW);

    // render to texture
    glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, g_fbo);
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//    glLoadIdentity();

    // place camera/eye
//    glTranslatef(0.0f, 1000.0f, 100.0f);
//    glRotatef(0.0f,1.0,0.0,0.0);
//    glRotatef(-90.0f,0.0,1.0,0.0);

    // Save State
    float fPrevColor[4];
    int iPrevPolygonMode[2];
    glGetIntegerv(GL_POLYGON_MODE, iPrevPolygonMode);
    glGetFloatv(GL_CURRENT_COLOR, fPrevColor);

    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    glColor3f(0.683f, 0.113f, 0.234f);
//    glutSolidTorus(0.2f, 2.0f, 10, 100);
    //imdebugTexImage(GL_TEXTURE_2D, g_texture, GL_RGBA);

    glColor4fv(fPrevColor);
    glPolygonMode(GL_FRONT, iPrevPolygonMode[0]);
    glPolygonMode(GL_BACK, iPrevPolygonMode[1]);

    glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, 0);

    // render to screen
//    glClearColor(0.2f, 0.3f, 0.4f, 1.0f);
//    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//    glLoadIdentity();
//    glTranslatef(0.0f, 0.0f, -2.0f);

    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, g_texture);
    glBegin(GL_QUADS);
        glTexCoord2f(0.0f, 0.0f); glVertex3f(-100.0f, -50.0f, 100.0f);
        glTexCoord2f(1.0f, 0.0f); glVertex3f(-50.0f, -50.0f, 100.0f);
        glTexCoord2f(1.0f, 1.0f); glVertex3f(-50.0f, 0.0f, 100.0f);
        glTexCoord2f(0.0f, 1.0f); glVertex3f(-100.0f, 0.0f, 100.0f);
    glEnd();
    glDisable(GL_TEXTURE_2D);

//    glutSwapBuffers();
}

void Minimap::privateUpdate() {

}

void Minimap::CheckFrameBufferStatus() {
    GLenum eStatus = glCheckFramebufferStatusEXT(GL_FRAMEBUFFER_EXT);
    switch (eStatus)
    {
        // everything is OK
    case GL_FRAMEBUFFER_COMPLETE_EXT:
        break;

        // Unsupported Format
    case GL_FRAMEBUFFER_UNSUPPORTED_EXT:
        std::cout << "Error: Unsupported Format" << std::endl;
        break;

        // Other Error
    default:
        assert(0);
        break;
    }
}
