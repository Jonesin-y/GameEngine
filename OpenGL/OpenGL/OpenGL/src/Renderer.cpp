#include"Renderer.h"
#include"VertexBufferLayout.h"
#include"IndexBuffer.h"
#include"VertexArray.h"
#include"shader.h"
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

void Renderer::Draw(const VertexArray& va, const IndexBuffer& ib, const Shader& shader)const
{
    shader.Bind();
    va.Bind();
    ib.Bind();
    GLCALL(glDrawElements(GL_TRIANGLES, ib.GetCount(), GL_UNSIGNED_INT, nullptr));

}

void Renderer::Clear()const
{
    GLCALL(glClear(GL_COLOR_BUFFER_BIT));
}
