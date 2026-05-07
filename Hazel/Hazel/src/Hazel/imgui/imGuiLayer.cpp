#include"hzpch.h"
#include"Core.h"
#include"Log.h"
#include"imgui.h"
#include"Application.h"
#include"imGuiLayer.h"
#include"OpenGL/imGuiRenderer.h"
#include<GLFW/glfw3.h>
#include<glad/glad.h>
namespace Hazel
{

	imGuiLayer::imGuiLayer()
	{
	}
	imGuiLayer::~imGuiLayer()
	{
	}
	void imGuiLayer::OnAttach()
	{
		ImGui::CreateContext();
		ImGuiIO& io = ImGui::GetIO(); 
		io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
		io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
		io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;
		ImGui::StyleColorsDark;
		// TEMPORARY: should eventually use Hazel key codes
		io.KeyMap[ImGuiKey_Tab] = GLFW_KEY_TAB;
		io.KeyMap[ImGuiKey_LeftArrow] = GLFW_KEY_LEFT;
		io.KeyMap[ImGuiKey_RightArrow] = GLFW_KEY_RIGHT;
		io.KeyMap[ImGuiKey_UpArrow] = GLFW_KEY_UP;
		io.KeyMap[ImGuiKey_DownArrow] = GLFW_KEY_DOWN;
		io.KeyMap[ImGuiKey_PageUp] = GLFW_KEY_PAGE_UP;
		io.KeyMap[ImGuiKey_PageDown] = GLFW_KEY_PAGE_DOWN;
		io.KeyMap[ImGuiKey_Home] = GLFW_KEY_HOME;
		io.KeyMap[ImGuiKey_End] = GLFW_KEY_END;
		io.KeyMap[ImGuiKey_Insert] = GLFW_KEY_INSERT;
		io.KeyMap[ImGuiKey_Delete] = GLFW_KEY_DELETE;
		io.KeyMap[ImGuiKey_Backspace] = GLFW_KEY_BACKSPACE;
		io.KeyMap[ImGuiKey_Space] = GLFW_KEY_SPACE;
		io.KeyMap[ImGuiKey_Enter] = GLFW_KEY_ENTER;
		io.KeyMap[ImGuiKey_Escape] = GLFW_KEY_ESCAPE;
		io.KeyMap[ImGuiKey_A] = GLFW_KEY_A;
		io.KeyMap[ImGuiKey_C] = GLFW_KEY_C;
		io.KeyMap[ImGuiKey_V] = GLFW_KEY_V;
		io.KeyMap[ImGuiKey_X] = GLFW_KEY_X;
		io.KeyMap[ImGuiKey_Y] = GLFW_KEY_Y;
		io.KeyMap[ImGuiKey_Z] = GLFW_KEY_Z;

		ImGui_ImplOpenGL3_Init("#version 410");

	}
	void imGuiLayer::OnDetach()
	{
	}

	void imGuiLayer::OnEvent(Event& event)
	{
		EventDispatcher dispatcher(event);
		dispatcher.Dispatch<MouseButtonPressedEvent>	(HZ_BIND_EVENT_FN(imGuiLayer::OnMouseButtonPressedEvent));
		dispatcher.Dispatch<MouseButtonReleasedEvent>	(HZ_BIND_EVENT_FN(imGuiLayer::OnMouseButtonReleasedEvent));
		dispatcher.Dispatch<MouseMovedEvent>			(HZ_BIND_EVENT_FN(imGuiLayer::OnMouseMovedEvent));
		dispatcher.Dispatch<MouseScrolledEvent>			(HZ_BIND_EVENT_FN(imGuiLayer::OnMouseScrolledEvent));
		dispatcher.Dispatch<KeyPressedEvent>			(HZ_BIND_EVENT_FN(imGuiLayer::OnKeyPressedEvent));
		dispatcher.Dispatch<KeyReleasedEvent>			(HZ_BIND_EVENT_FN(imGuiLayer::OnKeyReleasedEvent));
		dispatcher.Dispatch<WindowResizeEvent>			(HZ_BIND_EVENT_FN(imGuiLayer::OnWindowResizedEvent));

	}

	bool imGuiLayer::OnMouseButtonPressedEvent(MouseButtonPressedEvent& e)
	{
		ImGuiIO& io = ImGui::GetIO();
		io.AddMouseButtonEvent(e.GetButtonCode(), true);
		return false;

	}

