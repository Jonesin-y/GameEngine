#pragma once
#include"Event.h"
#include<sstream>
namespace Hazel {
	class HAZEL_API MouseMovedEvent :public Event
	{
		EVENT_CLASS_TYPE(MouseMoved);
		EVENT_CLASS_CATEGORY(EventCategoryInput | EventCategoryMouse)
	public:
		MouseMovedEvent(float MouseX,float MouseY):
			m_MouseX(MouseX), m_MouseY(MouseY) {}
		inline float GetMouseX() const { return m_MouseX; }
		inline float GetMouseY() const { return m_MouseY; }
		virtual std::string ToString() const override
		{
			std::stringstream ss;
			ss << "MouseMovedEvent: " << m_MouseX << ", " << m_MouseY;
			return ss.str();
		}

	private:
		float m_MouseX, m_MouseY;
	};
	class HAZEL_API MouseScrolledEvent :public Event
	{
		EVENT_CLASS_TYPE(MouseScrolled);
		EVENT_CLASS_CATEGORY(EventCategoryInput | EventCategoryMouse);
	public:
		MouseScrolledEvent(float ScrolledX,float ScrolledY) :
			m_ScrolledX(ScrolledX), m_ScrolledY(ScrolledY) {}
		inline float GetScrolledX() const { return m_ScrolledX; }
		inline float GetScrolledY() const { return m_ScrolledY; }
		virtual std::string ToString() const override
		{
			std::stringstream ss;
			ss << "MouseScrolledEvent: " << m_ScrolledX << ", " << m_ScrolledY;
			return ss.str();
		}

	private:
		float m_ScrolledX, m_ScrolledY;
	};
	class HAZEL_API MouseButtonPressedEvent :public Event
	{
		EVENT_CLASS_TYPE(MouseButtonPressed);
		EVENT_CLASS_CATEGORY(EventCategoryInput | EventCategoryMouseButton);
	public:
		MouseButtonPressedEvent(int buttonCode, int repeatCount)
			: m_ButtonCode(buttonCode), m_RepeatCount(repeatCount) {}
		inline int GetButtonCode() const { return m_ButtonCode; }
		inline int GetRepeatCount() const { return m_RepeatCount; }
		virtual std::string ToString() const override
		{
			std::stringstream ss;
			ss << "MouseButtonPressedEvent: " << m_ButtonCode << ", " << m_RepeatCount;
			return ss.str();
		}
	private:
		int m_ButtonCode, m_RepeatCount;
	};
	class HAZEL_API MouseButtonReleasedEvent :public Event
	{
		EVENT_CLASS_TYPE(MouseButtonReleased);
		EVENT_CLASS_CATEGORY(EventCategoryMouseButton | EventCategoryInput);
	public:
		MouseButtonReleasedEvent(int buttonCode) :
			m_ButtonCode(buttonCode) {
		}
		inline int GetButtonCode() const { return m_ButtonCode; }
		virtual std::string ToString() const override
		{
			std::stringstream ss;
			ss << "MouseButtonReleasedEvent: " << m_ButtonCode;
			return ss.str();
		}
	private:
		int m_ButtonCode;
	};
	
}