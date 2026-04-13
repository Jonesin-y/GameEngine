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
#include"tests/TestClearColor.h"
#include"tests/test.h"



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
    
    
    glfwSwapInterval(1);
    
    
    ImGui::CreateContext();
    ImGui_ImplGlfwGL3_Init(window, true);
    ImGui::StyleColorsDark();
    bool show_demo_window = true;
    bool show_another_window = false;
    ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);
    Renderer renderer;
    test::Test* currentTest = nullptr;
    test::TestMenu* testMenu = new test::TestMenu(currentTest);
    testMenu->TestRegister<test::TestClearColor>("Clear Test");
    currentTest = testMenu;
    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        GLCALL(glClearColor(0.0f, 0.0f, 0.0f, 1.0f));
        renderer.Clear();
        ImGui_ImplGlfwGL3_NewFrame();
        if (currentTest)
        {
            currentTest->OnUpdate(0.0f);
            
            currentTest->OnRender();
            
            ImGui::Begin("Test");
            if (currentTest != testMenu && ImGui::Button("<-"))
            {
                delete currentTest;
                currentTest = testMenu;
            }
            currentTest->OnImGuiRender();
            ImGui::End();

        }
       
      
        /* Render here */
      
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
    delete currentTest;
    if (currentTest != testMenu)
        delete testMenu;
    return 0;
}