	bool imGuiLayer::OnMouseButtonReleasedEvent(MouseButtonReleasedEvent& e)
	{
		ImGuiIO& io = ImGui::GetIO();
		io.AddMouseButtonEvent(e.GetButtonCode(), false);

		
		return false;
	}

	bool imGuiLayer::OnMouseMovedEvent(MouseMovedEvent& e)
	{
		ImGuiIO& io = ImGui::GetIO();
		io.AddMousePosEvent(e.GetMouseX(), e.GetMouseY());
		return false;
	}

	bool imGuiLayer::OnMouseScrolledEvent(MouseScrolledEvent& e)
	{
		ImGuiIO& io = ImGui::GetIO();
		io.AddMouseWheelEvent(e.GetScrolledX(), e.GetScrolledY());

		return false;
	}

	bool imGuiLayer::OnKeyPressedEvent(KeyPressedEvent& e)
	{
		ImGuiIO& io = ImGui::GetIO();
		
		io.KeysDown[e.GetKeyCode()] = true;

		io.KeyAlt = io.KeysDown[GLFW_KEY_LEFT_ALT] || io.KeysDown[GLFW_KEY_RIGHT_ALT];
		io.KeyCtrl = io.KeysDown[GLFW_KEY_LEFT_CONTROL] || io.KeysDown[GLFW_KEY_RIGHT_CONTROL];
		io.KeyShift = io.KeysDown[GLFW_KEY_LEFT_SHIFT] || io.KeysDown[GLFW_KEY_RIGHT_SHIFT];
		io.KeySuper = io.KeysDown[GLFW_KEY_LEFT_SUPER] || io.KeysDown[GLFW_KEY_RIGHT_SUPER];

		return false;
	}

	bool imGuiLayer::OnKeyReleasedEvent(KeyReleasedEvent& e)
	{
		ImGuiIO& io = ImGui::GetIO();
		io.KeysDown[e.GetKeyCode()] = false;

		io.KeyAlt = io.KeysDown[GLFW_KEY_LEFT_ALT] || io.KeysDown[GLFW_KEY_RIGHT_ALT];
		io.KeyCtrl = io.KeysDown[GLFW_KEY_LEFT_CONTROL] || io.KeysDown[GLFW_KEY_RIGHT_CONTROL];
		io.KeyShift = io.KeysDown[GLFW_KEY_LEFT_SHIFT] || io.KeysDown[GLFW_KEY_RIGHT_SHIFT];
		io.KeySuper = io.KeysDown[GLFW_KEY_LEFT_SUPER] || io.KeysDown[GLFW_KEY_RIGHT_SUPER];
		return false;
	}

	bool imGuiLayer::OnWindowResizedEvent(WindowResizeEvent& e)
	{
		ImGuiIO& io = ImGui::GetIO();

		io.DisplaySize = ImVec2(e.GetWidth(), e.GetHeight());
		io.DisplayFramebufferScale = ImVec2(1.0f, 1.0f);
		 
		glViewport(0, 0, e.GetWidth(), e.GetHeight());

		return false;
	}

	bool imGuiLayer::OnWindowClosedEvent(WindowCloseEvent& e)
	{
		ImGuiIO& io = ImGui::GetIO();

		return false;
	}

	bool imGuiLayer::OnWindowMovedEvent(WindowMovedEvent& e)
	{
		ImGuiIO& io = ImGui::GetIO();
		return false;
	}

	bool imGuiLayer::OnWindowFocusedEvent(WindowFocusEvent& e)
	{
		ImGuiIO& io = ImGui::GetIO();
		return false;
	}

	void imGuiLayer::OnUpdate()
	{
		ImGuiIO& io = ImGui::GetIO();
		Application* app = Application::Get();
		io.DisplaySize = ImVec2(app->GetWindow().GetWidth(), app->GetWindow().GetHeight());
		float time = glfwGetTime();
		float deltaTime = (m_Time > 0) ? time - m_Time : (1.0f / 144.0f);
		io.DeltaTime = deltaTime;
		ImGui_ImplOpenGL3_NewFrame();
		m_Time = time;

		ImGui::NewFrame();
		static bool show = false;
		ImGui::ShowDemoWindow(&show);

		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
		
	}
	
}