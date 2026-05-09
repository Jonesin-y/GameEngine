#include "hzpch.h"
#include "glfw/glfw3.h"
#include "WindowsInput.h"
#include "Application.h"
bool Hazel::WindowsInput::IsKeyPressedImpl(int keyCode)
{
	auto window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());
	int state = glfwGetKey(window, keyCode);
	return state == GLFW_PRESS || state == GLFW_REPEAT;
}

bool Hazel::WindowsInput::IsMouseButtonPressedImpl(int button)
{
	auto window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());
	int state = glfwGetMouseButton(window, button);
	return state == GLFW_PRESS;
}

std::pair<float, float> Hazel::WindowsInput::GetMousePosImpl()
{
	auto window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());
	double xpos, ypos;
	glfwGetCursorPos(window, &xpos, &ypos);
	return{ (float)xpos, (float)ypos };
}

float Hazel::WindowsInput::GetMousePosXImpl()
{
	auto [x, y] = GetMousePosImpl();
	return x;
}

float Hazel::WindowsInput::GetMousePosYImpl()
{
	auto [x, y] = GetMousePosImpl();
	return y;
}

