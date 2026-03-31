#pragma once
#include<GL/glew.h>
#define ASSERT(x) if(!(x)) __debugbreak()
#define GLCALL(x) GLCleanError();\
    x;\
    ASSERT(GLLogCall(#x,__FILE__,__LINE__))
void GLCleanError();
bool GLLogCall(const char* function, const char* filename, int line);