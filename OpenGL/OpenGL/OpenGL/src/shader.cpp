#include "shader.h"
#include"Renderer.h"
#include <fstream>
#include<sstream>
#include<GL/glew.h>
#include<iostream>
Shader::Shader(const std::string& filename) :m_FilePath(filename), m_RendererID(0)
{
	m_Source = Shader::ParseShader(filename);
	GLCALL(m_RendererID = CreateShader(m_Source.VertexSource,m_Source.FragmentSource));
	
}
Shader::~Shader()
{
	GLCALL(glDeleteProgram(m_RendererID));
}
void Shader::Bind() const
{
	GLCALL(glUseProgram(m_RendererID));
}

void Shader::UnBind() const
{
	GLCALL(glUseProgram(0));
}

ShaderProgramSource Shader::ParseShader(const std::string& filename)
{
	
	enum class ShaderType
	{
		NONE = -1, VERTEX = 0, FRAGMENT = 1
	};
	std::ifstream stream(filename);
	if (!stream.is_open())
	{
		std::cout << "打开失败" << std::endl;
		return { "","" };
	}
	std::string line;
	std::stringstream ss[2];
	ShaderType type = ShaderType::NONE;
	while (getline(stream, line))
	{
		if (line.find("#shader") != std::string::npos)
		{
			if (line.find("vertex")!=std::string::npos)
				type = ShaderType::VERTEX;
			if (line.find("fragment")!=std::string::npos)
				type = ShaderType::FRAGMENT;
		}
		else if(type!=ShaderType::NONE)
		{
			ss[(int)type] << line << '\n';
		}
	}
	return { ss[0].str(),ss[1].str() };
}

unsigned int Shader::CompileShader(unsigned int type, const std::string& src)
{
	GLCALL(unsigned int id = glCreateShader(type));
	const char* src_cstr = src.c_str();
	GLCALL(glShaderSource(id, 1, &src_cstr, NULL));
	GLCALL(glCompileShader(id));
	int result;
	GLCALL(glGetShaderiv(id, GL_COMPILE_STATUS, &result));
	if (result == GL_FALSE)
	{
		int length;
		GLCALL(glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length));
		char* message = (char*)alloca(length * sizeof(char));
		GLCALL(glGetShaderInfoLog(id, length, &length, message));
		std::cout << "Failed to compile:" << ((type == GL_VERTEX_SHADER) ? "vertex" : "fragment" )<< " shader" << std::endl;
		std::cout << message << std::endl;
		GLCALL(glDeleteShader(id));
		return 0;
	}
	return id;
}

unsigned int Shader::CreateShader(const std::string& vs_src, const std::string& fs_src)
{
	GLCALL(unsigned int program = glCreateProgram());
	GLCALL(unsigned int vs_id = CompileShader(GL_VERTEX_SHADER, vs_src));
	GLCALL(unsigned int fs_id = CompileShader(GL_FRAGMENT_SHADER, fs_src));
	GLCALL(glAttachShader(program,vs_id));
	GLCALL(glAttachShader(program, fs_id));
	GLCALL(glLinkProgram(program));
	GLCALL(glValidateProgram(program));
	GLCALL(glDeleteShader(vs_id));
	GLCALL(glDeleteShader(fs_id));
	return program;
}

void Shader::SetUniform4f(const std::string& name, float v0, float v1, float v2, float v3)
{
	int location = GetUniformLocation(name);
	GLCALL(glUniform4f(location, v0, v1, v2, v3));
}

void Shader::SetUniformMat4f(const std::string& name, const glm::mat4& matrix)
{
	int location = GetUniformLocation(name);
	GLCALL(glUniformMatrix4fv(location, 1, GL_FALSE, &matrix[0][0]));
}

void Shader::SetUniform1i(const std::string& name, int value)
{
	int location = GetUniformLocation(name);
	GLCALL(glUniform1i(location,value));
}

void Shader::SetUniformArray2i(const std::string& name, int values[])
{
	int location = GetUniformLocation(name);
	GLCALL(glUniform1iv(location, 2, values));
}
int Shader::GetUniformLocation(const std::string& name)
{
	if (m_UniformNameCache.find(name) != m_UniformNameCache.end())
	{
		return m_UniformNameCache[name];
	}
	GLCALL(int location = glGetUniformLocation(m_RendererID, name.c_str()));
	if (location == -1)
	{
		std::cout << "WARNING:uniform " << name << " donesn't exist!" << std::endl;
	}
	else {
		m_UniformNameCache[name] = location;
	}
	return location;
}
