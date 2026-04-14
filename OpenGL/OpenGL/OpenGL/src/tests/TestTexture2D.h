#pragma once
#include"test.h"
#include"Texture.h"
#include"glm/glm.hpp"
#include"glm/gtc/matrix_transform.hpp"
#include"imgui/imgui.h"
#include"Renderer.h"
#include"shader.h"
#include"VertexBufferLayout.h"
#include"VertexArray.h"
#include"IndexBuffer.h"
#include"VertexBuffer.h"
#include<string>
namespace test
{
	class TestTexture2D :public Test
	{
	private:
		unsigned int m_indices[6]={
			0,1,2,
			0,3,2
		};
		float m_positions[16] = {
			200.0f,200.0f,0.0f,0.0f,
			200.0f,400.0f,0.0f,1.0f,
			400.0f,400.0f,1.0f,1.0f,
			400.0f,200.0f,1.0f,0.0f
		};
		std::string m_texturePath;
		glm::mat4 m_proj, m_view, m_model, m_mvp;
		glm::vec3 m_translation;
		Texture* m_texturePtr;
		Shader* m_shaderPtr;
		VertexBuffer* m_vbPtr;
		IndexBuffer* m_ibPtr;
		VertexBufferLayout m_layout;
		Renderer m_renderer;
		VertexArray m_va;
	public:
		TestTexture2D();
		~TestTexture2D();
		virtual void OnUpdate(float deltaTime) override;
		virtual void OnRender() override;
		virtual void OnImGuiRender() override;
	};
}