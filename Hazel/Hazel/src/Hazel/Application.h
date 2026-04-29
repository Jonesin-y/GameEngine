#pragma once
#include "hzpch.h"
#include "Core.h"
#include "events/ApplicationEvent.h"
#include "window.h"
#include"Layer.h"
#include"LayerStack.h"
namespace Hazel {
	class HAZEL_API Application
	{
	public:
		Application();
		virtual ~Application();
		void OnEvent(Event& e);
		void PushLayer(Layer* layer)	;	
		void PushOverlay(Layer* overlay);	
		void PopLayer(Layer* layer)		;	
		void PopOverlay(Layer* overlay)	;
		void Run();
	private:
		bool OnWindowClose(WindowCloseEvent& event);
		std::unique_ptr<Window> m_Window;
		LayerStack m_LayerStack;
		bool m_Running = true;
	};
	Application* CreateApplication();

}
