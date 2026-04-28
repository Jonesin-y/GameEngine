#include"hzpch.h"
#include"Log.h"
#include "Application.h"
#include"GLFW/glfw3.h"
#include"events/ApplicationEvent.h"
#include"events/KeyEvent.h"
#include"events/MouseEvent.h"
namespace Hazel
{
#define BIND_EVENT_FN(x) std::bind(&Application::x,this,std::placeholders::_1)
	Application::Application()
	{
		m_Window = std::unique_ptr<Window>(Window::Create());
		m_Window->SetEventCallback(BIND_EVENT_FN(OnEvent));
	}
	Application::~Application()
	{
	}
	void Application::OnEvent(Event& event)
	{
		EventDispatcher dispatcher(event);
		HZ_CORE_INFO("{0}",event.ToString());
		dispatcher.Dispatch<WindowCloseEvent>(BIND_EVENT_FN(OnWindowClose));
		
	}
	
	void Application::Run()
	{
		while (m_Running)
		{
			glClearColor(0.2f, 0.3f, 0.8f, 1.0f);
			glClear(GL_COLOR_BUFFER_BIT);
			m_Window->OnUpdate();
		}
	}
	bool Application::OnWindowClose(WindowCloseEvent& event)
	{
		m_Running = false;
		return true;
	}
}