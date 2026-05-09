#pragma once
#include"Core.h"
#include"Layer.h"
#include"events/Event.h"
#include"events/MouseEvent.h"
#include"events/KeyEvent.h"
#include"events/ApplicationEvent.h"
namespace Hazel
{
	class HAZEL_API imGuiLayer : public Layer
	{
		
	public:
		imGuiLayer();
		~imGuiLayer();
		
		virtual void OnAttach()override;
		virtual void OnDetach()override;
		virtual void Begin();
		virtual void OnImGuiRender() override;
		virtual void End();
	private:
		float m_Time = 0.0f;
		//Mouse Event
		
	};
}