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
		void OnUpdate()override;
		void OnEvent(Event& event)override;
		void OnAttach()override;
		void OnDetach()override;

	private:
		float m_Time = 0.0f;
		//Mouse Event
		bool OnMouseButtonPressedEvent(MouseButtonPressedEvent& e);
		bool OnMouseButtonReleasedEvent(MouseButtonReleasedEvent& e);
		bool OnMouseMovedEvent(MouseMovedEvent& e);
		bool OnMouseScrolledEvent(MouseScrolledEvent& e);
		//Key Event
		bool OnKeyPressedEvent(KeyPressedEvent& e);
		bool OnKeyReleasedEvent(KeyReleasedEvent& e);
		//Window Event
		bool OnWindowResizedEvent(WindowResizeEvent& e);
		bool OnWindowClosedEvent(WindowCloseEvent& e);
		bool OnWindowMovedEvent(WindowMovedEvent& e);
		bool OnWindowFocusedEvent(WindowFocusEvent& e);
	};
}