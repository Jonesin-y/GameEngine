#pragma once
#include"Event.h"
#include<sstream>
namespace Hazel {
	class HAZEL_API WindowResizeEvent :public Event
	{
		EVENT_CLASS_TYPE(WindowResize);
		EVENT_CLASS_CATEGORY(EventCategoryApplication)
	public:
		WindowResizeEvent(float Width, float Height)
			:m_Width(Width), m_Height(Height) {
		}
		inline float GetWidth() const { return m_Width; }
		inline float GetHeight() const { return m_Height; }
		virtual std::string ToString() const override
		{
			std::stringstream ss;
			ss << "WindowResizeEvent: " << m_Width << ", " << m_Height;
			return ss.str();
		}
	private:
		float m_Width, m_Height;
	};
	class HAZEL_API WindowFocusEvent :public Event
	{
		WindowFocusEvent() {};
		EVENT_CLASS_TYPE(WindowFocus);
		EVENT_CLASS_CATEGORY(EventCategoryApplication);
	};
	class HAZEL_API WindowLostFocusEvent :public Event
	{
		WindowLostFocusEvent() {};
		EVENT_CLASS_TYPE(WindowLostFocus);
		EVENT_CLASS_CATEGORY(EventCategoryApplication);
	};
	class HAZEL_API WindowMovedEvent :public Event
	{
		WindowMovedEvent() {};
		EVENT_CLASS_TYPE(WindowMoved);
		EVENT_CLASS_CATEGORY(EventCategoryApplication);
	};
	class HAZEL_API WindowCloseEvent :public Event
	{
		WindowCloseEvent() {};
		EVENT_CLASS_TYPE(WindowClose);
		EVENT_CLASS_CATEGORY(EventCategoryApplication);
	};
	class HAZEL_API AppTickEvent :public Event
	{
		AppTickEvent() {};
		EVENT_CLASS_TYPE(AppTick);
		EVENT_CLASS_CATEGORY(EventCategoryApplication);
	};
	class HAZEL_API AppUpdateEvent :public Event
	{
		AppUpdateEvent() {};
		EVENT_CLASS_TYPE(AppUpdate);
		EVENT_CLASS_CATEGORY(EventCategoryApplication);
	};
	class HAZEL_API AppRenderEvent :public Event
	{
		AppRenderEvent() {};
		EVENT_CLASS_TYPE(AppRender);
		EVENT_CLASS_CATEGORY(EventCategoryApplication);
	};
}