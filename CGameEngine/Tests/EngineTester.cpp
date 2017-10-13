#include "EngineTester.h"
EngineTester* EngineTester::instance = nullptr;

EngineTester * EngineTester::GetInstance() {
	if (instance == nullptr) 
		instance = new EngineTester(); 
	return instance; 
}

int EngineTester::TestEverthing()
{
	std::cout << "--------------------------------------" << std::endl;
	std::cout << "--------Testing the GameEngine--------" << std::endl;
	std::cout << "--------------------------------------" << std::endl;
	std::cout << std::endl;

	int numberOfFailedTests = 0;
	for (unsigned int i = 1;i < functions.size() + 1; i++)
	{
		std::pair<std::string, std::function<int(void)>> func = functions[i-1];
		std::cout << "\t" << func.first << " - Test: " << i << "/" << functions.size() << std::endl;
		int res = func.second();
		if (res == 0) {
			std::cout << "\t" << "Test number " << i << " passed!" << std::endl;
		}
		else {
			std::cout << std::endl;
			std::cout << "--------------------" << std::endl;
			std::cout << "\t" << "Test number " << i << " failed!" << std::endl;
			std::cout << "\t" << "Test called " << func.first << " failed!" << std::endl;
			std::cout << "\t" << "Failure number: " << res << std::endl;
			std::cout << "--------------------" << std::endl;
			std::cout << std::endl;
			numberOfFailedTests++;
		}
		std::cout << std::endl;
	}

	if (numberOfFailedTests == 0) {
		std::cout << std::endl;
		std::cout << "-----------------------------------" << std::endl;
		std::cout << "---------All tests passed!---------" << std::endl;
		std::cout << "-----------------------------------" << std::endl;
	}
	else {
		std::cout << std::endl;
		std::cout << "-----------------------------------" << std::endl;
		std::cout << "---------"<< numberOfFailedTests<<"/"<<functions.size()<<" failed!" << std::endl;
		std::cout << "-----------------------------------" << std::endl;
	}
	return numberOfFailedTests;

}

void EngineTester::RegisterTest(std::pair<std::string, std::function<int(void)>> func)
{
	functions.push_back(func);
}
