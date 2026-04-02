#pragma once
#include"Renderer.h"
#include"VertexBufferLayout.h"
#include"VertexBuffer.h"
class VertexArray
{
private:
	unsigned int m_RendererID;
public:
	VertexArray();
	~VertexArray();
	void Bind() const;
	void UnBind() const;
	void AddBuffer(const VertexBuffer& vb, const VertexBufferLayout& layout);

	
};