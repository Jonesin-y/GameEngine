#pragma once
#include "hzpch.h"
#include "Core.h"
namespace Hazel
{
	class HAZEL_API Input
	{
	public:
		static bool IsKeyPressed(int keyCode)					{ return s_Instance->IsKeyPressedImpl(keyCode); }
		static bool IsMouseButtonPressed(int button)			{ return s_Instance->IsMouseButtonPressedImpl(button); }
		static std::pair<float, float>GetMousePos()				{ return s_Instance->GetMousePosImpl(); }
		static float GetMousePosX()								{ return s_Instance->GetMousePosXImpl(); }
		static float GetMousePosY()								{ return s_Instance->GetMousePosYImpl(); }
	protected:
		 virtual bool IsKeyPressedImpl(int keyCode) = 0;
		 virtual bool IsMouseButtonPressedImpl(int button) = 0;
		 virtual std::pair<float, float>GetMousePosImpl() = 0;
		 virtual float GetMousePosXImpl() = 0;
		 virtual float GetMousePosYImpl() = 0;
	private:
		static Input* s_Instance;
	};
}