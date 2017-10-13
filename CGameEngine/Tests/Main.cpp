#include <iostream>
#include <cassert>
#include "EngineTester.h"


//include every component of the engine you wanna test
#include "Engine/Util/Math.h"
#include "Engine/Util/Util.h"



using namespace ENGINE::UTIL;

void buildTests() {

	Test("ENGINE::UTIL Math.h - Test the random Function", [] {
		for (int i = 0; i < 1000; i++) {
			float rnd = ENGINE::UTIL::rand();
			if (rnd < 0 || rnd >= 1) {
				return 1;
			}
		}

		return 0;
	}));

	Test("ENGINE::UTIL Util.h - colorpartToOneRange: Expected values", [] {
		for (unsigned int i = 0; i < 255; i++) {
			float res = ENGINE::UTIL::colorpartToOneRange(i);
			if (res != ((float)i) / 255.0f) {
				return 1;
			}
			else if (res < 0 || res > 1) {
				return 2;
			}
		}

		return 0;
	}));

	Test("ENGINE::UTIL Util.h - splitString: Right vector size for a test string which can be split.", [] {
		std::string testStr = "Hello World. This is a test string to test the splitString function.";
		std::vector<std::string> parts = ENGINE::UTIL::splitString(testStr, ' ');
		if (parts.size() != 12) {
			return 1;
		}

		return 0;
	}));

	Test("ENGINE::UTIL Util.h - splitString: Right vector size for a test string which can not be split.", [] {
		std::string testStr = "ThereIsNoSpaceInThisSting";
		std::vector<std::string> parts = ENGINE::UTIL::splitString(testStr, ' ');
		if (parts.size() != 1) {
			return 1;
		}
		return 0;
	}));
	
	Test("ENGINE::UTIL Util.h - splitString: Right vector size for a test string which can be split.", [] {
		std::string testStr = "Hello World. This is a test string to test the splitString function.";
		std::vector<std::string> parts = ENGINE::UTIL::splitString(testStr, ' ');
		std::string arr[] = { "Hello", "World.", "This" , "is" , "a", "test","string","to", "test","the","splitString", "function." };
		std::vector<std::string> expectedRes(arr,arr+12);

		if (expectedRes.size() != parts.size())
			return 1;

		for (unsigned int i = 0; i < expectedRes.size() && i < parts.size(); i++) {
			if (parts[i] != expectedRes[i]) {
				return 2;
			}
		}

		return 0;
	}));
}


int main (int argc, char *argv[]){

	buildTests();

	return EngineTester::GetInstance()->TestEverthing();
}