#pragma once
#ifdef HZ_PLATFORM_WINDOWS
extern Hazel::Application* Hazel::CreateApplication();

int main(int argc, char** argy)
{
	Hazel::Log::Init();
	HZ_CORE_WARN("Log Initialized");
	auto app = Hazel::CreateApplication();
	app->Run();
	delete app;
}
#endif