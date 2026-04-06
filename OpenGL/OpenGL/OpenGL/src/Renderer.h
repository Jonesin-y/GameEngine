#pragma once
#include<GL/glew.h>
class VertexArray;
class IndexBuffer;
class Shader;
#define ASSERT(x) if(!(x)) __debugbreak()
#define GLCALL(x) GLCleanError();\
    x;\
    ASSERT(GLLogCall(#x,__FILE__,__LINE__))
void GLCleanError();
bool GLLogCall(const char* function, const char* filename, int line);
class Renderer
{
public:
    void Draw(const VertexArray& va, const IndexBuffer& ib, const Shader& shader)const;
    void Clear()const;
};