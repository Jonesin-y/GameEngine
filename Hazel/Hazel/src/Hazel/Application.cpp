#include"hzpch.h"
#include"KeyCode.h"
#include"Log.h"
#include"Application.h"
#include"events/ApplicationEvent.h"
#include"events/KeyEvent.h"
#include"events/MouseEvent.h"
#include"Windows/WindowsInput.h"
#include<GLFW/glfw3.h>
#include<glad/glad.h>

namespace Hazel
{
#define BIND_EVENT_FN(x) std::bind(&Application::x,this,std::placeholders::_1)
	Application* Application::s_Application = nullptr;
	Application::Application()
	{
		Application::s_Application = this;
		m_Window = std::unique_ptr<Window>(Window::Create());
		m_Window->SetEventCallback(BIND_EVENT_FN(OnEvent));
		m_imGuiLayer = new imGuiLayer;
		PushOverlay(m_imGuiLayer);
		unsigned int id;
		glGenVertexArrays(1, &id);

	}
	Application::~Application()
	{
	}
	void Application::OnEvent(Event& event)
	{
		EventDispatcher dispatcher(event);
		HZ_CORE_INFO("{0}",event.ToString());
		for (auto it = m_LayerStack.end();it != m_LayerStack.begin();)
		{
			(*--it)->OnEvent(event);
			if (event.Handled)
				break;
		}
		dispatcher.Dispatch<WindowCloseEvent>(BIND_EVENT_FN(OnWindowClose));
		
	}

	void Application::PushLayer(Layer* layer)
	{
		m_LayerStack.PushLayer(layer);
	}

	void Application::PushOverlay(Layer* overlay)
	{
		m_LayerStack.PushOverlay(overlay);
	}
	
	void Application::Run()
	{
		while (m_Running)
		{
			glClearColor(0.2f, 0.3f, 0.8f, 1.0f);
			glClear(GL_COLOR_BUFFER_BIT);
			for (Layer* layer : m_LayerStack)
			{
				layer->OnUpdate();
			}
			m_imGuiLayer->Begin();
			for (Layer* layer : m_LayerStack)
			{
				layer->OnImGuiRender();
			}
			m_imGuiLayer->End();
			m_Window->OnUpdate();
			
		}
	}
	bool Application::OnWindowClose(WindowCloseEvent& event)
	{
		m_Running = false;
		return true;
	}
}