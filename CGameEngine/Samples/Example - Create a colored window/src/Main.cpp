#include <tchar.h>	//Other entry point for windows
#include "Engine/Engine.h"

int _tmain(int argc, _TCHAR* argv[]) {
	
	//ENGINE::Run(0);
	ENGINE::EngineClass::RunEngine(0);
	return 0;
}