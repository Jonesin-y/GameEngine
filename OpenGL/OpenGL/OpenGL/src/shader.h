#pragma once

#include<string>
#include<unordered_map>
#include"glm/glm.hpp"
struct ShaderProgramSource
{
	std::string VertexSource;
	std::string FragmentSource;
};
class Shader
{
private:
	unsigned int m_RendererID;
	std::string m_FilePath;
	ShaderProgramSource m_Source;
	std::unordered_map<std::string, int>m_UniformNameCache;
public:
	Shader(const std::string& filename);
	~Shader();
	void Bind() const;
	void UnBind() const;
	ShaderProgramSource ParseShader(const std::string& filename);
	//Create Shader
	unsigned int CompileShader(unsigned int type, const std::string& src);
	unsigned int CreateShader(const std::string& vs_src, const std::string& fs_src);
	//Set Uniform
	void SetUniform4f(const std::string& name, float v0, float v1, float v2, float v3);
	void SetUniformMat4f(const std::string& name, const glm::mat4& matrix);
	void SetUniform1i(const std::string& name, int value);
	void SetUniformArray2i(const std::string& name, int values[]);
	int GetUniformLocation(const std::string& name);
};