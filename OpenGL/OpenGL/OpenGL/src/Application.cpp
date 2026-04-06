#include"IndexBuffer.h"
#include"Renderer.h"
#include"VertexArray.h"
#include"VertexBuffer.h"
#include"VertexBufferLayout.h"
#include"shader.h"
#include"Texture.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include<fstream>
#include<iostream>
#include<sstream>
#include<string>

float positions[] = {
    -0.5f, -0.5f,0.0f,0.0f,//0
     0.5f, -0.5f,1.0f,0.0f,//1
     0.5f, 0.5f,1.0f,1.0f,//2
    -0.5f,0.5f,0.0f,1.0f//3
};
unsigned int indices[] = {
    0,1,2,
    2,3,0
};


int main(void)
{
    GLFWwindow* window;

    /* Initialize the library */
    if (!glfwInit())
        return -1;

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    /* Make the window's context current */
    glfwMakeContextCurrent(window);
    if (glewInit() != GLEW_OK)
    {
        std::cout << "ERROR!" << std::endl;
    }
    std::cout << "OpenGL Version: " << glGetString(GL_VERSION) << std::endl;
    Texture texture("res/textures/godot.png");

    VertexArray va;
    VertexBuffer vb(positions, 4 * 4 * sizeof(float));
    VertexBufferLayout layout;
    layout.Push<float>(2);
    layout.Push<float>(2);
    va.AddBuffer(vb, layout);
    glfwSwapInterval(2);
    

    IndexBuffer ibo(indices, 6);
    Shader shader("res/shaders/Basic.shader");
    int location = 0;
    ASSERT(location != -1);
	float r = 0.0f;
    float e = 0.8f;
    float d = 0.2f;
	float a = 1.0f;
	float p1 = 0.05f;
	float p2 = 0.05f;
	float p3 = 0.05f;
	float p4 = 0.05f;
    Renderer renderer;
    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        renderer.Clear();
        if (r > 1.0) { p1 = -0.05f; }
        else if (r < 0.0) { p1 = 0.05f; }
        if (e > 1.0) { p2 = -0.04f; }
        else if (e < 0.0) { p2 = 0.04f; }
        if (e > 1.0) { p3 = -0.03f; }
        else if (e < 0.0) { p3 = 0.03f; }
        if (e > 1.0) { p4 = -0.02f; }
        else if (e < 0.0) { p4 = 0.02f; }
		r += p1;
        e += p2;
		d += p3;
		a += p4;
        shader.Bind();
		
        GLCALL(shader.SetUniform1i("u_Texture", 0));
        renderer.Draw(va, ibo, shader);
        /* Render here */
        
        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}