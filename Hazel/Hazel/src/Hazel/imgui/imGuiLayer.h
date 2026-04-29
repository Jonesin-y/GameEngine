#pragma once
#include"Core.h"
#include"Layer.h"
namespace Hazel
{
	class HAZEL_API imGuiLayer : public Layer
	{
	public:
		imGuiLayer();
		~imGuiLayer();
		void OnUpdate()override;
		void OnEvent(Event& event)override;
		void OnAttach()override;
		void OnDetach()override;
	private:
		float m_Time = 0.0f;
	};
}