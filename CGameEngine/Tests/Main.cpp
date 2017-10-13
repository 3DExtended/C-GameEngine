#include <iostream>
#include <cassert>
#include "EngineTester.h"


//include every component of the engine you wanna test
#include "Engine/Util/Math.h"



using namespace ENGINE::UTIL;

void buildTests() {

	Test("ENGINE::UTIL - Test the random Function", [] {
		for (int i = 0; i < 1000; i++) {
			float rnd = ENGINE::UTIL::rand();
			if (rnd < 0 || rnd >= 1) {
				return 1;
			}
		}

		return 0;
	}));

	Test("ENGINE::UTIL - Test the random Function", [] {
		for (int i = 0; i < 1000; i++) {
			float rnd = ENGINE::UTIL::rand();
			if (rnd < 0 || rnd >= 1) {
				return 1;
			}
		}

		return 0;
	}));


	
}


int main (int argc, char *argv[]){

	buildTests();

	return EngineTester::GetInstance()->TestEverthing();
}