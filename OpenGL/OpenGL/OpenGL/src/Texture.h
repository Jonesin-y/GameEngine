#pragma once
#include"Renderer.h"

#include <string>
class Texture
{
private:
	unsigned int m_RendererID;
	int m_Width, m_Height, m_BBP;
	unsigned char* m_LocalBuffer;
	std::string m_TexFilePath;
public:
	Texture(const char* file_name);
	~Texture();
	void Bind(unsigned int slot)const;
	void UnBind()const;
	inline int GetWidth()const { return m_Width; }
	inline int GetHeight()const { return m_Height; }
};