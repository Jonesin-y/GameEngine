#include"test.h"
#include"string"
#include"imgui/imgui.h"
#include<vector>
#include<functional>
test::TestMenu::TestMenu(Test*& currentTest):
 m_CurrentTest(currentTest)
{
	
}
void test::TestMenu::OnImGuiRender()
{
	for (auto& test : m_Tests)
	{
		if (test.first.c_str() && ImGui::Button(test.first.c_str()))
		{
			m_CurrentTest=test.second();
		}
	}
}