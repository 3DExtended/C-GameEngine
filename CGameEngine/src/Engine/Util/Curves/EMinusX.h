#pragma once
#include "../Curve.h"
#include <glm/glm.hpp>

using namespace ENGINE::UTIL;
template<typename T>
class EMinusX : public Curve<T> {
	T GetValue(T xValue) {
		return (T)glm::exp(-xValue);
	};
};