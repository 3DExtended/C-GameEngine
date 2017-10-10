#pragma once
#include "ScopeWatch.hpp"
namespace ENGINE {
	namespace UTIL {
		/// <summary>
		/// This class is a wrapper for using the scopewatch.
		/// The essential idea is to have a macro (Bind(...)) which can be used to bind a child 
		/// of this class and gets unbound automatically.
		/// </summary>
		class AutoUnbind {
		public:
			/// <summary>
			/// The method used to bind this object. 
			/// Has to be implemented!
			/// </summary>
			virtual void _bind() = 0;

			/// <summary>
			/// The method used to unbind this object. 
			/// Has to be implemented!
			/// </summary>
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
	