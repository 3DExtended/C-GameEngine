#pragma once
namespace ENGINE {
	namespace UTIL {
		template<typename T>
		class Curve {
		public:
			virtual T GetValue(T xValue) = 0;
		};
	}
}

