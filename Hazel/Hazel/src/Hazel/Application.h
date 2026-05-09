#pragma once
#include "hzpch.h"
#include "Core.h"
#include "events/ApplicationEvent.h"
#include "window.h"
#include"imgui/imGuiLayer.h"
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
		static Application& Get() { return *s_Application; }
		inline Window& GetWindow() { return *m_Window; }
		void Run();
	private:
		
		bool OnWindowClose(WindowCloseEvent& event);
		std::unique_ptr<Window> m_Window;
		imGuiLayer* m_imGuiLayer;
		LayerStack m_LayerStack;
		bool m_Running = true;
	private:
		static Application* s_Application;
	};
	Application* CreateApplication();

}
