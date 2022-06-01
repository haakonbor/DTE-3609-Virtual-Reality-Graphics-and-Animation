#include "../include/GLErrorHandler.h"

// Empty the error "stack"
void GLClearError() {
    while (glGetError() != GL_NO_ERROR) {

    }
}

// Print error number, function, file and line number to console
bool GLLogCall(const char* function, const char* file, int line) {
    while (GLenum error = glGetError()) {
        std::cout << "OpenGL error: " << std::hex << error << "\nFunction: " << function << "\nFile: " << file << "\nLine: " << line << std::endl;
        return false;
    }

    return true;
}
