#pragma once
#include "ScopeWatch.h"
class AutoUnbind {
public:
	virtual void _bind() = 0;
	virtual void _unbind() = 0;
};

#define Bind(obj) \
	((AutoUnbind*)((obj)))->_bind();\
	ENGINE::UTIL::ScopeWatch<AutoUnbind> unbinderWatch((obj), &AutoUnbind::_unbind)
