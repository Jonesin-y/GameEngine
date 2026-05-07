#pragma once
#include"hzpch.h"
#include"window.h"
struct GLFWwindow;
namespace Hazel
{
	
	class HAZEL_API WindowsWindow : public Window
	{
		public:
		WindowsWindow(const WindowProps& props);
		virtual ~WindowsWindow();
		virtual void OnUpdate() override;
		virtual unsigned int GetWidth() const override { return m_Data.Width; }
		virtual unsigned int GetHeight() const override { return m_Data.Height; }
		virtual void SetEventCallback(const EventCallbackFn& callback) override { m_Data.EventCallback = callback; }
		virtual void SetVSync(bool enabled) override;
		virtual bool IsVSync() const override;
		virtual void* GetNativeWindow() const { return m_Window; }
	private:
		bool Init(const WindowProps& props);
		void Shutdown();

	private:
		GLFWwindow* m_Window;
		struct WindowData
		{
			std::string Title;
			unsigned int Width;
			unsigned int Height;
			bool VSync;
			EventCallbackFn EventCallback;
		};
		WindowData m_Data;
	};
}
