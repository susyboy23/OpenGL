#pragma once
#include <string>
#include <vector>
#include <functional>
#include <iostream>

namespace test {
	class Test {
	public:
		Test() {}
		virtual ~Test() {}

		virtual void OnUpdate(float detlaTime) {}
		virtual void OnRender() {}
		virtual void OnImGuiRender() {}
	};

	class TestMenu : public Test {
	public:
	TestMenu(Test*& currentTestPointer); 

	void OnImGuiRender() override;
	template <typename T>
	void RegisterTest(const std::string testName)
	{	
		std::cout << "Registering Test" << testName << std::endl;
		m_Tests.push_back(std::make_pair(testName, []() {return new T(); }));
	}
	private:
		std::vector<std::pair<std::string, std::function<Test*()>>> m_Tests ;
		Test*& m_CurrentTest;
	};


}