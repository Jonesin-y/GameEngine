#include "TestTexture2D.h"

test::TestTexture2D::TestTexture2D()
	:m_texturePath("res/textures/zzz.jpg")
{
	m_translation = glm::vec3(0.0f, 0.0f, 0.0f);
	m_texturePtr = new Texture(m_texturePath.c_str());
	m_ibPtr = new IndexBuffer(m_indices, 6);
	m_vbPtr=new VertexBuffer(m_positions, 2 * 8 * sizeof(float));
	m_layout.Push<float>(2);
	m_layout.Push<float>(2);
	m_va.AddBuffer(*m_vbPtr, m_layout);
	m_shaderPtr = new Shader("res/shaders/Basic.shader");
	m_proj = glm::ortho(0.0f, 960.0f, 0.0f, 640.0f, -1.0f, 1.0f);
	m_view = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 0.0f));
	m_model = glm::translate(glm::mat4(1.0f), m_translation);
	m_mvp = m_proj * m_view * m_model;
}

test::TestTexture2D::~TestTexture2D()
{
	m_texturePtr->UnBind();
	m_va.UnBind();
	m_vbPtr->Unbind();
	m_ibPtr->Unbind();
	m_shaderPtr->UnBind();
	delete m_texturePtr;
	delete m_ibPtr;
	delete m_vbPtr;
	delete m_shaderPtr;

}

void test::TestTexture2D::OnUpdate(float deltaTime)
{
	m_model = glm::translate(glm::mat4(1.0f), m_translation);
	m_mvp = m_proj * m_view * m_model;
}

void test::TestTexture2D::OnRender()
{
	m_shaderPtr->Bind();
	m_shaderPtr->SetUniformMat4f("u_MVP", m_mvp);
	m_shaderPtr->SetUniform1i("u_Texture", 0);
	m_texturePtr->Bind(0);
	m_renderer.Draw(m_va, *m_ibPtr, *m_shaderPtr);
}

void test::TestTexture2D::OnImGuiRender()
{
	ImGui::SliderFloat3("Translation", &m_translation.x, 0.0f, 960.0f);
}
