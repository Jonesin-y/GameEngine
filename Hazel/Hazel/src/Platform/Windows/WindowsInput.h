#pragma once
#include "Input.h"
namespace Hazel
{
	class WindowsInput : public Input
	{
	protected:
		virtual bool IsKeyPressedImpl(int keyCode) override;
		virtual bool IsMouseButtonPressedImpl(int button) override;
		virtual std::pair<float, float>GetMousePosImpl() override;
		virtual float GetMousePosXImpl() override;
		virtual float GetMousePosYImpl() override;
	};
}