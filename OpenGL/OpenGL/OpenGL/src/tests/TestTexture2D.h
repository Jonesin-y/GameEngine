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
		unsigned int m_indices[12]={
			0,1,2,
			0,3,2,
			4,5,6,
			4,7,6
		};
		float m_positions[48] = {
			0.0f,  0.0f,  1.0f,0.0f,0.0f,1.0f, //0
			0.0f,  200.0f,0.0f,0.0f,1.0f,1.0f, //1
			200.0f,200.0f,0.0f,1.0f,0.0f,1.0f, //2
			200.0f,0.0f,  1.0f,1.0f,0.0f,1.0f, //3
			400.0f,0.0f,  0.2f,0.5f,0.8f,1.0f, //4
			400.0f,200.0f,0.2f,0.5f,0.8f,1.0f,//5
			600.0f,200.0f,0.2f,0.5f,0.8f,1.0f,//6
			600.0f,0.0f,  0.2f,0.5f,0.8f,1.0f//7
		};
		std::string m_texturePathA;
		std::string m_texturePathB;
		glm::mat4 m_proj, m_view, m_model, m_mvp;
		glm::vec3 m_translationA;
		glm::vec3 m_translationB;
		Texture* m_texturePtrA;
		Texture* m_texturePtrB;
		Shader* m_shaderPtr;
		VertexBuffer* m_vbPtr;
		IndexBuffer* m_ibPtr;
		VertexBufferLayout m_layout;
		Renderer m_renderer;
		VertexArray m_va;
		int m_samplers[2] = { 0,1 };
	public:
		TestTexture2D();
		~TestTexture2D();
		virtual void OnUpdate(float deltaTime) override;
		virtual void OnRender() override;
		virtual void OnImGuiRender() override;
	};
}