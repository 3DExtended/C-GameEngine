#pragma once
#include "ScopeWatch.h"
namespace ENGINE {
	namespace UTIL {
		class AutoUnbind {
		public:
			virtual void _bind() = 0;
			virtual void _unbind() = 0;
		};
	}
}
#define CONCATENATE_DETAIL(x,y) x##y
#define CONCATENATE(x,y) CONCATENATE_DETAIL(x,y)
#define MAKE_UNIQUE(x) CONCATENATE(x,__COUNTER__)

#define Bind(obj)\
	((ENGINE::UTIL::AutoUnbind*)((obj)))->_bind();\
	ENGINE::UTIL::ScopeWatch<ENGINE::UTIL::AutoUnbind> MAKE_UNIQUE(unbindWatch)((obj), &ENGINE::UTIL::AutoUnbind::_unbind)
	