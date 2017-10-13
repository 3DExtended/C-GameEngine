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
		int res = func.second();
		if (res == 0) {
			std::cout << "\t" << "Test " <<i<< "/" << functions.size() << ":   " << func.first << std::endl;
			std::cout << "\t" << "Test number " << i << " passed!" << std::endl;
		}
		else {
			std::cout << std::endl;
			std::cout << "\t\\/   \\/   \\/   \\/   \\/   \\/   \\/   \\/   \\/   \\/ " << std::endl;
			std::cout << std::endl;
			std::cout << "\t\t" << "Test " << i << "/" << functions.size() << ":   " << func.first << " failed!"<< std::endl;
			std::cout << "\t\t" << "Failure number: " << res << std::endl;
			std::cout << std::endl;
			std::cout << "\t/\\   /\\   /\\   /\\   /\\   /\\   /\\   /\\   /\\   /\\ " << std::endl;
			std::cout << std::endl;
			numberOfFailedTests++;
		} 
		std::cout << std::endl;
	}

	if (numberOfFailedTests == 0) {
		std::cout << "-----------------------------------" << std::endl;
		std::cout << "---------All tests passed!---------" << std::endl;
		std::cout << "-----------------------------------" << std::endl;
	}
	else {
		std::cout << "-----------------------------------" << std::endl;
		std::cout << "\t"<< numberOfFailedTests<<"/"<<functions.size()<<" tests failed!" << std::endl;
		std::cout << "-----------------------------------" << std::endl;
	}
	return numberOfFailedTests;

}

void EngineTester::RegisterTest(std::pair<std::string, std::function<int(void)>> func)
{
	functions.push_back(func);
}
