#include "hzpch.h"
#include "Log.h"
#include "WindowsWindow.h"
#include"events/ApplicationEvent.h"
#include"events/KeyEvent.h"
#include"events/MouseEvent.h"
#include<glad/glad.h>
#include<GLFW/glfw3.h>
#include "WindowsInput.h"
namespace Hazel
{
	Input* Input::s_Instance = new WindowsInput();
	static bool s_GLFWInitialized = false;
	static void GLFWErrorCallback(int error, const char* detail)
	{
		HZ_CORE_ERROR("GLFW ERROR ({0}),{1}", error, detail);
	}
	Window* Window::Create(const WindowProps& props)
	{
		return new WindowsWindow(props);
	}
	WindowsWindow::WindowsWindow(const WindowProps& props)
	{
		Init(props);
	}
	WindowsWindow::~WindowsWindow()
	{
		Shutdown();
	}
	void WindowsWindow::SetVSync(bool enabled)
	{
		if (enabled)
			glfwSwapInterval(1);
		else
			glfwSwapInterval(0);
		m_Data.VSync = enabled;
	}

	bool WindowsWindow::IsVSync() const
	{
		return m_Data.VSync;
	}
	void WindowsWindow::Shutdown()
	{
		glfwDestroyWindow(m_Window);
	}
	void WindowsWindow::OnUpdate()
	{
		glfwPollEvents();
		glfwSwapBuffers(m_Window);
	}
	bool WindowsWindow::Init(const WindowProps& props)
	{
		m_Data.Title = props.Title;
		m_Data.Width = props.Width;
		m_Data.Height = props.Height;
		HZ_CORE_INFO("Created Window {0},({1},{2})", m_Data.Title, m_Data.Width, m_Data.Height);
		if (!s_GLFWInitialized)
		{
			int success = glfwInit();
			HZ_CORE_ASSERT(success, "Could not initialized GLFW!");
			glfwSetErrorCallback(GLFWErrorCallback);
			s_GLFWInitialized = true;
		}
		m_Window = glfwCreateWindow(m_Data.Width, m_Data.Height, m_Data.Title.c_str(), nullptr, nullptr);
		glfwMakeContextCurrent(m_Window);
		int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		HZ_CORE_ASSERT(status,"Failed to load Glad!")
		glfwSetWindowUserPointer(m_Window, &m_Data);
		SetVSync(true);

		//Set glfw callbacks
		glfwSetWindowSizeCallback(m_Window, [](GLFWwindow* window, int width, int height)
			{
				WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
				data.Width = width;
				data.Height = height;
				WindowResizeEvent event(width, height);
				data.EventCallback(event);
			});
		glfwSetWindowCloseCallback(m_Window, [](GLFWwindow* window)
			{
				WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
				WindowCloseEvent event;
				data.EventCallback(event);
			});
		glfwSetKeyCallback(m_Window, [](GLFWwindow* window, int key, int sancode, int action, int mods)
			{
				WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
				switch (action)
				{
				case GLFW_PRESS:
					{
					KeyPressedEvent event(key, 0);
					data.EventCallback(event);
					}
				case GLFW_RELEASE:
					{
					KeyReleasedEvent event(key);
					data.EventCallback(event);
					}
				case GLFW_REPEAT:
					{
					KeyPressedEvent event(key, 1);
					data.EventCallback(event);
					}
				}

			});
		glfwSetMouseButtonCallback(m_Window, [](GLFWwindow* window, int button, int action, int mods)
			{
				WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
				switch (action)
				{
				case GLFW_PRESS:
				{
					MouseButtonPressedEvent event(button);
					data.EventCallback(event);
				}
				case GLFW_RELEASE:
				{
					MouseButtonReleasedEvent event(button);
					data.EventCallback(event);
				}
				}
			});
		glfwSetScrollCallback(m_Window, [](GLFWwindow* window, double xOffset, double yOffset)
			{
				WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
				MouseScrolledEvent event((float)xOffset, (float)yOffset);
				data.EventCallback(event);
			});
		glfwSetCursorPosCallback(m_Window, [](GLFWwindow* window, double xPosition, double yPosition)
			{
				WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
				MouseMovedEvent event((float)xPosition, (float)yPosition);
				data.EventCallback(event);
			}
		);
		return true;
	}

}