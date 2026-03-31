#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include<string>
#include<iostream>
#include<fstream>
#include<sstream>
#include"Renderer.h"
#include"VertexBuffer.h"
#include"IndexBuffer.h"
struct ShaderProgramSource
{
    std::string VertexSource;
    std::string FragmentSource;
};
ShaderProgramSource ParseShader(std::string filename)
{
    enum class ShaderType
    {
        NONE=-1, VERTEX=0, FRAGMENT=1
	};
    std::ifstream stream(filename);
    if (!stream.is_open())
    {
        std::cout << "读取失败" << std::endl;
		return { "", "" };
    }
    std::string line;
	std::stringstream ss[2];
	ShaderType type = ShaderType::NONE;
    while (getline(stream, line))
    {
        if (line.find("#shader")!=std::string::npos)
        {
            if (line.find("vertex") != std::string::npos)
                type = ShaderType::VERTEX;
            if (line.find("fragment") != std::string::npos)
                type = ShaderType::FRAGMENT;
        }
        else
        {
			ss[(int)type] << line << '\n';
        }
    }
	return { ss[0].str(),ss[1].str() };
}

float positions[] = {
    -0.5f, -0.5f,//0
     0.5f, -0.5f,//1
     0.5f, 0.5f,//2
    -0.5f,0.5f,//3
};
unsigned int indices[] = {
    0,1,2,
    2,3,0
};
static unsigned int CompileShader(unsigned int type, const std::string& src)
{
	unsigned int id = glCreateShader(type);
	const char* src_cstr = src.c_str();
    glShaderSource(id, 1, &src_cstr,NULL);
    glCompileShader(id);
	//TODO: Error handling
    int result;
    glGetShaderiv(id, GL_COMPILE_STATUS, &result);
    if (result == GL_FALSE)
    {
        int length;
		glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
        char* message = (char*)alloca(length * sizeof(char));
        glGetShaderInfoLog(id, length, &length, message);
        std::cout << "Failed to compile" << (type == GL_VERTEX_SHADER ? "vertex" : "fragment") << "shader" << std::endl;
        std::cout << message << std::endl;
        glDeleteShader(id);
        return 0;
    }
    return id;
}
static unsigned int CreateShader(const std::string& vs_src, const std::string& fs_src)
{
    unsigned int program = glCreateProgram();
    unsigned int vs_id = CompileShader(GL_VERTEX_SHADER, vs_src);
    unsigned int fs_id = CompileShader(GL_FRAGMENT_SHADER, fs_src);
    glAttachShader(program, vs_id);
    glAttachShader(program, fs_id);
	glLinkProgram(program);
	glValidateProgram(program);
    glDeleteShader(vs_id);
    glDeleteShader(fs_id);
    return program;
}

ShaderProgramSource source = ParseShader("res/shaders/Basic.shader");
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
    unsigned int vao;
    glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);
    glfwSwapInterval(2);
    VertexBuffer vb(positions, 4*2*sizeof(float));
    vb.Bind();
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 2, (const void*)0);
    IndexBuffer ibo(indices, 6);
    ibo.Bind();
	std::cout << "Vertex shader: " << std::endl;
    std::cout << source.VertexSource << std::endl;
    std::cout << "Fragment shader:" << std::endl;
    std::cout << source.FragmentSource << std::endl;

    unsigned shader = CreateShader(source.VertexSource ,source.FragmentSource);
	glUseProgram(shader);
	int location = glGetUniformLocation(shader, "u_Color");
    ASSERT(location != -1);
	float r = 0.0f;
    float e = 0.8f;
    float d = 0.2f;
	float a = 1.0f;
	float p1 = 0.05f;
	float p2 = 0.05f;
	float p3 = 0.05f;
	float p4 = 0.05f;
    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
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
		glUseProgram(shader);
		

        GLCALL(glUniform4f(location, r, e, d, a));
        /* Render here */
        GLCALL(glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr));
        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }
	glDeleteProgram(shader);

    glfwTerminate();
    return 0;
}