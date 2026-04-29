#pragma once
#include"hzpch.h"
#include"events/Event.h"
namespace Hazel {
	class HAZEL_API Layer
	{
	public:
		Layer(const std::string& name = "Layer");
		~Layer() {};
		virtual void OnAttach() {};
		virtual void OnDetach() {};
		virtual void OnUpdate() {};
		virtual void OnEvent(Event& event) {};

		std::string GetName() { return m_LayerName; }


	private:
		std::string m_LayerName;
	};
}
