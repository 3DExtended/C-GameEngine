#pragma once
namespace ENGINE {

	class EngineClass {
	public:
		static void RunEngine(int indexOfStartScene);
	private:

	};

	void RunEngine(int indexOfStartScene) {
		EngineClass::RunEngine(indexOfStartScene);
	}
}