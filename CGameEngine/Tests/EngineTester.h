#pragma once
#include <vector>
#include <iostream>
#include <algorithm>
#include <functional>
#include <string>
class EngineTester {
public:
	static EngineTester* GetInstance();

	int TestEverthing();
	void RegisterTest(std::pair<std::string, std::function<int(void)>> func);
private:
	EngineTester() {};
	std::vector<std::pair<std::string, std::function<int(void)>>> functions;
	static EngineTester * instance;
};

#define Test EngineTester::GetInstance()->RegisterTest(std::pair<std::string, std::function<int(void)>>