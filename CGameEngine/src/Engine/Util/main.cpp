#include <iostream>
#include <glm/glm.hpp>
#include "./ScopeWatch.h"
using namespace ENGINE::UTIL;
class Test{
public:
	Test(){};

	void Shout(){
		glm::vec3 testVecasd(0);

		std::cout << "Test: " << testVecasd.x <<std::endl;
	}
};

void test(int argc, char const *argv[])
{

	std::cout << "Before shout"<<std::endl;

	Test* testing = new Test();

	{
		ScopeWatch<Test>(testing, &Test::Shout);

		std::cout << "In scope after watch" << std::endl;

	}

	std::cout << "Everything is closed." << std::endl;
}