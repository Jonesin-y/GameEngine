#pragma once
#include<string>
#include<vector>
#include<functional>
namespace test
{
	class Test
	{
	
		
	public:
		Test() {};
		~Test() {};
		virtual void OnUpdate(float deltaTime) {};
		virtual void OnRender() {};
		virtual void OnImGuiRender() {};
	};
	class TestMenu :public Test
	{
	private:
		Test*& m_CurrentTest;
		std::vector<std::pair<std::string, std::function<Test* ()>>> m_Tests;
	public:
		
		TestMenu(Test*& currentTest);
		~TestMenu() {};

		virtual void OnImGuiRender() override;
		template<typename T>
		void TestRegister(const std::string&name)
		{
			m_Tests.push_back(std::make_pair(name, []() {return new T;}));
		}
	};
}