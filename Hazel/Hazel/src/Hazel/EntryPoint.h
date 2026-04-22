#pragma once
#ifdef HZ_PLATFORM_WINDOWS
extern Hazel::Application* Hazel::CreateApplication();

int main(int argc, char** argy)
{
	Hazel::Log::Init();
	HZ_CORE_ERROR("ERROR!");
	HZ_INFO("hello!");
	auto app = Hazel::CreateApplication();
	app->Run();
	delete app;
}
#endif