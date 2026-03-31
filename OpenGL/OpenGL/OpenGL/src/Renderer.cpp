#include"Renderer.h"
#include<iostream>
void GLCleanError()
{
    GLenum error = glGetError();
    while (glGetError())
    {

    }
}
bool GLLogCall(const char* function, const char* filename, int line)
{

    while (GLenum error = glGetError())
    {
        std::cout << "OpenGL" << "(" << error << ")" << " " << "function:" << function << " " << "filename:" << filename << " " << "line:" << line << std::endl;
        return false;

    }
    return true;
}