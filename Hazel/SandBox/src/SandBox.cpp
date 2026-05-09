#include "Hazel.h"
class ExampleLayer : public Hazel::Layer
{
public:
	ExampleLayer() :
		Layer("Example"){}
	void OnEvent(Hazel::Event& event) override
	{
		
	}
	void OnUpdate() override
	{
		
	}
};
class SandBox :public Hazel::Application
{
public:
	SandBox()
	{
	};
	~SandBox()
	{

	};
	
};

Hazel::Application* Hazel::CreateApplication()
{
	return new SandBox();
	

}