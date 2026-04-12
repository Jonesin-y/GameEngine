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
#include"glm/glm.hpp"
#include"glm/gtc/matrix_transform.hpp"
#include"imgui/imgui.h"
#include"imgui/imgui_impl_glfw_gl3.h"

float positions[] = {
    100.0f,100.0f,0.0f,0.0f,//0
     200.0f,100.0f,1.0f,0.0f,//1
     200.0f, 200.0f,1.0f,1.0f,//2
    100.0f,200.0f,0.0f,1.0f//3
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
    window = glfwCreateWindow(960, 640, "Hello World", NULL, NULL);
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
    GLCALL(glEnable(GL_BLEND));
    GLCALL(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));
    Texture texture("res/textures/zzz.jpg");

    VertexArray va;
    VertexBuffer vb(positions, 4 * 4 * sizeof(float));
    VertexBufferLayout layout;
    layout.Push<float>(2);
    layout.Push<float>(2);
    va.AddBuffer(vb, layout);
    glfwSwapInterval(2);
    

    IndexBuffer ibo(indices, 6);
    glm::mat4 proj = glm::ortho(0.0f, 960.0f, 0.0f, 640.0f, -1.0f, 1.0f);
    glm::mat4 view = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 0.0f));
    glm::vec3 translationA(200.0f, 200.0f, 0.0f);
    glm::vec3 translationB(400.0f, 400.0f, 0.0f);
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
    ImGui::CreateContext();
    ImGui_ImplGlfwGL3_Init(window, true);
    ImGui::StyleColorsDark();
    bool show_demo_window = true;
    bool show_another_window = false;
    ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);
    Renderer renderer;
    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        renderer.Clear();
        ImGui_ImplGlfwGL3_NewFrame();
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
        {
            // Display some text (you can use a format string too)
            ImGui::SliderFloat3("Translation", &translationA.x, 0.0f, 960.0f);            // Edit 1 float using a slider from 0.0f to 1.0f    
            ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
        }
        {
            glm::mat model = glm::translate(glm::mat4(1.0f), translationA);
            glm::mat4 mvp = proj * view * model;

            GLCALL(shader.SetUniform1i("u_Texture", 0));
            GLCALL(shader.SetUniformMat4f("u_MVP", mvp));
            renderer.Draw(va, ibo, shader);
        }
        /* Render here */
        {
            glm::mat model = glm::translate(glm::mat4(1.0f), translationB);
            glm::mat4 mvp = proj * view * model;

            GLCALL(shader.SetUniform1i("u_Texture", 0));
            GLCALL(shader.SetUniformMat4f("u_MVP", mvp));
            renderer.Draw(va, ibo, shader);
        }
        ImGui::Render();
        ImGui_ImplGlfwGL3_RenderDrawData(ImGui::GetDrawData());
        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }
    ImGui_ImplGlfwGL3_Shutdown();
    ImGui::DestroyContext();
    glfwTerminate();
    return 0;
}