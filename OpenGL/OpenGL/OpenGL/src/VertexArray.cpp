#include "VertexArray.h"
#include"VertexBufferLayout.h"
#include"VertexBuffer.h"
VertexArray::VertexArray()
{
	GLCALL(glGenVertexArrays(1,&m_RendererID));
}

VertexArray::~VertexArray()
{
	UnBind();
	GLCALL(glDeleteVertexArrays(1, &m_RendererID));
	
}

void VertexArray::Bind() const
{
	GLCALL(glBindVertexArray(m_RendererID));
}
void VertexArray::UnBind()const
{
	GLCALL(glBindVertexArray(0));
}

void VertexArray::AddBuffer(const VertexBuffer& vb, const VertexBufferLayout& layout)
{

	Bind();
	vb.Bind();
	
	const auto& elements = layout.GetElements();
	unsigned int offset = 0;
	for (int i = 0;i < elements.size();++i)
	{
		const auto& element = elements[i];
		unsigned int stride = layout.GetStride();
		GLCALL(glEnableVertexAttribArray(i));
		GLCALL(glVertexAttribPointer(i, element.count, element.type, element.normalized,stride,(const void*)offset));
		unsigned int size = VertexBufferElement::GetSizeOfType(element.type);
		offset += element.count * size;
	}
}
